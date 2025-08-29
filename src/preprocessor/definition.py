"""
Read the definitions from the source code
"""

from loguru import logger
from enum import Enum

from src.utils import FilePos


class DefinitionReader:
    """
    The class to read the definitions from the source code
    This class is just a set of static methods, no need to create an instance
    """

    def __init__(self): ...

    @staticmethod
    def parse_locrange(locrange: str) -> tuple[FilePos, FilePos]:
        """
        Parse the location range string

        :param locrange: The location range string
        :return: The start position and end position
        """
        start, end = locrange.split(" -> ")
        return FilePos.from_location_line(start), FilePos.from_location_line(end)

    @staticmethod
    def find_comment(
        start_line: FilePos, is_backward: bool = True
    ) -> tuple[FilePos | None, FilePos | None, str]:
        """
        Find the comment forward or backward from the start line (contain the start line)

        :param start: The start position
        :param is_backward: True if find backward, False otherwise
        :return: The comment start position, comment end position (include the start and end), and the comment content
                 Return (None, None, "") if not found
        """
        # Algorithm (For forward searching):
        # 1. Init state
        # 2. Check current state:
        #   2.1 If in init state, goto step 3.
        #   2.2 If in multiline-comment state, goto step 4.
        #   2.3 If in non-comment state, return result.
        # 3. get the next line:
        #   3.1 If it starts with "//", into init state, goto step 2.
        #   3.2 If it starts with "/*", into multiline-comment state, goto step 2.
        #   3.3 Else, into non-comment state, set result to line end, goto step 2.
        # 4. Find the next "*/":
        #   4.1 If found and the "*/" is at the end of the line, into init state, goto step 2.
        #   4.2 If found and the "*/" is not at the end of the line, into non-comment state, set result to "*/" position, goto step 2.
        #   4.3 If not found, into non-comment state, set result to "/*" position, goto step 2.

        # prepare positions
        if is_backward:
            start_line.set_to_end_of_line()
        else:
            start_line.set_to_start_of_line()
        comment_end_pos = start_line.copy()
        comment_start_pos = start_line.copy()
        cur_pos = start_line.copy()

        # prepare state
        class State(Enum):
            INIT = 1
            MULTILINE_COMMENT = 2
            NON_COMMENT = 3

        state = State.INIT

        def get_next_line() -> FilePos:
            """
            Get the next line position
            """
            if not hasattr(get_next_line, "after_first_invocation"):
                # because the during the first invocation, the current line has not been processed
                # so we need to return the current line
                get_next_line.after_first_invocation = True
                return cur_pos

            try:
                if is_backward:
                    # move to the previous line
                    new_line = FilePos(cur_pos.file, cur_pos.line - 1, 1)
                    new_line.set_to_end_of_line()
                else:
                    # move to the next line
                    new_line = FilePos(cur_pos.file, cur_pos.line + 1, 1)
                    new_line.set_to_start_of_line()
            except:
                # out of range
                return None
            return new_line

        def parse_next_line():
            """
            Parse the next line
            """
            nonlocal cur_pos, comment_end_pos, state

            if (next_line := get_next_line()) is not None:
                cur_pos = next_line
            else:
                # out of range, into non-comment state
                state = State.NON_COMMENT
                comment_end_pos = cur_pos
                return

            if cur_pos.cur_line.lstrip().startswith("//"):
                # single line comment
                state = State.INIT
            else:
                if not is_backward and cur_pos.cur_line.lstrip().startswith("/*"):
                    # multiline comment
                    state = State.MULTILINE_COMMENT
                elif is_backward and cur_pos.cur_line.rstrip().endswith("*/"):
                    # multiline comment
                    state = State.MULTILINE_COMMENT
                else:
                    # not a comment
                    state = State.NON_COMMENT
                    comment_end_pos = cur_pos

        def is_pos_at_end_of_line_after_strip(pos: FilePos, is_backward: bool) -> bool:
            """
            Check if the position is at the end of the line after strip
            """
            end_of_line_pos = pos.copy()
            if not is_backward:
                end_of_line_pos.set_to_end_of_line()
            else:
                end_of_line_pos.set_to_start_of_line()

            if pos == end_of_line_pos:
                return True

            content = pos.get_content_till_pos(end_of_line_pos)
            if not is_backward:
                content = content.removeprefix(pos.cur_char).strip()
            else:
                content = content.removesuffix(pos.cur_char).strip()

            return content == ""

        def find_multiline_comment_end():
            """
            Find the end of the multiline comment
            """
            nonlocal cur_pos, comment_end_pos, state

            # find the end of the multiline comment
            if not is_backward:
                mc_end_pos = cur_pos.find_str("*/", is_backward=False)
                if mc_end_pos is not None:
                    # set to '/' of "*/"
                    mc_end_pos.set_to_next_char()
            else:
                mc_end_pos = cur_pos.find_str("/*", is_backward=True)

            if mc_end_pos is None:
                # not found, set result to "/*" position
                state = State.NON_COMMENT
                comment_end_pos = cur_pos
            elif is_pos_at_end_of_line_after_strip(mc_end_pos, is_backward):
                # found and at the end of the line, into init state
                state = State.INIT
                cur_pos = mc_end_pos
            else:
                # found and not at the end of the line, into non-comment state
                state = State.NON_COMMENT
                comment_end_pos = mc_end_pos

        # start searching
        while state != State.NON_COMMENT:
            # check current state
            if state == State.INIT:
                parse_next_line()
            elif state == State.MULTILINE_COMMENT:
                find_multiline_comment_end()

        # return the result
        if comment_start_pos > comment_end_pos:
            comment_start_pos, comment_end_pos = comment_end_pos, comment_start_pos
        return (
            comment_start_pos,
            comment_end_pos,
            comment_start_pos.get_content_till_pos(comment_end_pos).strip(),
        )

    @staticmethod
    def with_comment(backward_comment: bool = True, forward_comment: bool = False):
        """
        The decorator to add the comment to the return value of the reader function
        """

        def decorator(reader_func):
            def wrapper(*args, **kwargs):
                start_pos, end_pos, content = reader_func(*args, **kwargs)
                if start_pos is None:
                    return (None, None, "")

                if backward_comment:
                    # if need to add the backward comment, find the comment backward
                    line_before = FilePos(start_pos.file, start_pos.line - 1, 1)
                    (
                        backward_comment_start,
                        backward_comment_end,
                        backward_comment_content,
                    ) = DefinitionReader.find_comment(line_before, is_backward=True)
                    if backward_comment_start is not None:
                        content = backward_comment_content + "\n" + content
                        start_pos = backward_comment_start

                if forward_comment:
                    # if need to add the forward comment, find the comment forward
                    line_after = FilePos(end_pos.file, end_pos.line + 1, 1)
                    (
                        forward_comment_start,
                        forward_comment_end,
                        forward_comment_content,
                    ) = DefinitionReader.find_comment(line_after, is_backward=False)
                    if forward_comment_start is not None:
                        content += "\n" + forward_comment_content
                        end_pos = forward_comment_end
                return start_pos, end_pos, content

            return wrapper

        return decorator

    @staticmethod
    @with_comment(backward_comment=True, forward_comment=False)
    def read_function_signature(
        function_locrange: str, is_template: bool = False
    ) -> tuple[FilePos, FilePos, str]:
        """
        Read the function signature

        :param function_locrange: The function location range string
        :param is_template: True if the function is a template function, False otherwise
        :return: The function start position, function end position, and the function signature
        """
        try:
            # because the function locrange may be a implementation, its end position may be the end of the function,
            # so we only use the start position to find the function signature
            start_pos, _ = DefinitionReader.parse_locrange(function_locrange)
        except ValueError as e:
            logger.error(
                f"Invalid function signature location range: {function_locrange}, {e}"
            )
            return (None, None, "")

        # find the ";" or "{" after
        semicolon_pos = start_pos.find_str(";")
        brace_pos = start_pos.find_str("{")
        match (semicolon_pos is None, brace_pos is None):
            case (True, True):
                logger.error(
                    f"Can not find the end of the function signature: {function_locrange}"
                )
                return (None, None, "")
            case (False, True):
                end_pos = semicolon_pos
            case (True, False):
                end_pos = brace_pos
            case (False, False):
                end_pos = min(semicolon_pos, brace_pos)

        # find "template" keyword before the function signature
        if is_template:
            template_pos = start_pos.find_str("template", is_backward=True)
            if template_pos is not None:
                start_pos = template_pos

        return (
            start_pos,
            end_pos,
            start_pos.get_content_till_pos(end_pos).strip() + ";",
        )  # add the semicolon

    @staticmethod
    def _read_simple_element_definition(
        element_locrange: str, element_type: str
    ) -> tuple[FilePos, FilePos, str]:
        """
        This is a helper function to read the simple element definition which is ended with ";"

        :param element_locrange: The element location range string
        :param element_type: The element type, used for logging
        :return: The element start position, element end position, and the element definition
        """
        try:
            start_pos, end_pos = DefinitionReader.parse_locrange(element_locrange)
        except ValueError:
            logger.error(
                f"Invalid {element_type} definition location range: {element_locrange}"
            )
            return (None, None, "")

        # find the ";" after end_pos
        semicolon_pos = end_pos.find_str(";")
        if semicolon_pos is None:
            logger.error(
                f"Can not find the end of the {element_type} definition: {element_locrange}"
            )
            return (None, None, "")

        return (
            start_pos,
            semicolon_pos,
            start_pos.get_content_till_pos(semicolon_pos).strip() + ";",
        )

    @staticmethod
    @with_comment(backward_comment=True, forward_comment=False)
    def read_typedef_definition(
        typedef_locrange: str,
    ) -> tuple[FilePos, FilePos, str]:
        """
        Read the typedef definition

        :param typedef_locrange: The typedef location range string
        :return: The typedef start position, typedef end position, and the typedef definition
        """
        start_pos, end_pos, content = DefinitionReader._read_simple_element_definition(
            typedef_locrange, "typedef"
        )
        # we don't need struct definition in typedef, so we remove content inside "{}"
        if "{" in content and "}" in content:
            content = (
                content.split("{")[0].strip() + " " + content.split("}")[-1].strip()
            )
        return start_pos, end_pos, content

    @staticmethod
    @with_comment(backward_comment=True, forward_comment=False)
    def read_simple_composite_definition(
        composite_locrange: str,
    ) -> tuple[FilePos, FilePos, str]:
        """
        Read the simple composite definition

        :param composite_locrange: The composite location range string
        :return: The composite start position, composite end position, and the composite definition
        """
        return DefinitionReader._read_simple_element_definition(
            composite_locrange, "composite"
        )

    @staticmethod
    @with_comment(backward_comment=True, forward_comment=False)
    def read_member_definition(
        member_locrange: str,
    ) -> tuple[FilePos, FilePos, str]:
        """
        Read the member definition

        :param member_locrange: The member location range string
        :return: The member start position, member end position, and the member definition
        """
        return DefinitionReader._read_simple_element_definition(
            member_locrange, "member"
        )

    @staticmethod
    @with_comment(backward_comment=True, forward_comment=False)
    def read_complex_composite_definition(
        composite_locrange: str, member_locranges: tuple[str], is_template: bool = False
    ) -> tuple[FilePos, FilePos, str]:
        """
        Read the complex composite definition

        :param composite_locrange: The composite location range string
        :param member_locranges: The member location range strings, this must be tuple to make the function hashable
        :param is_template: True if the composite is a template composite, False otherwise
        :return: The composite start position, composite end position, and the composite definition
        """
        try:
            start_pos, end_pos = DefinitionReader.parse_locrange(composite_locrange)
        except ValueError:
            logger.error(
                f"Invalid composite definition location range: {composite_locrange}"
            )
            return (None, None, "")

        # unlike simple composite, complex composite includes methods, however we only want attribute members
        # so we firstly get the content before "{" and the content after "}"
        # then we get all the member definitions
        # finally we combine them together

        # find the "template" keyword before the composite definition
        if is_template:
            template_pos = start_pos.find_str("template", is_backward=True)
            if template_pos is not None:
                start_pos = template_pos

        # find the "{" to get the definition start bracket
        brace_open_pos = start_pos.find_str("{")
        if brace_open_pos is None:
            logger.error(
                f"Can not find the start of the composite definition: {composite_locrange}"
            )
            return (None, None, "")
        pre_brace_content = start_pos.get_content_till_pos(brace_open_pos)
        if ";" in pre_brace_content:
            # if there is a semicolon before the brace, this composite has no {}
            semicolon_pos = start_pos.find_str(";")
            return (
                start_pos,
                semicolon_pos,
                start_pos.get_content_till_pos(semicolon_pos).strip() + ";",
            )

        # find the "}" and ";" to get the definition end bracket and semicolon
        while True:
            brace_close_pos = end_pos.find_str("}")
            if brace_close_pos is not None:
                semicolon_pos = brace_close_pos.find_str(";")
                if semicolon_pos is not None:
                    break
            # on error
            logger.error(
                f"Can not find the end of the composite definition: {composite_locrange}"
            )
            return (None, None, "")

        # get property definitions
        member_definitions = ""
        for member_locrange in member_locranges:
            _, _, member_definition = DefinitionReader.read_member_definition(
                member_locrange
            )
            member_definitions += member_definition + "\n"

        # combine the content
        combined_contents = (
            pre_brace_content.strip()
            + "{\n"
            + member_definitions
            + "// ... methods are omitted\n"
            + brace_close_pos.get_content_till_pos(semicolon_pos).strip()
            + ";"
        )

        return (
            start_pos,
            semicolon_pos,
            combined_contents,
        )
