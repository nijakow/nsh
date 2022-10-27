#ifndef NSH_UTIL_LIST_H
#define NSH_UTIL_LIST_H

#define nsh_list_decl(name) \
nsh_class(name ## _list_node, { struct name ## _list_node* next; struct name* value; }); \
nsh_class(name ## _list, { struct name ## _list_node*  nodes; });

#define nsh_list_impl(name) \
void name ## _list_node_create(struct name ## _list_node* node) { \
    node->next = NULL; \
    node->value = NULL; \
} \
void name ## _list_node_destroy(struct name ## _list_node* node) { \
    nsh_delete(name ## _list_node, node->next);  \
    nsh_delete(name, node->value); \
} \
void name ## _list_create(struct name ## _list* list) { \
    list->nodes = NULL; \
} \
void name ## _list_destroy(struct name ## _list* list) { \
    nsh_delete(name ## _list_node, list->nodes);  \
}

#endif
