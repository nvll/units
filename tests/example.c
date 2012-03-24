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
#include "list.h"

typedef struct {
	int value;
	list_t node;
} list_entry_t;

static units_test_t test_list_init (void)
{
	list_t list;

	list_initialize(&list);
	if (!list_is_empty(&list))
		test_fail(1, "list not initialized properly");
	
	test_pass;
}

static units_test_t test_list_insert (void)
{
	list_t list;
	list_entry_t entry;
	list_entry_t *returned;

	entry.value = 17;
	
	list_initialize(&list);
	list_add_head(&list, &entry.node);

	returned = list_peek_head_type(&list, list_entry_t, node);

	if (returned->value != entry.value)
		test_fail(1, "peeked entry does not match the one inserted");
	
	returned = list_remove_tail_type(&list, list_entry_t, node);
	
	if (returned->value != entry.value)
		test_fail(2, "removed tail entry does not match the one inserted");

	if (!list_is_empty(&list))
		test_fail(3, "list is not empty after removing sole element");

	test_pass;
}

start_tests
add_test(test_list_init)
add_test(test_list_insert)
end_tests

