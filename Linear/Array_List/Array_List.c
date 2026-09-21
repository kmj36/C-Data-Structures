#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define INIT_CAPACITY 16
#define MAX_RANDOM 256

#define SUCCESS 0
#define FAILED -1

typedef struct _ArrayList {
    int *data;
    int capacity;
    int size;
} ArrayList;

ArrayList createList(int capacity);
void insertList(ArrayList* list, int data);
void removeList(ArrayList* list, int index, int data);
void growList(ArrayList* list);
void printList(ArrayList* list);
void freeList(ArrayList* list);

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));
    int i;
    ArrayList list1 = createList(INIT_CAPACITY);

    for(i = 0; i < 16; i++)
        insertList(&list1, rand() % MAX_RANDOM);

    printList(&list1);
    freeList(&list1);

    return SUCCESS;
}

ArrayList createList(int capacity) {
    assert(capacity > 0);
    ArrayList newList;

    newList.data = malloc(sizeof(int)*capacity);
    newList.capacity = capacity;
    newList.size = 0;

    return newList;
}

void insertList(ArrayList* list, int data) {
    assert(list != NULL);
    int idx = list->size;

    if( list->size == list->capacity ) growList(list);

    list->data[idx] = data;
    list->size++;
}

void growList(ArrayList* list) {
    assert(list != NULL);
    int newCapacity = list->capacity * 2;
    int *newData = malloc(sizeof(int)*newCapacity);

    // memcpy(목적지 주소, 원본 주소, 총 바이트 수)로 데이터 복사
    memcpy(newData, list->data, sizeof(int)*list->capacity);

    free(list->data);
    list->data = newData;
    list->capacity = newCapacity;
}

void printList(ArrayList* list) {
    assert(list != NULL);
    int i;

    printf("[List Info]: list : %p, list.data : %p, list.size : %d, list.capacity : %d\n", list, list->data, list->size, list->capacity);

    for(i = 0; i < list->size; i++)
        printf("%d\n", list->data[i]);
}

void freeList(ArrayList* list) {
    assert(list != NULL);
    
    if(list->data != NULL) {
        printf("[Delete list Info]: list.data : %p, list.size : %zu bytes, list.capacity : %d\n", list->data, sizeof(int)*list->size, list->capacity);
        free(list->data);
        list->data = NULL;
        list->capacity = 0;
        list->size = 0;
    } else
        printf("List is empty\n");
}

void removeList(ArrayList* list, int index, int data) {

}