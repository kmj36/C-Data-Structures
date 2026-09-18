#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUCCESS 0
#define FAILED -1
#define MAX_RANDOM 256

typedef struct _node {
    int data;
    struct _node* next;
} node;

node* head = NULL;
node* tail = NULL;

node* createNode(int data);
int insertNode(int data);
void printList();
int freeList();

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));

    int i;
    if(argc < 2)
        for(i = 0; i < 10; i++) insertNode(rand() % MAX_RANDOM);
    else
	for(i = 1; i < argc; i++) insertNode(atoi(argv[i]));

    printList();
    freeList();

    return 0;
}

node* createNode(int data) {
    node* newNode = malloc(sizeof(node));
    
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

int insertNode(int data) {
    if(head == NULL) {
        head = createNode(data);
        tail = head;
        tail->next = head;
        return SUCCESS;
    }

    node* newNode = createNode(data);

    newNode->next = head;
    tail->next = newNode;
    tail = newNode;
    
    return SUCCESS;
}

void printList() {
    node* cur = head;

    printf("[Circle list] : ");
    while(cur->next != head) {
        printf("%02X->", cur->data);
	    cur = cur->next;
    }
    printf("%02X->", cur->data);
    printf("head\n");
}

int freeList() {
    node* freeTarget;
    node* cur = head;

    while(cur->next != head) {
        freeTarget = cur;
	    cur = cur->next;

	    printf("delete: 0x%08X | data: %02X | nextNode: 0x%08X\r\n", freeTarget, freeTarget->data, freeTarget->next);
	
	    free(freeTarget);
    }

    printf("delete: 0x%08X | data: %02X | nextNode: 0x%08X\r\n", cur, cur->data, cur->next);
    free(cur);

    head = NULL;
    tail = NULL;

    return SUCCESS;
}
