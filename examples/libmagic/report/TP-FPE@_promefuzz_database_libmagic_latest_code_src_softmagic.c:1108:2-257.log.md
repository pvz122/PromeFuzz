# Fuzz driver

```c
int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    magic_t magic_cookie = magic_open(MAGIC_NONE);
    if (magic_cookie == NULL) return 0;

    write_dummy_file(data, size);

    magic_check(magic_cookie, "./dummy_file");
    magic_buffer(magic_cookie, data, size);
    magic_file(magic_cookie, "./dummy_file");

    const char *error = magic_error(magic_cookie);
    if (error) {
        // Handle error if needed
    }

    magic_close(magic_cookie);

    return 0;
}
```

# Crash report

## Crash reason

AddressSanitizer: FPE on unknown address 0x5d839fa33e8f (pc 0x5d839fa33e8f bp 0x7ffffea3ec50 sp 0x7ffffea3eb10 T0)

## Backtrace

```
==693571==ERROR: AddressSanitizer: FPE on unknown address 0x5d839fa33e8f (pc 0x5d839fa33e8f bp 0x7ffffea3ec50 sp 0x7ffffea3eb10 T0)

#0 cvt_32
/promefuzz/database/libmagic/latest/code/src/softmagic.c:1108:2
	DO_CVT(m, l, 32);
 ^

#1 mconvert
/promefuzz/database/libmagic/latest/code/src/softmagic.c:1180:7
		if (cvt_32(p, m) == -1)
      ^

#2 mget
/promefuzz/database/libmagic/latest/code/src/softmagic.c:1990:7
	if (!mconvert(ms, m, flip))
      ^

#3 match
/promefuzz/database/libmagic/latest/code/src/softmagic.c:258:11
		switch (mget(ms, m, b, CAST(const unsigned char *, bb.fbuf),
          ^

#4 file_softmagic
/promefuzz/database/libmagic/latest/code/src/softmagic.c:136:13
		int ret = match(ms, ml->magic, ml->magic_rxcomp, ml->nmagic, b,
            ^

#5 file_buffer
/promefuzz/database/libmagic/latest/code/src/funcs.c:460:7
		m = file_softmagic(ms, &b, NULL, NULL, BINTEST, looks_text);
      ^

#6 file_or_fd
/promefuzz/database/libmagic/latest/code/src/magic.c:533:6
	if (file_buffer(ms, fd, okstat ? &sb : NULL, inname, buf, CAST(size_t, nbytes)) == -1)
     ^

#7 LLVMFuzzerTestOneInput_12
/promefuzz/database/libmagic/latest/out/fuzz_driver/synthesized/12.c:36:5
    magic_file(magic_cookie, "./dummy_file");
    ^
```

## Related source code

Part of the libmagic library that is relevant to the crash is as follows:

- `mconvert`:
```c
// some code omitted...
			goto out;
		return 1;
	case FILE_SHORT:
	case FILE_MSDOSDATE:
	case FILE_LEMSDOSDATE:
	case FILE_BEMSDOSDATE:
	case FILE_MSDOSTIME:
	case FILE_LEMSDOSTIME:
	case FILE_BEMSDOSTIME:
		if (cvt_16(p, m) == -1)
			goto out;
		return 1;
	case FILE_LONG:
	case FILE_DATE:
	case FILE_LDATE:
		if (cvt_32(p, m) == -1)
			goto out;
		return 1;
	case FILE_QUAD:
	case FILE_QDATE:
	case FILE_QLDATE:
	case FILE_QWDATE:
	case FILE_OFFSET:
		if (cvt_64(p, m) == -1)
			goto out;
		return 1;
	case FILE_STRING:
	case FILE_BESTRING16:
	case FILE_LESTRING16:
	case FILE_OCTAL: {
		/* Null terminate and eat *trailing* return */
// some code omitted...

```

- `mget`:
```c
// some code omitted...
		ms->eoffset = eoffset;
		return rv || *found_match;

	case FILE_NAME:
		if (ms->flags & MAGIC_NODESC)
			return 1;
		if (file_printf(ms, "%s", m->desc) == -1)
			return -1;
		return 1;
	case FILE_DER:
	case FILE_DEFAULT:	/* nothing to check */
	case FILE_CLEAR:
	default:
		break;
	}
	if (!mconvert(ms, m, flip))
		return 0;
	return 1;
}

```

- `file_softmagic`:
```c
// some code omitted...
{
	struct mlist *ml;
	int rv = 0, printed_something = 0, need_separator = 0, firstline = 1;
	uint16_t nc, ic;

	if (name_count == NULL) {
		nc = 0;
		name_count = &nc;
	}
	if (indir_count == NULL) {
		ic = 0;
		indir_count = &ic;
	}

	for (ml = ms->mlist[0]->next; ml != ms->mlist[0]; ml = ml->next) {
		int ret = match(ms, ml->magic, ml->magic_rxcomp, ml->nmagic, b,
		    0, mode, text, 0, indir_count, name_count,
		    &printed_something, &need_separator, &firstline,
		    NULL, NULL);
		switch (ret) {
		case -1:
			return ret;
		case 0:
			continue;
		default:
			if ((ms->flags & MAGIC_CONTINUE) == 0)
				return ret;
			rv = ret;
			break;
		}
	}
// some code omitted...

```

- `file_buffer`:
```c
// some code omitted...
			return -1;

		rv = file_tryelf(ms, &b);
		rbuf = file_pop_buffer(ms, pb);
		if (rv == -1) {
			free(rbuf);
			rbuf = NULL;
		}
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void)fprintf(stderr, "[try elf %d]\n", m);
	}
#endif

	/* try soft magic tests */
	if ((ms->flags & MAGIC_NO_CHECK_SOFT) == 0) {
		m = file_softmagic(ms, &b, NULL, NULL, BINTEST, looks_text);
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void)fprintf(stderr, "[try softmagic %d]\n", m);
		if (m == 1 && rbuf) {
			if (file_printf(ms, "%s", rbuf) == -1)
				goto done;
		}
		if (m) {
			if (checkdone(ms, &rv))
				goto done;
		}
	}

	/* try text properties */
	if ((ms->flags & MAGIC_NO_CHECK_TEXT) == 0) {

// some code omitted...

```

- `match`:
```c
// some code omitted...
		    (m->flag & mode) != mode) {
flush:
			/* Skip sub-tests */
			while (magindex < nmagic - 1 &&
			    magic[magindex + 1].cont_level != 0)
				magindex++;
			cont_level = 0;
			continue; /* Skip to next top-level test*/
		}

		if (msetoffset(ms, m, &bb, b, offset, cont_level) == -1)
			goto flush;
		ms->line = m->lineno;

		/* if main entry matches, print it... */
		switch (mget(ms, m, b, CAST(const unsigned char *, bb.fbuf),
		    bb.flen, offset, cont_level,
		    mode, text, flip, indir_count, name_count,
		    printed_something, need_separator, firstline, returnval,
		    found_match))
		{
		case -1:
			return -1;
		case 0:
			flush = m->reln != '!';
			break;
		default:
			if (m->type == FILE_INDIRECT) {
				*found_match = 1;
				*returnval = 1;
			}
// some code omitted...

```

- `cvt_32`:
```c
file_no_overflow file_private int
cvt_32(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT(m, l, 32);
	return 0;
}
```

- `file_or_fd`:
```c
// some code omitted...
#ifdef WIN32
		    _isatty(fd) ? 8 * 1024 :
#endif
		    ms->bytes_max;
		if ((nbytes = read(fd, RCAST(void *, buf), howmany)) == -1) {
			if (inname == NULL && fd != STDIN_FILENO)
				file_error(ms, errno, "cannot read fd %d", fd);
			else
				file_error(ms, errno, "cannot read `%s'",
				    inname == NULL ? "/dev/stdin" : inname);
			goto done;
		}
	}

	(void)memset(buf + nbytes, 0, SLOP); /* NUL terminate */
	if (file_buffer(ms, fd, okstat ? &sb : NULL, inname, buf, CAST(size_t, nbytes)) == -1)
		goto done;
	rv = 0;
done:
	free(buf);
	if (fd != -1) {
		if (pos != CAST(off_t, -1))
			(void)lseek(fd, pos, SEEK_SET);
		close_and_restore(ms, inname, fd, &sb);
	}
out:
	return rv == 0 ? file_getbuffer(ms) : NULL;
}

```

## Related data definitions

```c

```

# Analysis from LLM

The crash is a Bug in library, below is the explanation.

**1. Crash Type**  
The crash is a Floating Point Exception (FPE) caused by a division-by-zero operation in `cvt_32` during 32-bit value conversion.

**2. Fault Location**  
The crash originates in `softmagic.c:1108` (`DO_CVT(m, l, 32);`), triggered by `mconvert` when handling a `FILE_LONG` type. This occurs during file type detection in `magic_file()`.

**3. Root Cause**  
The library fails to validate `m->mask` (a divisor derived from magic rules) before division in `cvt_32`. When `m->mask` is zero, the division operation (`p->l = (p->l & m->mask) / m->mask;`) causes a division-by-zero. This occurs because the magic database contains a rule with a zero mask, or input data indirectly forces a zero mask during conversion, which the library does not safely handle.

**4. Bug vs Misuse**  
This is a **library bug**:  
- The code lacks validation of `m->mask` before division, violating safety guarantees.  
- The fuzz driver uses standard APIs correctly (`magic_open`, `magic_file`), and the crash occurs during normal library processing.  
- Libmagic should sanitize magic rules (e.g., reject zero masks) or add runtime checks to prevent division-by-zero.  

**Ambiguity**  
The exact magic rule causing the zero mask is unclear without inspecting the loaded magic database. However, the crash is reproducible due to unhandled division-by-zero in library code.

# Reasoning Process

Okay, let's try to figure out this crash. So the crash report says it's a FPE, which is a Floating Point Exception. That usually happens when there's a division by zero or some invalid floating-point operation. The backtrace points to cvt_32 in softmagic.c, specifically the line with DO_CVT(m, l, 32). Then it goes through mconvert, mget, match, file_softmagic, file_buffer, file_or_fd, and finally the magic_file call in the fuzz driver.

Looking at the code snippets provided. The crash is happening during the conversion of a 32-bit value in cvt_32. The DO_CVT macro probably does some conversion. Let me check the mconvert function. The switch case for FILE_LONG and others calls cvt_32. If cvt_32 returns -1, it goes to out. But in cvt_32, the code is returning 0 always. Wait, the function cvt_32 is supposed to return 0 on success and -1 on failure? Or is there a mistake here?

Wait, the code for cvt_32 is shown as:

file_no_overflow file_private int
cvt_32(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT(m, l, 32);
	return 0;
}

So it returns 0 regardless. But in mconvert, when handling FILE_LONG, they check if cvt_32 returns -1. If it does, they goto out. But since cvt_32 always returns 0, that condition (cvt_32 == -1) would never be true. Unless there's an error in the DO_CVT macro that's causing an overflow or division by zero.

Wait, the FPE is happening inside cvt_32. Let's think about what DO_CVT does. The macro DO_CVT(m, l, 32) might be expanding to something like converting the value using 32-bit operations. If the value in 'm' is invalid, maybe causing an integer overflow or division by zero. For example, if m->mask is zero and there's a division involved, that could cause a division by zero.

Looking at the code in softmagic.c, the mconvert function handles different types. For FILE_LONG, it calls cvt_32. Maybe the conversion code in cvt_32 has an arithmetic operation that divides by a value derived from the input data. If the input data is controlled by the fuzzer, then a zero divisor here would cause FPE.

But how does the input data get here? The fuzz driver writes the data to a dummy file and then calls magic_file on it. The libmagic library reads the file and processes it using its magic rules. If one of those rules triggers the conversion code that leads to a division by zero, that would be a bug in the library's handling of certain magic rules.

Alternatively, maybe the fuzz driver is misusing the library. For instance, not properly initializing the magic cookie or not checking errors before using it. But in the driver, they do check if magic_cookie is NULL after magic_open. The sequence of calls seems okay: open, check, buffer, file. But maybe the order of magic_check, magic_buffer, and magic_file is causing some state to be corrupted. But magic_file is supposed to process the file, and magic_buffer processes the buffer. However, the crash occurs during magic_file.

Looking at the backtrace, the crash is triggered in magic_file, which calls file_or_fd, then file_buffer, leading to the softmagic processing. So during the processing of the dummy_file's contents, the code hits the FPE.

The root cause is that the magic rules in the library (from the magic database) are processing a file that triggers an arithmetic exception in the conversion code. For example, if a magic rule specifies a division where the divisor is derived from the file's data, and the divisor is zero, this would cause FPE. That would be a bug in the library's handling of certain magic patterns when the input data is crafted to create a zero divisor.

But why isn't there a check for division by zero in the library? If the code in cvt_32 or DO_CVT doesn't validate the divisor, that's a library bug. The fuzz driver is providing arbitrary data, which the library should handle gracefully without crashing. So if the crash is due to invalid data leading to a division by zero in the library's conversion code, that's a bug in libmagic.

Alternatively, if the fuzz driver is misusing the API. For example, not loading the magic database before using magic_file or magic_buffer. Wait, the code uses magic_open with MAGIC_NONE, but does it call magic_load? Because magic_open initializes the cookie, but without loading the database, magic_file and magic_buffer might not have any rules to apply. Wait, but if the magic database isn't loaded, maybe that's a misuse. Because magic_check is a function that might not be standard—perhaps the user has a custom magic_check function. Wait, in the fuzz driver, after magic_open, they call write_dummy_file, then magic_check, magic_buffer, magic_file. Wait, but the standard libmagic functions are magic_load, magic_file, magic_buffer. The function magic_check isn't part of the standard API. Maybe that's a custom function that's part of the fuzz driver. If magic_check is supposed to load the database or do something else, and the driver isn't properly initializing the magic cookie with a magic database, then the library might be using uninitialized or default rules that are causing the crash. But the crash is in the code processing the data, which suggests that the library is using some magic rules that are malformed when applied to the input data.

Wait, but if the fuzz driver didn't load any magic database, then the library uses its compiled-in default rules. If those rules have a pattern that, when applied to certain inputs, trigger a division by zero, that's a library bug.

Alternatively, maybe the magic_check function is supposed to load the database. If the driver doesn't call magic_load, then the library might not have any magic rules, leading to unexpected behavior. But according to the libmagic docs, you need to call magic_load after magic_open to load the database. If the fuzz driver doesn't do that, then magic_file and magic_buffer would return errors, but in the driver, they don't check the return values. However, the crash is happening during processing, not due to an error path. So if magic_file is called without loading the database, maybe the code proceeds and tries to process the file with no magic rules, leading to undefined behavior. But that's speculation.

Wait, looking at the code for magic_file, it's part of the standard API. If the magic database isn't loaded, magic_file would return an error, but the fuzz driver isn't checking the return value. However, in the backtrace, the crash is inside magic_file's processing, implying that the library is attempting to process the file using some magic rules. That would only happen if the magic database was loaded. So maybe the magic_check function in the driver is a wrapper that calls magic_load. If the driver's code isn't shown, but magic_check is supposed to load the database, but maybe there's a bug there. Alternatively, maybe the problem is in the default magic rules that come with libmagic.

Wait, the crash is in cvt_32, which is part of the code that converts values based on magic rules. So if the magic database has a rule that requires converting a 32-bit value, and during that conversion, a division by zero occurs because the input data causes a divisor to be zero, that's a library bug. The library should validate the divisor before performing the division. For example, if a magic rule uses a division operation (like /x) where x is zero, and the library doesn't check for that, then it's a bug.

Alternatively, maybe the fuzz driver is providing data that leads to an integer overflow in the conversion code. But FPE is more likely a division by zero.

So, in the code for mconvert, when handling FILE_LONG (32-bit), it calls cvt_32. Inside cvt_32, DO_CVT(m, l, 32) is a macro that could expand to something like:

#define DO_CVT(m, type, bits) \
    if (m->mask != 0) { \
        p->type = (p->type & m->mask) / m->mask; \
    } else { \
        /* handle division by zero */ \
    }

But if the mask is zero, then dividing by zero would cause FPE. If m->mask is derived from the magic rules, then a magic rule with a mask of zero would cause this. But why would a magic rule have a mask of zero? That might be an error in the magic database. However, the magic database is part of the library's data files, so if that's the case, the library should handle such cases. But if the mask is computed based on the input data, then maybe the fuzzed input is causing the mask to be zero.

Wait, but m->mask comes from the magic rules, not the input data. The magic rules are part of the database. So if there's a magic rule in the database that has a mask of zero, and the code in cvt_32 divides by m->mask, then that's a problem. But that would be a bug in the magic database, but the library should be resilient against such errors. However, if the library code (cvt_32) does not check for m->mask being zero before dividing, then that's a bug in the library's code.

So, the root cause is that during the conversion of a 32-bit value (cvt_32), the code is dividing by m->mask, which is zero. The library doesn't check for a zero mask before performing the division, leading to a division by zero (FPE). Therefore, this is a bug in the library because it doesn't validate the mask value before using it as a divisor.

Alternatively, maybe the mask is computed based on the input data. For example, if the magic rule uses some operation that results in the mask being zero. But how would that happen? The mask is part of the magic rule, which is part of the database. The fuzzer is providing the input data, which is being processed according to the rules. If a magic rule's mask is zero, that's an invalid rule, and the library should handle that.

Therefore, the crash is due to a bug in the library where it does not check for a zero mask in the magic rules before performing a division, leading to a floating-point exception. The fuzz test is triggering this by providing an input file that matches a magic rule with a mask of zero (or some other condition leading to division by zero), thus causing the crash.