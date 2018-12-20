#ifndef _CIRCULAR_LINKED_LIST_H_
#define _CIRCULAR_LINKED_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

    /**
     * @brief A node holds a pointer to the user-defined
     * element required to be stored, a pointer to
     * the next element in the list, and a pointer to
     * the previous element in the list.
     */
    typedef struct node_t
    {
        void*		element;
        struct node_t*	next;
        struct node_t*	prev;
    } node_t;

    /**
     * @brief Definition of the circular doubly linked-list.
     * It holds informations about the current size
     * of the list, a pointer to the head node of the list,
     * and a pointer to the tail of the list.
     */
    typedef struct list_t
    {
        size_t		size;
        struct node_t*	head;
        struct node_t*	tail;
    } circ_list_t;

    /**
     * @brief Creates a new instance of a `list_t`.
     * @return a pointer to the created list.
     */
    circ_list_t*	cll_create();

    /**
     * @brief Same as `list_create` except no dynamic
     * allocation on the heap will be perform to create
     * the list.
     * @return a circ_list_t value
     */
    circ_list_t	cll_create_static();

    /**
     * @brief Clears the list by deleting every node in it.
     * The list will still be usable after this call.
     */
    void		cll_clear(circ_list_t* list);

    /**
     * @brief Destroys every element of the given `list` and
     * frees the memory allocated by the `list`. The given pointer
     * will not be usable after a call to this function.
     */
    void		cll_destroy(circ_list_t* list);

    /**
     * @brief Adds a new element to the `list`. This will cause a new `node_t`
     * to be created, holding the given `element` and pushed at the front of the
     * given `list`.
     * @return a pointer to the newly created node.
     */
    node_t*	cll_push_front(circ_list_t* list, void* element);

    /**
     * @brief Adds a new element to the `list`. This will cause a new `node_t`
     * to be created, holding the given `element` and pushed to the back of the
     * given `list`.
     * @return a pointer to the newly created node.
     */
    node_t*	cll_push_back(circ_list_t* list, void* element);

    /**
     * @brief Searches the list for the given `node`.
     * @return the found node if any, NULL otherwise.
     */
    node_t*	cll_find_node(const circ_list_t* list, const node_t* node);

    /**
     * @brief Removes the given `node` from the `list`
     * and frees the memory allocated by the `node`.
     * @return a positive value if the given `node` has
     * been successfully removed from the `list`, a negative
     * value otherwise.
     */
    int		  cll_remove_node(circ_list_t* list, node_t* node);

    /**
     * @return the size of the given `list`. That is, the number of nodes currently
     * held by the list.
     */
    size_t  cll_get_size(const circ_list_t* list);

    /**
     * @return a positive value if the given `list` is
     * empty, zero otherwise.
     */
    int     cll_is_empty(const circ_list_t* list);

    /**
     * @brief Removes the node associated with the given node pointer
     * from the list.
     * @return the pointer held by the removed node.
     */
    void*		cll_pop_node(circ_list_t* list, node_t* node);

    /**
     * @brief Removes the node located at the head of the list.
     * @return the pointer held by the removed node.
     */
    void*		cll_pop_back(circ_list_t* list);

    /**
     * @brief Removes the node located at the tail of the list.
     * @return the pointer held by the removed node.
     */
    void*		cll_pop_front(circ_list_t* list);

    node_t* cll_get_next(circ_list_t* list);

    node_t* cll_get_previous(circ_list_t* list);

    void* cll_get_actual(circ_list_t* list);

    void cll_goto_head(circ_list_t* list);
    void cll_goto_tail(circ_list_t* list);

    /**
     * @brief Creates a new node instance initialized
     * with the given `element`.
     * @return a new instance of a `node_t`.
     */
    node_t*	cll_node_new(void* element);

#ifdef __cplusplus
}
#endif

#endif
