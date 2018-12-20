/*
Library highly based on "circular-linked-list" from HQarroum and these tutorials:

* https://br.ccm.net/faq/10226-listas-circulares-ring-buffer#lista-circ-c
* https://pt.wikibooks.org/wiki/Programar_em_C/Listas_encadeadas#Lista_encadeada_linear
*/
#include "circular_linked_list.h"

/**
 * @brief Creates a new instance of a `circ_list_t`.
 * @return a pointer to the created list.
 */
circ_list_t*	cll_create()
{
  circ_list_t*	list;
    
  list = malloc(sizeof(*list));
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return (list);
}

/**
 * @brief Same as `list_create` except no dynamic
 * allocation on the heap will be perform to create
 * the list.
 * @return a circ_list_t value
 */
circ_list_t cll_create_static()
{
  return ((circ_list_t) {
      .size = 0,
      .head = NULL,
      .tail = NULL
  });
}

/**
 * @brief Clears the list by deleting every node in it.
 * The list will still be usable after this call.
 */
void	cll_clear(circ_list_t* list)
{
  node_t* node = list->head;
  
  while (!cll_is_empty(list)) {
    node_t* next = node->next;
    
    cll_remove_node(list, node);
    node = next;
  }
}

/**
 * @brief Destroys every element of the given `list` and
 * frees the memory allocated by the `list`. The given pointer
 * will not be usable after a call to this function.
 */
void	cll_destroy(circ_list_t* list)
{
  cll_clear(list);
  free(list);
}


/**
 * @brief Searches the list for the given `node`.
 * @return the found node if any, NULL otherwise.
 */
node_t*	cll_find_node(const circ_list_t* list, const node_t* element)
{
  node_t* node = list->head;
  
  for (size_t i = 0; i < list->size; ++i) {
    if (node == element) {
      return (node);
    }
    node = node->next;
  }
  return (NULL);
}

/**
 * @return the size of the given `list`. That is, the number of nodes currently
 * held by the list.
 */
size_t	cll_get_size(const circ_list_t* list)
{
  return (list->size);
}

/**
 * @return a positive value if the given `list` is
 * empty, zero otherwise.
 */
int	cll_is_empty(const circ_list_t* list)
{
  return (cll_get_size(list) == 0);
}

/**
 * @brief Creates a new node instance initialized
 * with the given `element`.
 * @return a new instance of a `node_t`.
 */
node_t* cll_new_node(void* element)
{
  node_t* node;
  
  node = malloc(sizeof(*node));
  node->element = element;
  node->next = NULL;
  node->prev = NULL;
  return (node);
}

/**
 * @brief Adds a new element to the `list`. This will cause a new `node_t`
 * to be created, holding the given `element` and pushed at the front of the
 * given `list`.
 * @return a pointer to the newly created node.
 */
node_t*	cll_push_front(circ_list_t* list, void* element)
{
  node_t* node = cll_new_node(element);
  node_t* head = list->head;
  
  if (head) {
    // Binding the node to the list elements.
    node->next = head;
    node->prev = head->prev;
    // Binding the list elements to the node.
    head->prev->next = node;
    head->prev = node;
  } else {
    node->next = node;
    node->prev = node;
    list->tail = node;
  }
  list->head = node;
  list->size++;
  return (node);
}

/**
 * @brief Adds a new element to the `list`. This will cause a new `node_t`
 * to be created, holding the given `element` and pushed to the back of the
 * given `list`.
 * @return a pointer to the newly created node.
 */
node_t*	cll_push_back(circ_list_t* list, void* element)
{
  node_t* node = cll_new_node(element);
  node_t* tail = list->tail;

  if (tail) {
    // Binding the node to the list elements.
    node->next = tail->next;
    node->prev = tail;
    // Binding the list elements to the node.
    tail->next->prev = node;
    tail->next = node;
  } else {
    node->next = node;
    node->prev = node;
    list->head = node;
  }
  list->tail = node;
  list->size++;
  return (node);
}

/**
 * @brief Removes the node associated with the given node pointer
 * from the list.
 * @return the pointer held by the removed node.
 */
void* cll_pop_node(circ_list_t* list, node_t* node)
{
  void* element;
  
  if (!node) {
    return (NULL);
  }
  element = node->element;
  cll_remove_node(list, node);
  return (element);
}

/**
 * @brief Removes the node located at the head of the list.
 * @return the pointer held by the removed node.
 */
void* cll_pop_back(circ_list_t* list)
{
  return (cll_pop_node(list, list->tail));
}

/**
 * @brief Removes the node located at the tail of the list.
 * @return the pointer held by the removed node.
 */
void* cll_pop_front(circ_list_t* list)
{
  return (cll_pop_node(list, list->head));
}

node_t* cll_get_next(circ_list_t* list)
{
    return(list->head = list->head->next);
}

node_t* cll_get_previous(circ_list_t* list)
{
    return(list->head = list->head->prev);
}

void* cll_get_actual(circ_list_t* list)
{
    return list->head->element;
}

void cll_goto_head(circ_list_t* list)
{
    while(list->head != list->tail)
    {
        list->head = list->head->next;
    }
    list->head = list->head->next;
}

void cll_goto_tail(circ_list_t* list)
{
    while(list->head != list->tail)
    {
        list->head = list->head->next;
    }
}

/**
 * @brief Removes the given `node` from the `list`
 * and frees the memory allocated by the `node`.
 * @return a positive value if the given `node` has
 * been successfully removed from the `list`, a negative
 * value otherwise.
 */
int	cll_remove_node(circ_list_t* list, node_t* node)
{
  node_t* found = cll_find_node(list, node);
  
  if (found != NULL) {
    found->prev->next = found->next;
    found->next->prev = found->prev;
    if (list->head == found) {
      list->head = found->next;
    }
    if (list->tail == found) {
      list->tail = found->prev;
    }
    list->size--;
    if (list->size == 0) {
      list->tail = NULL;
      list->head = NULL;
    }
    free(found);
    return (1);
  }
  return (0);
}
