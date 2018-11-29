/*
 *  This file is a part of libacars
 *
 *  Copyright (c) 2018 Tomasz Lemiech <szpajder@gmail.com>
 */
#ifndef LA_LIST_H
#define LA_LIST_H 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct la_list la_list;

struct la_list {
	void *data;
	la_list *next;
};

la_list *la_list_next(la_list const * const l);
la_list *la_list_append(la_list *l, void *data);
size_t la_list_length(la_list const *l);
void la_list_foreach(la_list *l, void (*cb)(), void *ctx);
void la_list_free(la_list *l);
void la_list_free_full(la_list *l, void (*node_free)());

#ifdef __cplusplus
}
#endif

#endif // !LA_LIST_H
