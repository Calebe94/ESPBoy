#include <stdio.h>
#include <stdlib.h>

#include "dynamic_list.h"

void dl_init(dynamic_list_t *v)
{
    v->capacity = LIST_INIT_CAPACITY;
    v->total = 0;
    v->items = malloc(sizeof(void *) * v->capacity);
}

int  dl_length(dynamic_list_t *v)
{
    return v->total;
}

void dl_resize(dynamic_list_t *v, int capacity)
{
    #ifdef DEBUG_ON
    printf("list_resize: %d to %d\n", v->capacity, capacity);
    #endif

    void **items = realloc(v->items, sizeof(void *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void dl_append(dynamic_list_t *v, void *item)
{
    if (v->capacity == v->total)
        dl_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void dl_insert(dynamic_list_t *v, int index, void *item)
{
    if (index < 0 || index >= v->total)
        return;

    if (v->capacity == v->total)
        dl_resize(v, v->capacity * 2);

    v->total++;

    for (int i = index; i < v->total; i++) {
        v->items[i + 1] = v->items[i];
    }

    v->items[index] = item;
}

void dl_set(dynamic_list_t *v, int index, void *item)
{
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}

void *dl_get(dynamic_list_t *v, int index)
{
    if (index >= 0 && index < v->total)
        return v->items[index];
    return NULL;
}

void dl_delete(dynamic_list_t *v, int index)
{
    if (index < 0 || index >= v->total)
        return;

    v->items[index] = NULL;

    for (int i = index; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4)
        dl_resize(v, v->capacity / 2);
}

void dl_pop(dynamic_list_t *v)
{
    int index = v->total - 1;
    if (index < 0 || index >= v->total)
        return;

    v->items[index] = NULL;

    for (int i = index; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4)
        dl_resize(v, v->capacity / 2);
}

void dl_free(dynamic_list_t *v)
{
    free(v->items);
}