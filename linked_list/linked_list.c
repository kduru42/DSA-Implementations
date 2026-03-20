#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int length;
} LinkedList;

void init_list(LinkedList** ll) {
    *ll = (LinkedList*)malloc(sizeof(LinkedList));
    if (*ll != NULL)
    {
        (*ll)->head = NULL;
        (*ll)->tail = NULL;
        (*ll)->length = 0;
    }
}

void push_front(LinkedList* list, int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return;
    
    n->data = val;
    n->next = list->head;
    if (!list->head)
        list->tail = n;

    list->head = n;
    list->length++;
}

void push_back(LinkedList* list, int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return;
    *n = (Node){val, NULL};

    if (!list->head)
        list->head = n;
    else
        list->tail->next = n;
    
    list->tail = n;
    list->length++;

}

void insert_at(LinkedList* ll, int val, int index) {
    if (index < 0 || index > ll->length) 
        return;
    else if (index == 0)
        push_front(ll, val);
    else if (index == ll->length)
        push_back(ll, val);
    else
    {
        Node* n = (Node*)malloc(sizeof(Node));
        if (!n) return;
        *n = (Node){val, NULL};

        int temp = 0;
        Node* iter = ll->head;
        while (temp++ < index - 1)
            iter = iter->next;
        n->next = iter->next;
        iter->next = n;
        ll->length++;
    }
}

void insert_after_value(LinkedList* ll, int val, int val_to_find) {
    if (!ll->head) return;

    Node* iter = ll->head;
    while (iter)
    {
        if (iter->data == val_to_find)
        {
            if (iter == ll->tail)
                push_back(ll, val);
            else
            {
                Node* n = (Node*)malloc(sizeof(Node));
                if (!n) return;
                *n = (Node){val, NULL};

                n->next = iter->next;
                iter->next = n;
                ll->length++;
            }
            return;
        }
        iter = iter->next;
    }
}

void insert_sorted(LinkedList* ll, int val) {
    if (!ll->head || ll->head->data > val)
    {
        push_front(ll, val);
        return;
    }

    Node* iter = ll->head;
    while (iter->next)
    {
        if (iter->next->data > val)
        {
            Node* n = (Node*)malloc(sizeof(Node));
            if (!n) return;
            *n = (Node){val, NULL};
            n->next = iter->next;
            iter->next = n;
            ll->length++;
            return;
        }
        iter = iter->next;
    }
    push_back(ll, val);
}

void print_list(LinkedList* list) {
    if (!list) return;
    Node* iter = list->head;
    while(iter) {
        printf("%d----->", iter->data);
        iter = iter->next;
    }
    
}

int main() {
    LinkedList* ll;
    init_list(&ll);
    push_back(ll, 42);
    push_back(ll, 24);
    push_back(ll, 12);
    insert_at(ll, 58, 1);
    insert_at(ll, 102, 2);
    push_back(ll, 105);
    insert_sorted(ll, 110);
    print_list(ll);
}