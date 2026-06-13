#pragma once
#include <cstdio>
#include <cstdlib>

#define MAX_QUEUE_SIZE 100

class CircularQueue {
    int front, rear;
    int data[MAX_QUEUE_SIZE];
public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull()  { return (rear + 1) % MAX_QUEUE_SIZE == front; }
    void enqueue(int val) {
        if (isFull()) { printf("큐 포화 에러\n"); exit(1); }
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        data[rear] = val;
    }
    int dequeue() {
        if (isEmpty()) { printf("큐 공백 에러\n"); exit(1); }
        front = (front + 1) % MAX_QUEUE_SIZE;
        return data[front];
    }
};
