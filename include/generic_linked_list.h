#ifndef GENERIC_LINKED_LIST_H
#define GENERIC_LINKED_LIST_H


    void init(ELEMENT** head);
    void print_list(ELEMENT* head);
    ELEMENT* add(ELEMENT* node, DATA data);
    void add_at(ELEMENT* node, DATA data);
    void remove_node(ELEMENT* head);
    ELEMENT * reverse_rec(ELEMENT * ptr, NODE * previous);
    ELEMENT * reverse(ELEMENT * node);
    ELEMENT *free_list(ELEMENT *head);
    ELEMENT *sort_list(ELEMENT *head);

#endif





