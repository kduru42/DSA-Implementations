#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int length;
} LinkedList;

void list_init(LinkedList** ll) {
    *ll = (LinkedList*)malloc(sizeof(LinkedList));
    (*ll)->head = NULL;
    (*ll)->tail = NULL;
    (*ll)->length = 0;
}

// INSERTION

void push_front(LinkedList* ll, int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return;
    *n = (Node){val, NULL, NULL};

    n->next = ll->head;
    n->prev = NULL;
    if (!ll->head)
        ll->tail = n;
    ll->head = n;
    ll->length++;
}

void push_back(LinkedList* ll, int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return;
    *n = (Node){val, NULL, NULL};

    if (!ll->head)
        ll->head = n;
    else
        ll->tail->next = n;

    n->prev = ll->tail;
    ll->tail = n;
    ll->length++;
}

void insert_at(LinkedList* ll, int val, int index) {

    if (index < 0 || index > ll->length) return;

    if(index == 0)
        push_front(ll, val);
    else if (index == ll->length)
        push_back(ll, val);
    else {
        Node* n = (Node*)malloc(sizeof(Node));
        if (!n) return;
        *n = (Node){val, NULL, NULL};

        int i = 0;
        Node* iter = ll->head;
        while (i++ < index)
            iter = iter->next;
        iter->prev->next = n;
        n->prev = iter->prev;
        n->next = iter;
        iter->prev = n;
        ll->length++;
    }
}

void insert_after_value(LinkedList* ll, int val1, int val2) {
    if (!ll->head) return;

    Node* iter = ll->head;
    while(iter) {
        if (iter->data == val2) {
            Node* n = (Node*)malloc(sizeof(Node));
            if (!n) return;
            *n = (Node){val1, NULL, NULL};

            Node* temp = iter->next;
            iter->next = n;
            n->next = temp;
            n->prev = iter;
            temp->prev = n;
            ll->length++;
        }
        iter = iter->next;
    }
}

void insert_sorted(LinkedList* ll, int val) {
    if (!ll->head) {
        push_back(ll, val);
        return;
    }

    if (val <= ll->head->data)
    {
        push_front(ll, val);
        return;
    }
    else {
        Node* iter = ll->head;
        while (iter) {
            if (val <= iter->data) {
                Node* n = (Node*)malloc(sizeof(Node));
                if (!n) return;
                *n = (Node){val, NULL, NULL};

                iter->prev->next = n;
                n->next = iter;
                n->prev = iter->prev;
                iter->prev = n;
                ll->length++;
                return;
            }
            iter = iter->next;
        }
    }
    push_back(ll, val);
}

void print_list(LinkedList* ll) {
    if (!ll->head) return;

    Node* iter = ll->head;
    while(iter) {
        printf("%d----->", iter->data);
        iter = iter->next;
    }
    printf("\n");
}

int main() 
{

    LinkedList* ll;
    list_init(&ll);

    push_front(ll, 42);
    push_front(ll, 78);
    push_back(ll, 105);
    insert_at(ll, 48, 2);
    insert_after_value(ll, 79, 78);
    insert_sorted(ll, 100);

    print_list(ll);

}