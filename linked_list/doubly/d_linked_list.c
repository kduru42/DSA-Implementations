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
    else
        ll->head->prev = n;


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


// DELETION

void pop_front(LinkedList* ll) {
    if (!ll->head) return;

    if (!ll->head->next) {
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
    } else {
        Node* temp = ll->head;
        ll->head = ll->head->next;
        ll->head->prev = NULL;
        free(temp);
    }
    ll->length--;
}

void pop_back(LinkedList* ll) {
    if (!ll->head) return;

    if (!ll->head->next) {
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
    } else {
        Node* temp = ll->tail;
        ll->tail = ll->tail->prev;
        ll->tail->next = NULL;
        free(temp);
    }
    ll->length--;
}

void delete_at(LinkedList* ll, int index) {
    if (!ll->head || index < 0 || index >= ll->length) return;

    if (index == 0)
        pop_front(ll);
    else if (index == ll->length - 1)
        pop_back(ll);
    else {
        int i = 0;
        Node* iter;
        if (index < ll->length / 2) {
            iter = ll->head;
            while (i++ < index)
                iter = iter->next;
        } else {
            int i = ll->length - 1;
            iter = ll->tail;
            while (i-- > index)
                iter = iter->prev;
        }
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
        free(iter);
        ll->length--;
    }
}

void delete_value(LinkedList* ll, int val) {
    if (!ll->head) return;

    if (ll->head->data == val)
        pop_front(ll);
    else {
        Node* iter = ll->head;
        while(iter) {
            if (iter->data == val) {
                iter->prev->next = iter->next;
                if (iter != ll->tail)
                    iter->next->prev = iter->prev;
                free(iter);
                ll->length--;
                return;
            }
            iter = iter->next;
        }
    }
    
}

void delete_all_value(LinkedList* ll, int val) {
    if (!ll->head) return;

    Node* iter = ll->head;
    while(iter) {
        if (iter->data == val) {
            if (iter == ll->head)
                pop_front(ll);
            else {
                Node* temp = iter->next;
                iter->prev->next = iter->next;
                if (iter != ll->tail)
                    iter->next->prev = iter->prev;
                free(iter);
                iter = temp;
                continue;
            }
            ll->length--;
        }
        iter = iter->next;
    }
}

void free_list(LinkedList* ll) {
    if (!ll) return;

    Node* iter = ll->head;
    while(iter) {
        Node* temp = iter->next;
        free(iter);
        iter = temp;
    }
    free(ll);
}

// SEARCH & ACCESS

Node* find(LinkedList* ll, int val) {
    if (!ll->head) return NULL;

    Node* iter = ll->head;
    while(iter) {
        if (iter->data == val)
            return iter;
        iter = iter->next;
    }
    return NULL;
}

Node* get_at(LinkedList* ll, int index) {
    if (!ll->head || index < 0 || index >= ll->length) return NULL;

    if (index == 0)
        return ll->head;
    else if (index == ll->length - 1)
        return ll->tail;
    else {
        Node* iter;
        int i;
        if (index < ll->length / 2) {
            iter = ll->head;
            i = 0;
            while (i++ < index)
                iter = iter->next;
        } else {
            iter = ll->tail;
            i = ll->length - 1;
            while (i-- > index)
                iter = iter->prev;
        }
        return iter;
    }
    return NULL;
}

Node* get_nth_from_end(LinkedList* ll, int index) {
    if (!ll->head || index < 0 || index >= ll->length) return NULL;

    if (index == 0)
        return ll->tail;
    else if (index == ll->length - 1)
        return ll->head;
    else {
        Node* iter = ll->tail;
        int i = ll->length - 1;
        int real_index = ll->length - index - 1;
        while (i-- > real_index)
            iter = iter->prev;
        return iter;
    }
    return NULL;
}

// ALGORITHMS

void reverse(LinkedList* ll) {
    if (!ll->head) return;

    Node* temp = NULL;
    Node* iter = ll->head;
    ll->head = ll->tail;
    ll->tail = iter;
    while (iter) {
        temp = iter->next;
        iter->next = iter->prev;
        iter->prev = temp;
        iter = temp;
    }
}

Node* mergeSort(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;

    Node* result;
    if (l->data <= r->data) {
        result = l;
        result->next = mergeSort(l->next, r);
    } else {
        result = r;
        result->next = mergeSort(r->next, l);
    }
    return result;
}

Node* sort(Node* head) {
    if (!head || !head->next) return NULL;

    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* middle = slow;
    Node* left = head;
    Node* right = slow->next;
    slow->next = NULL;
    right->prev = NULL;

    sort(left);
    sort(right);
    return mergeSort(left, right);
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
    insert_at(ll, 48, 0);
    insert_at(ll, 48, 6);
    ll->head = sort(ll->head);

    print_list(ll);

    free_list(ll);

}