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

// INSERTION

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
        if (iter->next->data >= val)
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

// DELETION

void pop_front(LinkedList* ll) {
    if (!ll->head) return;

    Node* temp = ll->head;
    ll->head = ll->head->next;
    free(temp);
    ll->length--;
}

void pop_back(LinkedList* ll) {
    if (!ll->head) return;

    if(!ll->head->next)
    {
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
    }
    else
    {
        Node* temp = ll->head;
        while (temp->next->next)
            temp = temp->next;
        free(ll->tail);
        ll->tail = temp;
        temp->next = NULL;
    }

    ll->length--;
}

void delete_at(LinkedList* ll, int index) {
    if (!ll->head) return;

    if (index == 0)
        pop_front(ll);
    else if (index == ll->length - 1)
        pop_back(ll);
    else {
        int i = 0;
        Node* iter = ll->head;
        while (i++ < index - 1)
            iter = iter->next;
        Node* temp = iter->next;
        iter->next = iter->next->next;
        free(temp);
        ll->length--;
    }
}

void delete_value(LinkedList* ll, int val) {
    if (!ll->head) return;

    if (ll->head->data == val)
        pop_back(ll);
    else {
        Node* iter = ll->head;
        while (iter->next)
        {
            if (iter->next->data == val) {
                Node* temp = iter->next;
                iter->next = iter->next->next;
                free(temp);
                ll->length--;
                return;
            }
            iter = iter->next;
        }
    }
}

void delete_all_value(LinkedList* ll, int val) {
    if (!ll->head) return;

    if (ll->head->data == val)
        pop_back(ll);

    Node* iter = ll->head;
    while (iter->next) {
        if (iter->next->data == val) {
            Node* temp = iter->next;
            iter->next = iter->next->next;
            free(temp);
            ll->length--;
        }
        if (!iter->next) break;
        iter = iter->next;
    }
}

void free_list(LinkedList* ll) {
    Node* iter = ll->head;
    while(iter) {
        Node* temp = iter;
        iter = iter->next;
        free(temp);
    }
    free(ll);
}

// SEARCH && ACCESS

Node* find(LinkedList* ll, int val) {
    if (!ll->head) return NULL;

    Node* iter = ll->head;
    while (iter) {
        if (iter->data == val)
            return iter;
        iter = iter->next;
    }

    return NULL;
}

Node* get_at(LinkedList* ll, int index) {
    if (!ll->head) return NULL;

    if (index < 0 || index >= ll->length) return NULL;

    if (index == 0)
        return ll->head;
    else if (index == ll->length - 1)
        return ll->tail;
    else {
        Node* iter = ll->head;
        int i = 0;
        while (i++ < index)
            iter = iter->next;
        return iter;
    }
    return NULL;
}

Node* get_nth_from_end(LinkedList* ll, int index) {
    if (!ll->head) return NULL;

    if (index < 0 || index > ll->length) return NULL;

    return get_at(ll, ll->length - index);
}

// ALGORITHMS

// Reversing Linked List using Three Pointer Algorithm (O(n) time, O(1) space)
void reverse(LinkedList *ll) {
    if (!ll->head) return;

    Node* curr = ll->head;
    Node* prev = NULL;
    Node* next = NULL;
    ll->tail = ll->head;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    ll->head = prev;
}


// Merge function for mergeSort (O(n + m) time, O(1) space)
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

// Sorting a linked list using Merge Sort algorith  (O(nlogn) time, O(1) space)
Node* sort(Node* head) {
    if (!head || !head->next) return head;

    Node* slow = head;
    Node* fast = head->next;
    while (fast &&  fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* middle = slow;
    Node* left = head;
    Node* right = middle->next;
    middle->next = NULL;

    left = sort(left);
    right = sort(right);

    return mergeSort(left, right);
}

// Merging two linked lists (O(1) time, O(1) space)
Node* merge(LinkedList* ll1, LinkedList* ll2) {
    if (!ll1->head) return ll2->head;
    if (!ll2->head) return ll1->head;

    ll1->tail->next = ll2->head;
    return ll1->head;
}

// Finds if a linked list has cycle using Floyd's Algorithm (O(n) time, O(1) space)
Node* detect_cycle(LinkedList* ll) {
    if (!ll->head) return NULL;

    Node* slow = ll->head;
    Node* fast = ll->head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (fast) {
        slow = ll->head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
    return NULL;
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
    // Node* temp = ll->head;
    // temp = temp->next;
    // temp = temp->next;
    // ll->tail->next = temp;
    // printf("%d", detect_cycle(ll)->data);
    print_list(ll);
    // free_list(ll);
}