#ifndef _DYNAMIC_LIST_H_
#define _DYNAMIC_LIST_H_

#define LIST_INIT_CAPACITY 4 

#define DL_INIT(list) list_t list; list_init(&list)
#define DL_APPEND(list, item) list_append(&list, (void *) item)
#define DL_SET(list, id, item) list_set(&list, id, (void *) item)
#define DL_GET(list, type, id) (type) list_get(&list, id)
#define DL_DELETE(list, id) list_delete(&list, id)
#define DL_POP(list) list_pop(&list)
#define DL_LENGTH(list) list_length(&list)
#define DL_FREE(list) list_free(&list)
#define DL_INSERT(list, id, item) list_insert(&list, id, (void *) item)

typedef struct vector {
    void **items;
    int capacity;
    int total;
} dynamic_list_t;

void dl_init(dynamic_list_t *);
int  dl_length(dynamic_list_t *);
void dl_resize(dynamic_list_t *, int);
void dl_append(dynamic_list_t *, void *);
void dl_insert(dynamic_list_t *, int, void *);
void dl_set(dynamic_list_t *, int, void *);
void *dl_get(dynamic_list_t *, int);
void dl_delete(dynamic_list_t *, int);
void dl_pop(dynamic_list_t *);
void dl_free(dynamic_list_t *);

#endif