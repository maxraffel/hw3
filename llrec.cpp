#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot) {
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }

    Node* temp = head->next;
    

    if (head->val <= pivot) {
        smaller = head;
        smaller->next = NULL;
        llpivot(temp, smaller->next, larger, pivot);
    } else {
        larger = head;
        larger->next = NULL;
        llpivot(temp, smaller, larger->next, pivot);
    }
    head = NULL;
}
