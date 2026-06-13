#pragma once
#include <cstdio>
#include <algorithm>

#define MAX_HEAP_SIZE 100

class MinHeap {
    int data[MAX_HEAP_SIZE];
    int size;
public:
    MinHeap() : size(0) {}
    bool isEmpty() { return size == 0; }
    bool isFull()  { return size >= MAX_HEAP_SIZE - 1; }
    void insert(int val) {
        if (isFull()) { printf("힙 포화 에러\n"); return; }
        data[++size] = val;
        int i = size;
        while (i > 1 && data[i] < data[i / 2]) {
            std::swap(data[i], data[i / 2]);
            i /= 2;
        }
    }
    int remove() {
        if (isEmpty()) { printf("힙 공백 에러\n"); return -1; }
        int minVal = data[1];
        data[1] = data[size--];
        int i = 1;
        while (true) {
            int smallest = i;
            if (2 * i <= size && data[2 * i] < data[smallest]) smallest = 2 * i;
            if (2 * i + 1 <= size && data[2 * i + 1] < data[smallest]) smallest = 2 * i + 1;
            if (smallest == i) break;
            std::swap(data[i], data[smallest]);
            i = smallest;
        }
        return minVal;
    }
    void display() {
        printf("[MinHeap size=%d] ", size);
        for (int i = 1; i <= size; i++) printf("%d ", data[i]);
        printf("\n");
    }
};
