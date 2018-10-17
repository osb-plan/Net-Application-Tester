#include <stdio.h>
#include <stdlib.h>
#include "../include/data_defs.h"


void init(FIELD** head) {
    *head = NULL;
}

void print_list(FIELD* head) {
    FIELD * temp;
    printf("FIELD List:\n");
    printf("-------------------------------------\n");
    
    for (temp = head; temp; temp = temp->next)
    {
        printf("%s \n", temp->field_info.field_name);
        printf("%d \n", temp->field_info.field_type);
        printf("%d \n", temp->field_info.variation.var_type);        
    }
    printf("-------------------------------------\n");

}

FIELD* add(FIELD* node, DATA data) {
    FIELD* temp = (FIELD*) malloc(sizeof (FIELD));
    if (temp == NULL) {
        exit(0); // no memory available
    }
    temp->field_info = data;
    temp->next = node;
    node = temp;
    return node;
}

void add_at(FIELD* node, DATA data) {
    FIELD* temp = (FIELD*) malloc(sizeof (FIELD));
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }
    temp->field_info = data;
    temp->next = node->next;
    node->next = temp;
}

void remove_node(FIELD* head) {
    FIELD* temp = (FIELD*) malloc(sizeof (FIELD));
    if (temp == NULL) {
        exit(EXIT_FAILURE); 
    }
    temp = head->next;
    head->next = head->next->next;
    free(temp);
}

FIELD * reverse_rec(FIELD * ptr, FIELD* previous) {
    FIELD * temp;
    if (ptr->next == NULL) {
        ptr->next = previous;
        return ptr;
    } else {
        temp = reverse_rec(ptr->next, ptr);
        ptr->next = previous;
        return temp;
    }
}

FIELD * reverse(FIELD * node) {
    FIELD * temp;
    FIELD * previous = NULL;
    while (node != NULL) {
        temp = node->next;
        node->next = previous;
        previous = node;
        node = temp;
    }
    return previous;
}

FIELD *free_list(FIELD *head) {
    FIELD *tmpPtr = head;
    FIELD *followPtr;
    while (tmpPtr != NULL) {
        followPtr = tmpPtr;
        tmpPtr = tmpPtr->next;
        free(followPtr);
    }
    return NULL;
}


