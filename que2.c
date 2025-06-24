#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure definition
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Linked list structure to hold head and size
typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

// Initialize the linked list
void initList(LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

// Create a new node with given data
Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at the front of the list
void insertFront(LinkedList *list, int data) {
    Node *node = createNode(data);
    node->next = list->head;
    list->head = node;
    list->size++;
}

// Insert at the end of the list
void insertEnd(LinkedList *list, int data) {
    Node *node = createNode(data);
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *temp = list->head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = node;
    }
    list->size++;
}

// Insert at a specific position (0-based index)
bool insertAt(LinkedList *list, int index, int data) {
    if (index < 0 || index > list->size) return false;

    if (index == 0) {
        insertFront(list, data);
        return true;
    }

    Node *node = createNode(data);
    Node *temp = list->head;
    for (int i = 0; i < index - 1; i++) {
        temp = temp->next;
    }
    node->next = temp->next;
    temp->next = node;
    list->size++;
    return true;
}

// Delete node by value (first occurrence)
bool deleteByValue(LinkedList *list, int data) {
    if (!list->head) return false;

    Node *temp = list->head, *prev = NULL;

    if (temp->data == data) {
        list->head = temp->next;
        free(temp);
        list->size--;
        return true;
    }

    while (temp && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return false;

    prev->next = temp->next;
    free(temp);
    list->size--;
    return true;
}

// Delete node at index (0-based)
bool deleteAt(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) return false;

    Node *temp = list->head, *prev = NULL;

    if (index == 0) {
        list->head = temp->next;
        free(temp);
        list->size--;
        return true;
    }

    for (int i = 0; i < index; i++) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    free(temp);
    list->size--;
    return true;
}

// Search for value; returns index or -1 if not found
int search(LinkedList *list, int data) {
    Node *temp = list->head;
    int index = 0;
    while (temp) {
        if (temp->data == data) return index;
        temp = temp->next;
        index++;
    }
    return -1;
}

// Print the linked list
void printList(LinkedList *list) {
    Node *temp = list->head;
    printf("List (size=%d): ", list->size);
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free all nodes
void freeList(LinkedList *list) {
    Node *temp = list->head;
    while (temp) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
    list->size = 0;
}

// Example usage
int main() {
    LinkedList list;
    initList(&list);

    insertFront(&list, 10);
    insertEnd(&list, 20);
    insertAt(&list, 1, 15);  // List: 10 -> 15 -> 20
    printList(&list);

    printf("Index of 15: %d\n", search(&list, 15));
    deleteByValue(&list, 15);
    printList(&list);

    deleteAt(&list, 1);
    printList(&list);

    freeList(&list);
    return 0;
}
