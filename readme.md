Units
=====

Units is simple / dynamic unit testing framework for C (and C++, I suppose). 

###Main features:
- Lightweight
- Tests are sandboxed, but can share functions in their own files
- There is no global configuration. All tests are completely contained within their own file, no registration needed.
- It should run on any unix system with a somewhat recent version of GCC (tested on 4.2 and 4.6)
- Output is TAP compliant

###Writing tests
See example.c. Each function is called individually as its own test if included with add_test. Tests are sandboxed in
child processes so there is no memory sharing between them.

###Running tests
Running tests is easy. For most projects you can simply drop a .c in the tests directory, build and run:

	user@host:~/code/units$ make
	compiling main.c
	compiling tests/example.c
	linking runtests
	user@host:~/code/units$ ./runtests 
	1..4
	ok 1 - always_passing
	not ok 2 - always_failing
	not ok 3 - fail_with_output
		this is a string with
		linebreaks
		in the failure output
	ok 4 - pass_with_output
		everything went better than expected
	# 4 tests run, 2/4 passed 

Example of running the example tests via `prove`:

	user@host:~/code/units$ prove -e '' -v ./runtests 
	./runtests .. 
	1..4
	ok 1 - always_passing
	not ok 2 - always_failing
	not ok 3 - fail_with_output
		this is a string with
		linebreaks
		in the failure output
	ok 4 - pass_with_output
		everything went better than expected
	# 4 tests run, 2/4 passed
	Dubious, test returned 2 (wstat 512, 0x200)
	Failed 2/4 subtests 
	
	Test Summary Report
	-------------------
	./runtests (Wstat: 512 Tests: 4 Failed: 2)
  	Failed tests:  2-3
  	Non-zero exit status: 2
	Files=1, Tests=4,  0 wallclock secs ( 0.03 usr +  0.00 sys =  0.03 CPU)
	Result: FAIL
