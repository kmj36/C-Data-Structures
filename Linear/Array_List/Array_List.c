#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define INIT_CAPACITY 16
#define INSERT_MAX_NUMBERS 16
#define MAX_RANDOM 256
#define SUCCESS 0
#define FAILED -1

typedef struct _ArrayList {
    int *data;
    int capacity;
    int size;
} ArrayList;

ArrayList* create(int capacity);                     // ArrayList 생성
void isNull(ArrayList* list);                       // ArrayList NULL assert 체크
int isEmpty(ArrayList* list);                       // ArrayList size 가 0 일 경우 1 반환, 아닐 경우 0 반환
int isFull(ArrayList* list);                        // ArrayList size 가 capacity 와 같을 경우 1 반환, 아닐 경우 0 반환
int get(ArrayList* list, int index);                // ArrayList index 위치의 data 값을 반환, 실패 시 -1 반환
int set(ArrayList* list, int index, int data);      // ArrayList index 위치의 data 값을 갱신, 성공 시 0, 실패 시 -1 반환
int insert(ArrayList* list, int index, int data);   // ArrayList index 위치에 data 를 삽입 후 뒤로 시프트
int delete(ArrayList* list, int index);             // ArrayList index 위치를 제거하여 반환 후 앞으로 시프트
int find(ArrayList* list, int search);              // ArrayList data 찾은 후 그 index 위치를 반환, 찾지 못하면 -1 반환
void append(ArrayList* list, int data);             // List 맨 끝에 data 추가
void grow(ArrayList* list);                         // List 크기를 2배로 확장
void printLine(ArrayList* list);
void print(ArrayList* list);                        // List 출력
void clear(ArrayList* list);                        // List 비우기

int main(int argc, char* argv[]) {
    ArrayList* list1 = create(INIT_CAPACITY);

    if(argc > 1) {
        for(int i = 1; i < argc; i++)
            append(list1, atoi(argv[i]));
    }
    else {
        srand((unsigned int)time(NULL));
        for(int i = 0; i < INSERT_MAX_NUMBERS; i++)
            append(list1, rand() % MAX_RANDOM);
    }
    printLine(list1);

    printf("[Get 5 random element]\n");
    for(int i = 0; i < 5; i++) {
        int randomIndex = rand() % INSERT_MAX_NUMBERS;
        printf("list1[%d]: %d\n", randomIndex, get(list1, randomIndex));
    }
    printf("\n");

    printf("[Replace random element]\n");
    int randomIndex2 = rand() % INSERT_MAX_NUMBERS;
    set(list1, randomIndex2, 1234);
    printf("list1[%d]: %d\n\n", randomIndex2, get(list1, randomIndex2));

    printf("[Random find element]\n");
    int randomIndex3 = rand() % INSERT_MAX_NUMBERS;
    int findTarget = get(list1, randomIndex3);
    printf("list1 - find %d index:[%d]\n\n", findTarget, find(list1, findTarget));

    printf("[Insert 4 values index 0]\n");
    for(int i = 0; i < 4; i++)
        insert(list1, 0, i);
    printLine(list1);

    printf("[Delete 4 values index 0]\n");
    for(int i = 0; i < 4; i++)
        delete(list1, 0);
        
    printLine(list1);


    clear(list1);
    return SUCCESS;
}

ArrayList* create(int capacity) {
    assert(capacity > 0);
    ArrayList* newList = malloc(sizeof(ArrayList));

    newList->data = malloc(sizeof(int)*capacity);
    newList->capacity = capacity;
    newList->size = 0;
    printf("[Create list Info]: list: %p, list.data : %p, list.size : %d, list.capacity : %d\n", newList, newList->data, newList->size, newList->capacity);

    return newList;
}

void isNull(ArrayList* list) {
    assert(list != NULL);
}

int isEmpty(ArrayList* list) {
    isNull(list);
    return list->size == 0;
}

int isFull(ArrayList* list) {
    isNull(list);
    return list->capacity == list->size;
}

int get(ArrayList* list, int index) {
    isNull(list);
    if(isEmpty(list)) {
        printf("[func get()] : List is Empty.\n");
        return FAILED;
    }

    if(index < 0 || index > list->size-1) {
        printf("[func get()] : Invalid index.\n");
        return FAILED;
    }

    return list->data[index];
}

int set(ArrayList* list, int index, int data) {
    isNull(list);

    if(index < 0 || index > list->size-1) {
        printf("[func get()] : Invalid index.\n");
        return FAILED;
    }

    list->data[index] = data;

    return SUCCESS;
}

int insert(ArrayList* list, int index, int data) {
    isNull(list);

    if(index < 0 || index > list->size) {
        printf("[func insert()] : Invalid index.\n");
        return FAILED;
    }

    if(isFull(list)) grow(list);

    int i = list->size;
    while(i > index) { 
        list->data[i] = list->data[i-1];
        i--;
    }

    list->data[index] = data;
    list->size++;

    return SUCCESS;
}

int delete(ArrayList* list, int index) {
    isNull(list);

    if(isEmpty(list)) {
        printf("[func delete()] : List is Empty.\n");
        return FAILED;
    }

    if(index < 0 || index > list->size-1) {
        printf("[func delete()] : Invalid index.\n");
        return FAILED;
    }

    int returnData = list->data[index];

    int i = index;
    while(i < list->size) {
        list->data[i] = list->data[i+1];
        i++;
    }

    list->size--;

    return returnData;
}

int find(ArrayList* list, int search) {
    isNull(list);
    
    if(isEmpty(list)) {
        printf("[func find()] : List is Empty.\n");
        return FAILED;
    }

    int index = FAILED;
    int i = 0;
    while(i < list->size) {
        if(list->data[i] == search) index = i;
        i++;
    }

    return index;
}

void append(ArrayList* list, int data) {
    isNull(list);

    int idx = list->size;

    if(isFull(list))
        grow(list);

    list->data[idx] = data;
    list->size++;
}

void grow(ArrayList* list) {
    isNull(list);
    if(isEmpty(list)) {
        printf("[func grow()]: List is empty.\n");
        return;
    }

    int newCapacity = list->capacity * 2;
    int *newData = malloc(sizeof(int)*newCapacity);

    // memcpy(목적지 주소, 원본 주소, 총 바이트 수)
    memcpy(newData, list->data, sizeof(int)*list->capacity);

    free(list->data);
    list->data = newData;
    list->capacity = newCapacity;
}

void printLine(ArrayList* list) {
    isNull(list);
    if(isEmpty(list)) {
        printf("[func printLine()]: List is empty.\n");
        return;
    }

    for(int i = 0; i < list->size; i++)
        printf("%d ", list->data[i]);
    printf("\n");
}

void print(ArrayList* list) {
    isNull(list);
    if(isEmpty(list)) {
        printf("[func print()]: List is empty.\n");
        return;
    }

    printf("[List Info]: list : %p, list.data : %p, list.size : %d, list.capacity : %d\n", list, list->data, list->size, list->capacity);
    for(int i = 0; i < list->size; i++)
        printf("%d\n", list->data[i]);
    printf("\n");
}

void clear(ArrayList* list) {
    isNull(list);
  
    printf("[Delete list Info]: list: %p, list.data : %p, list.size : %d, list.capacity : %d\n", list, list->data, list->size, list->capacity);
    
    free(list->data);
    list->data = NULL;
    list->capacity = 0;
    list->size = 0;
}