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
#ifndef __UNITS_H
#define __UNITS_H
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

extern list_t test_list;
struct test_entry {
	unsigned int (*func)(void);
	list_t node;
};
typedef struct test_entry entry_t;
typedef unsigned int units_test_t;

static inline void _add_test(units_test_t (*func)(void))
{

	entry_t *test = malloc(sizeof(entry_t));
	test->func = func;
	list_add_tail(&test_list, &test->node);
}

#define start_tests __attribute__((constructor)) static void test_initializer (void) {
#define add_test(func) _add_test(func);
#define end_tests }
#define test_pass \
	do { \
		printf("%s: PASS\n", __func__); \
		return 0; \
	} while (0)
#define test_fail(value, string) \
	do { \
		printf("%s: FAIL (error %d: %s)\n", __func__, value, string); \
		return value; \
	} while (0);

#endif
