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

ArrayList create(int capacity);                 // ArrayList 생성
void isNull(ArrayList* list);                   // ArrayList NULL assert 체크
int isEmpty(ArrayList* list);                   // ArrayList size 가 0 일 경우 1 반환, 아닐 경우 0 반환
int isFull(ArrayList* list);                    // ArrayList size 가 capacity 와 같을 경우 1 반환, 아닐 경우 0 반환
int get(ArrayList* list, int index);            // ArrayList index 위치의 data 값을 반환, 실패 시 -1 반환
int set(ArrayList* list, int index, int data);  // ArrayList index 위치의 data 값을 갱신, 성공 시 0, 실패 시 -1 반환
void append(ArrayList* list, int data);         // List 맨 끝에 data 추가
void grow(ArrayList* list);                     // List 크기를 2배로 확장
void print(ArrayList* list);                    // List 출력
void clear(ArrayList* list);                    // List 비우기

int main(int argc, char* argv[]) {
    ArrayList list1 = create(INIT_CAPACITY);

    if(argc > 1) {
        for(int i = 1; i < argc; i++)
            append(&list1, atoi(argv[i]));
    }
    else {
        srand((unsigned int)time(NULL));
        for(int i = 0; i < INSERT_MAX_NUMBERS; i++)
            append(&list1, rand() % MAX_RANDOM);
    }

    printf("[Get 5 Random value]\n");
    for(int i = 0; i < 5; i++) {
        int randomIndex = rand() % INSERT_MAX_NUMBERS;
        printf("list1[%d]: %d\n", randomIndex, get(&list1, randomIndex));
    }
    printf("\n");


    printf("[Replace Random value]\n");
    int randomIndex2 = rand() % INSERT_MAX_NUMBERS;
    set(&list1, randomIndex2, 1234);
    printf("list1[%d]: %d\n\n", randomIndex2, get(&list1, randomIndex2));

    print(&list1);

    clear(&list1);
    return SUCCESS;
}

ArrayList create(int capacity) {
    assert(capacity > 0);
    ArrayList newList;

    newList.data = malloc(sizeof(int)*capacity);
    newList.capacity = capacity;
    newList.size = 0;

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
        printf("[func get()] : Invaild index.\n");
        return FAILED;
    }

    return list->data[index];
}

int set(ArrayList* list, int index, int data) {
    isNull(list);
    if(isEmpty(list)) {
        printf("[func set()] : List is Empty.\n");
        return FAILED;
    }

    if(index < 0 || index > list->size-1) {
        printf("[func get()] : Invaild index.\n");
        return FAILED;
    }

    list->data[index] = data;

    return SUCCESS;
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
    if(isEmpty(list)) {
        printf("[func clear()]: List is empty.\n");
        return;
    }
  
    printf("[Delete list Info]: list: %p, list.data : %p, list.size : %zu bytes, list.capacity : %d\n", list, list->data, sizeof(int)*list->size, list->capacity);
    
    free(list->data);
    list->data = NULL;
    list->capacity = 0;
    list->size = 0;
}