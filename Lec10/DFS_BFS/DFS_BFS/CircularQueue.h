#pragma once
#include <stdio.h>
#define MAX_QUEUE_SIZE 100

class CircularQueue {
    int front, rear;
    int data[MAX_QUEUE_SIZE];
public:
    CircularQueue() : front(0), rear(0) {}
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }
    void enqueue(int val) {
        if (isFull()) { printf("Queue Full\n"); return; }
        rear = (rear + 1) % MAX_QUEUE_SIZE;
        data[rear] = val;
    }
    int dequeue() {
        if (isEmpty()) { printf("Queue Empty\n"); return -1; }
        front = (front + 1) % MAX_QUEUE_SIZE;
        return data[front];
    }
};
