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
	return SUCCESS;
    }

    node* cur = head;
    while(cur->next != NULL) cur = cur->next;

    cur->next = createNode(data);
    return SUCCESS;
}

void printList() {
    node* cur = head;

    printf("[Head list] : ");
    while(cur != NULL) {
        printf("%02X->", cur->data);
	cur = cur->next;
    }
    printf("NULL\r\n");
}

int freeList() {
    node* freeTarget;
    while(head != NULL) {
        freeTarget = head;
	head = head->next;

	printf("delete: 0x%08X | data: %02X | nextNode: 0x%08X\r\n", freeTarget, freeTarget->data, freeTarget->next);
	
	free(freeTarget);
    }

    return SUCCESS;
}
