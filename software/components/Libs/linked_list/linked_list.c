#include <stdlib.h>
#include <k_config.h>
#include "linked_list.h"

void linked_list_init(linked_list_t **list){
    (*list) = NULL;
}

err_t linked_list_is_empty(linked_list_t **list){
    if((*list)->next==NULL)    return RESP_OK;
    else                    return RESP_FAIL;
}

err_t linked_list_append(linked_list_t **list, void *data){
    linked_list_t *new = (linked_list_t*)malloc(sizeof(linked_list_t));
    if(new == NULL)     return RESP_FAIL;
    new->data = data;
    new->next = *list;
    *list = new;
    return RESP_OK;
}

err_t linked_list_insert(linked_list_t **list, void *data){
    linked_list_t *new = NULL, *actual = NULL;
    new = (linked_list_t*)malloc(sizeof(linked_list_t));
    if(new == NULL)     return RESP_FAIL;
    new->data = data;
    new->next = NULL;

    if(*list == NULL)   *list = new;
    else{
        actual = *list;
        while(actual->next != NULL){
            actual = actual->next;
        }
        actual->next = new;
    }
    return RESP_OK;
}
err_t linked_list_pop(linked_list_t **list){
    if(*list == NULL)   return RESP_FAIL;
    else{
        linked_list_t *actual;
        actual = *list;
        *list = (*list)->next;
        free(actual);
    }
    return RESP_OK;
}
err_t linked_list_remove(linked_list_t **list){
    if(*list == NULL)   return RESP_FAIL;
    else{
        linked_list_t *actual = NULL, *previous = NULL;
        actual = *list;
        while(actual->next != NULL){
            previous = actual;
            actual = actual->next;
        }
        previous->next = NULL;
        free(actual);
    }
    return RESP_OK;
}
