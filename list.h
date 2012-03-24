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
#ifndef __LIST_H
#define __LIST_H

#define offsetof(type, member) __builtin_offsetof(type, member)
#define containerof(list, type, member) (type *) ((uintptr_t)list - offsetof(type, member))

struct list {
	struct list *prev;
	struct list *next;
};
typedef struct list list_t;

static inline void list_initialize (list_t *list)
{
	list->next = list->prev = list;
}

static inline int list_is_empty(list_t *list)
{
	return (list->next == list);
}

/* Insertion ops */
static inline void list_add_after(list_t *target, list_t *node)
{
	node->next = target->next;
	node->prev = target;

	target->next = target->next->prev = node;
}

static inline void list_add_head (list_t *list, list_t *node)
{
	list_add_after(list, node);
}

static inline void list_add_tail (list_t *list, list_t *node)
{
	list_add_after(list->prev, node);
}

/* Removal ops */
static inline list_t *list_remove(list_t *list, list_t *target)
{
	if (list == target)
		return NULL;

	target->prev->next = target->next;
	target->next->prev = target->prev;

	target->next = target->prev = NULL;

	return target;
}
	
static inline list_t *list_remove_head (list_t *list)
{
	return list_remove(list, list->next);
}

#define list_remove_head_type(list, type, member)  \
		containerof(list_remove_head(list), type, member)

static inline list_t *list_remove_tail (list_t *list)
{
	return list_remove(list, list->prev);
}

#define list_remove_tail_type(list, type, member)  \
		containerof(list_remove_tail(list), type, member)

/* Iteration ops */
static inline list_t *list_next(list_t *list, list_t *cur)
{
	if (cur->next == list)
		return NULL;

	return cur->next;
}

static inline list_t *list_prev(list_t *list, list_t *cur)
{
	if (cur->prev == list)
		return NULL;
	
	return cur->prev;
}

/* Inspection ops */
static inline list_t *list_peek(list_t *list, list_t *cur)
{
	if (cur == list)
		return NULL;
	
	return cur;
}

#define list_peek_type(list, type, member)  \
		containerof(list_peek(list), type, member)

static inline list_t *list_peek_head(list_t *list)
{
	return list_peek(list, list->next);
}

#define list_peek_head_type(list, type, member)  \
		containerof(list_peek_head(list), type, member)

static inline list_t *list_peek_tail(list_t *list)
{
	return list_peek(list, list->prev);
}

#define list_peek_tail_type(list, type, member)  \
		containerof(list_peek_tail(list), type, member)

/* Iteration */
#define list_foreach(list, type, member, current) \
	for (current = containerof((list)->next, type, member); \
			&(current)->member != list; \
			current = containerof((current)->member.next, type, member))

#define list_foreach_safe(list, type, member, current) \
	for (list_t *__list_iter_tmp = (current = containerof((list)->next, type, member), current->member.next); \
			&(current)->member != list; \
			current = containerof(__list_iter_tmp, type, member), __list_iter_tmp = __list_iter_tmp->next)
		

#endif
