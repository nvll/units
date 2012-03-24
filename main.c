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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "units.h"

#define offsetof(type, member) __builtin_offsetof(type, member)
#define containerof(list, type, member) (type *) ((uintptr_t)list - offsetof(type, member))

units_list_t test_list;

__attribute__((constructor)) void test_units_list_init(void)
{
	units_list_initialize(&test_list);
}

int main (int argc, char *argv[])
{
	int pid, status;
	unsigned int pass = 0, fail = 0;

	while (!units_list_is_empty(&test_list)) {
		entry_t *test = units_list_remove_head_type(&test_list, entry_t, node);
		pid = fork();
		if (pid) {
			wait(&status);
			if (WEXITSTATUS(status) == 0)
				pass++;
			else
				fail++;
		} else {
			exit(test->func());
		}
	}
	
	int total = pass + fail;
	printf("%d %s run, %d/%d passed\n", total, (total == 1) ? "test" : "tests", pass, total);
	
	return fail;
}
