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
#include <stdint.h>
#include <string.h>

/* Units specific units_list implementation */
struct units_list {
	struct units_list *prev;
	struct units_list *next;
};
typedef struct units_list units_list_t;

static inline void units_list_initialize (units_list_t *units_list)
{
	units_list->next = units_list->prev = units_list;
}

static inline int units_list_is_empty(units_list_t *units_list)
{
	return (units_list->next == units_list);
}
static inline void units_list_add_after(units_list_t *target, units_list_t *node)
{
	node->next = target->next;
	node->prev = target;

	target->next = target->next->prev = node;
}

static inline units_list_t *units_list_remove(units_list_t *units_list, units_list_t *target)
{
	if (units_list == target)
		return NULL;

	target->prev->next = target->next;
	target->next->prev = target->prev;

	target->next = target->prev = NULL;

	return target;
}

static inline units_list_t *units_list_remove_head (units_list_t *list)
{
	return units_list_remove(list, list->next);
}

#define units_list_remove_head_type(list, type, member)  \
		containerof(units_list_remove_head(list), type, member)
	
/* test code */
extern units_list_t test_list;
extern int units_test_cnt;

typedef struct {
	unsigned int value;
	const char *buf;
	int len;
} return_t;

typedef return_t * units_test_t;

typedef struct {
	return_t *(*func)(void);
	units_list_t node;
} entry_t;



static inline void _add_test(units_test_t (*func)(void))
{

	entry_t *test = malloc(sizeof(entry_t));
	test->func = func;
	units_list_add_after(test_list.prev, &test->node);
	units_test_cnt++;
}

static inline return_t *test_result (unsigned int value, const char *buf)
{
	return_t *ret = malloc(sizeof(return_t));
	ret->value = value;
	
	ret->buf = buf; 
	if (buf)
		ret->len = strlen(ret->buf); 
	else
		ret->len = 0; 
	return ret; 
}

#define test_pass return test_result(0, NULL)
#define test_pass_v(string) return test_result(0, string)
#define test_fail(x, y) return test_result(x, y)

#define start_tests __attribute__((constructor)) static void units_test (void) {
#define add_test(x) _add_test(x); // Just to keep ; usage consistent
#define end_tests }

#endif
