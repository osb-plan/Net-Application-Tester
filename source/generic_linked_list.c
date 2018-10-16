#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int info;
} DATA;

typedef struct node {
    DATA data;
    struct node* next;
} ELEMENT;

void init(ELEMENT** head) {
    *head = NULL;
}

void print_list(ELEMENT* head) {
    ELEMENT * temp;
    for (temp = head; temp; temp = temp->next)
        printf("%5d", temp->data.info);
}

ELEMENT* add(ELEMENT* node, DATA data) {
    ELEMENT* temp = (NODE*) malloc(sizeof (NODE));
    if (temp == NULL) {
        exit(0); // no memory available
    }
    temp->data = data;
    temp->next = node;
    node = temp;
    return node;
}

void add_at(ELEMENT* node, DATA data) {
    ELEMENT* temp = (ELEMENT*) malloc(sizeof (ELEMENT));
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->next = node->next;
    node->next = temp;
}

void remove_node(ELEMENT* head) {
    ELEMENT* temp = (ELEMENT*) malloc(sizeof (ELEMENT));
    if (temp == NULL) {
        exit(EXIT_FAILURE); 
    }
    temp = head->next;
    head->next = head->next->next;
    free(temp);
}

ELEMENT * reverse_rec(ELEMENT * ptr, ELEMENT* previous) {
    ELEMENT * temp;
    if (ptr->next == NULL) {
        ptr->next = previous;
        return ptr;
    } else {
        temp = reverse_rec(ptr->next, ptr);
        ptr->next = previous;
        return temp;
    }
}

ELEMENT * reverse(ELEMENT * node) {
    ELEMENT * temp;
    ELEMENT * previous = NULL;
    while (node != NULL) {
        temp = node->next;
        node->next = previous;
        previous = node;
        node = temp;
    }
    return previous;
}

ELEMENT *free_list(ELEMENT *head) {
    ELEMENT *tmpPtr = head;
    ELEMENT *followPtr;
    while (tmpPtr != NULL) {
        followPtr = tmpPtr;
        tmpPtr = tmpPtr->next;
        free(followPtr);
    }
    return NULL;
}

ELEMENT *sort_list(ELEMENT *head) {
    ELEMENT *tmpPtr = head, *tmpNxt = head->next;
    DATA tmp;
    while (tmpNxt != NULL) {
        while (tmpNxt != tmpPtr) {
            if (tmpNxt->data.info < tmpPtr->data.info) {
                tmp = tmpPtr->data;
                tmpPtr->data = tmpNxt->data;
                tmpNxt->data = tmp;
            }
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = head;
        tmpNxt = tmpNxt->next;
    }
    return tmpPtr;
}

