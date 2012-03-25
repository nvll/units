/*
 * Copyright (c) 2012, Christopher Anderson
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */  
#include "units.h"

static units_test_t always_passing (void)
{	
	int x = 3, y = 7;

	if (x + y == 10)
		test_pass;
	
	test_fail_v("mathematics do not work");
}

static units_test_t always_failing (void)
{
	test_fail;
}

static units_test_t fail_with_output (void)
{
	const char *output = "this is a string with\nlinebreaks\nin the failure output";
	test_fail_v(output);
}

static units_test_t pass_with_output (void)
{
	test_pass_v("everything went better than expected");
}

start_tests
add_test(always_passing)
add_test(always_failing)
add_test(fail_with_output)
add_test(pass_with_output)
end_tests

