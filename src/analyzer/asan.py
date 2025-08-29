"""
Parse ASan error
"""

from loguru import logger
from pathlib import Path
from functools import cached_property
from parse import search
from dataclasses import dataclass
import re

from src.utils import is_source_file, FilePos


@dataclass
class AsanTrace:
    """
    Class for an ASan trace message, it is like:
    ```
        #1 0x633f0e3fe58b in LLVMFuzzerTestOneInput /root/path/promefuzz/database/ngiflib/75b9920/out/test/./driver25.c:13:9
    ```
    """

    number: int
    """
    The number of the trace
    """

    address: str
    """
    The hex address of the trace
    """

    function: str
    """
    The function of the trace
    """

    location: str
    """
    The location of the trace
    """

    @classmethod
    def from_msg(cls, msg: str):
        """
        Parse the ASan trace message

        :param msg: The ASan trace message
        :return: The parsed ASan trace
        """
        msg = msg.strip()
        # fields to parse
        number = None
        address = None
        function = None
        location = None

        # There are three patterns of ASan trace message:
        # - #{number} {address} in {function} {location}
        # - #{number} {address} in {function} ({location}) (BuildId: {build_id})
        # - #{number} {address} ({location}) (BuildId: {build_id})

        def parse_number(msg: str) -> str:
            nonlocal number
            # find "#"" to " "
            start, end = msg.find("#"), msg.find(" ")
            if start == -1 or end == -1:
                raise ValueError(
                    f"Failed to parse number field in ASan trace message: {msg}"
                )
            number = int(msg[start + 1 : end])
            return msg[end + 1 :].strip()

        def parse_address(msg: str) -> str:
            nonlocal address
            # find "0x" to " "
            start, end = msg.find("0x"), msg.find(" ")
            if start == -1 or end == -1:
                raise ValueError(
                    f"Failed to parse address field in ASan trace message: {msg}"
                )
            address = msg[start:end]
            return msg[end + 1 :].strip()

        def parse_func_loc_pattern_1(msg: str) -> str:
            nonlocal function, location
            # pattern 1:
            # in {function} {location}
            msg = msg.removeprefix("in ")
            # find the first "/", then find " " just before it
            # the location is from this " " to the end of the string
            loc_start = msg.find("/")
            if loc_start == -1:
                loc_start = len(msg) - 1
            loc_start = msg.rfind(" ", 0, loc_start)
            if loc_start == -1:
                raise ValueError(
                    f"Failed to parse function field in ASan trace message: {msg}"
                )
            location = msg[loc_start + 1 :].strip()
            function = msg[:loc_start].strip()
            return ""

        def parse_func_loc_pattern_2(msg: str) -> str:
            nonlocal function, location
            # pattern 2:
            # in {function} ({location}) (BuildId: {build_id})

            # remove (BuildId: {build_id})
            msg = msg.split("(BuildId:")[0].strip()
            # remove "in "
            msg = msg.removeprefix("in ")
            if not msg.endswith(")"):
                raise ValueError(
                    f"Failed to parse location field in ASan trace message: {msg}"
                )
            # find the matching "(" of the last ")"
            unmatched = 1
            for i in range(len(msg) - 2, -1, -1):
                if msg[i] == "(":
                    unmatched -= 1
                elif msg[i] == ")":
                    unmatched += 1
                if unmatched == 0:
                    break
            if unmatched != 0:
                raise ValueError(
                    f"Failed to parse location field in ASan trace message: {msg}"
                )
            location = msg[i + 1 : -1].strip()
            function = msg[:i].strip()
            return ""

        def parse_func_loc_pattern_3(msg: str) -> str:
            nonlocal function, location
            # pattern 3:
            # ({location}) (BuildId: {build_id})

            # remove (BuildId: {build_id})
            msg = msg.split("(BuildId:")[0].strip()
            if not msg.endswith(")"):
                raise ValueError(
                    f"Failed to parse location field in ASan trace message: {msg}"
                )
            location = msg[1:-1].strip()
            function = "<unknown function>"
            return ""

        # parse the message
        msg = parse_address(parse_number(msg))
        if msg.startswith("in "):
            if msg.endswith(")"):
                msg = parse_func_loc_pattern_2(msg)
            else:
                msg = parse_func_loc_pattern_1(msg)
        else:
            msg = parse_func_loc_pattern_3(msg)

        return cls(
            number=number,
            address=address,
            function=function,
            location=location,
        )

        # Deprecated code using regex
        # pattern_1 = r'#(?P<number>\d+)\s+(?P<address>0x[0-9a-fA-F]+)\s+in\s+(?P<function>[^/\d]+)(?P<location>.+)'
        # pattern_2 = r"#(?P<number>\d+)\s+0x(?P<address>[a-fA-F0-9]+)\s+in\s+(?P<function>[a-zA-Z0-9:]+(?:[a-zA-Z0-9<>*,&_]*\([^)]*\))?)\s+\((?P<location>[^)]+)\)\s+\(BuildId:\s+(?P<build_id>[a-fA-F0-9]+)\)"
        # pattern_3 = r"#(?P<number>\d+)\s+0x(?P<address>[a-fA-F0-9]+)\s+\((?P<location>[^)]+)\)\s+\(BuildId:\s+(?P<build_id>[a-fA-F0-9]+)\)"
        # match = re.match(pattern_2, msg)
        # if not match:
        #     match = re.match(pattern_1, msg)
        #     if not match:
        #         match = re.match(pattern_3, msg)
        #         if not match:
        #             raise ValueError(f"Failed to parse ASan trace message: {msg}")

        # # function may be empty, so we need to check it
        # try:
        #     function_match = match.group("function").strip()
        # except:
        #     function_match = "<unknown function>"

        # return cls(
        #     number=int(match.group("number")),
        #     address=match.group("address").strip(),
        #     function=function_match,
        #     location=match.group("location").strip(),
        # )

    @property
    def file_pos(self) -> FilePos | None:
        """
        The file position of the trace

        :return: The file position, or None if location is not a file position
        """
        try:
            return FilePos.from_location_line(self.location)
        except:
            return None


@dataclass
class AsanTraceback:
    """
    Class for an ASan traceback message, it is like:
    ```
    READ of size 1 at 0x5020000003b1 thread T0
        #0 0x633f0e3ff817 in CheckGif /root/path/promefuzz/database/ngiflib/75b9920/build_asan/ngiflib.c:383:23
        #1 0x633f0e3fe58b in LLVMFuzzerTestOneInput /root/path/promefuzz/database/ngiflib/75b9920/out/test/./driver25.c:13:9
        #2 0x633f0e30bd24 in fuzzer::Fuzzer::ExecuteCallback(unsigned char const*, unsigned long) (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x4ed24) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
        #3 0x633f0e30b419 in fuzzer::Fuzzer::RunOne(unsigned char const*, unsigned long, bool, fuzzer::InputInfo*, bool, bool*) (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x4e419) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
        #4 0x633f0e30cc05 in fuzzer::Fuzzer::MutateAndTestOne() (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x4fc05) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
        #5 0x633f0e30d765 in fuzzer::Fuzzer::Loop(std::vector<fuzzer::SizedFile, std::allocator<fuzzer::SizedFile>>&) (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x50765) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
        #6 0x633f0e2faa3f in fuzzer::FuzzerDriver(int*, char***, int (*)(unsigned char const*, unsigned long)) (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x3da3f) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
        #7 0x633f0e3250c6 in main (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x680c6) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
        #8 0x7101d5c2a1c9 in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
        #9 0x7101d5c2a28a in __libc_start_main csu/../csu/libc-start.c:360:3
        #10 0x633f0e2efa24 in _start (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x32a24) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
    ```
    """

    description: str
    """
    The description of the traceback, as shown in the first line
    """

    traces: list[AsanTrace]
    """
    The traces of the traceback
    """

    @classmethod
    def from_msg(cls, msg: str):
        """
        Parse the ASan traceback message

        :param msg: The ASan traceback message
        :return: The parsed ASan traceback
        """

        description = ""
        traces = []
        for line_num, line in enumerate(msg.strip().splitlines()):
            if line_num == 0:
                description = line
                continue
            try:
                trace = AsanTrace.from_msg(line)
                traces.append(trace)
            except Exception as e:
                logger.error(e)

        return cls(description=description, traces=traces)


class AsanError:
    """
    Class to represent an ASan error.
    """

    def __init__(self, err_msg: str):
        """
        Initialize the ASan error.
        """
        self.err_msg = err_msg
        if not self.error_reason:
            raise ValueError("No error reason found in the ASan error message")

    @cached_property
    def signature(self) -> str:
        """
        The crash signature, consists of the error reason and the crash position in the traceback,
        used to identify the same crash in different fuzz drivers.
        """
        # We identify a crash by its reason and the crash position in the traceback
        reason = self.error_reason
        if "LeakSanitizer" in reason:
            # It is like: LeakSanitizer: detected memory leaks
            reason = "memory-leak"
        elif "attempting double-free" in reason:
            # It is like: AddressSanitizer: attempting double-free on 0x504000001cd0 in thread T0
            reason = "double-free"
        elif "exceeds maximum supported size" in reason:
            # It is like: AddressSanitizer: requested allocation size 0xffffffffffffffc4 (0x7c8 after adjustments for alignment, red zones etc.) exceeds maximum supported size of 0x10000000000 (thread T0)
            reason = "bad-alloc"
        elif "AddressSanitizer:" in reason:
            # It is like: AddressSanitizer: heap-use-after-free on address 0x603e0001fc64 at pc 0x417f6a bp 0x7fff626b3250 sp 0x7fff626b3248
            reason = reason.split("AddressSanitizer:")[1].strip().split(" ")[0]
        elif "libFuzzer:" in reason:
            # It is like: libFuzzer: out-of-memory (malloc(2708508608))
            reason = reason.split("libFuzzer:")[1].strip().split(" ")[0]
        else:
            logger.warning(f"Unknown ASan error reason: {reason}")
            reason = "unknown"

        def _get_file_from_non_source_trace(
            trace: AsanTrace,
        ) -> Path | None:
            """
            Get the file from a non-source trace, like:
            ```
            #4 0x633f0e30cc05 in fuzzer::Fuzzer::MutateAndTestOne() (/root/path/promefuzz/database/ngiflib/75b9920/out/test/driver25+0x4fc05) (BuildId: 9a9f99affde95b57bc6113a739fc7b05472ef08e)
            ```
            """
            return Path(trace.location.split("+")[0]) if "+" in trace.location else None

        # find the source position
        for tb in self.tracebacks:
            for t in tb.traces:
                pos = t.file_pos
                if pos is not None and is_source_file(pos.file):
                    return f"{reason}@{str(pos).replace('/', '_')}"
                elif pos is None and is_source_file(_get_file_from_non_source_trace(t)):
                    return f"{reason}@{t.location.replace('/', '_')}"

        # no source position found, maybe it is a fuzz driver crash
        if (
            len(self.tracebacks) > 0
            and len(self.tracebacks[0].traces) > 0
            and (
                "sanitizing" in self.tracebacks[0].traces[0].location
                or "driver.cpp" in self.tracebacks[0].traces[0].location
            )
        ):
            return f"{reason}@driver"

        # can not find source position
        logger.warning(f"Cannot find source position in ASan error: \n{self.err_msg}")
        return f"{reason}@unknown"

    @cached_property
    def error_reason(self) -> str | None:
        """
        The error reason of ASan error message, as shown in title like:
        ```
        ==3695993==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x5020000003b1 at pc 0x633f0e3ff818 bp 0x7fff33707d10 sp 0x7fff33707d08
        ```

        :return: The error reason, or None if parsing failed
        """
        # Parse =={digit}==ERROR: {reason}\n
        err_reason = search("=={:d}==ERROR: {reason}\n", self.err_msg)
        if err_reason is None:
            # try another pattern (This space is stupid, but there are really some cases like this)
            err_reason = search("=={:d}== ERROR: {reason}\n", self.err_msg)
            if err_reason is None:
                return None

        return err_reason["reason"]

    @cached_property
    def tracebacks(self) -> list[AsanTraceback]:
        """
        The tracebacks of ASan error message
        """
        traceback_msgs = re.finditer(r"\n.+\n(\s+#\d+ 0x.+ .+\n)+\n", self.err_msg)
        tracebacks = [
            AsanTraceback.from_msg(traceback.group()) for traceback in traceback_msgs
        ]
        if tracebacks:
            return tracebacks
        else:
            e = f"No tracebacks found in the ASan error message:\n{self.err_msg}"
            logger.error(e)
            return []

    @property
    def readable(self) -> str:
        """
        The readable error message.
        """
        readable = self.error_reason + "\n\n"
        for traceback in self.tracebacks:
            readable += traceback.description + "\n"
            have_file_pos = False
            for trace in traceback.traces:
                if trace.file_pos:
                    have_file_pos = True
                    readable += f"{str(trace.file_pos)}\n"
                    readable += f"{trace.file_pos.line:>6}|{trace.file_pos.cur_line}\n"
                    readable += f"{' ' * 6}|{' ' * (trace.file_pos.col - 1)}^\n"

            if not have_file_pos:
                # if there is no valid source file position to print, give a hint
                readable += f"{' ' * 6}| traceback not related to source code\n"
            readable += "\n"

        return readable
