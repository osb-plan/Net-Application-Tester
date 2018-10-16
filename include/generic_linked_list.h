#ifndef GENERIC_LINKED_LIST_H
#define GENERIC_LINKED_LIST_H

    void init(NODE** head);
    void print_list(NODE* head);
    NODE* add(NODE* node, DATA data);
    void add_at(NODE* node, DATA data);
    void remove_node(NODE* head);
    NODE * reverse_rec(NODE * ptr, NODE * previous);
    NODE * reverse(NODE * node);
    NODE *free_list(NODE *head);
    NODE *sort_list(NODE *head);

#endif





