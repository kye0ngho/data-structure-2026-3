#pragma once
#include <cstdio>
#include <cstdlib>

struct Node {
    int   data;
    Node* link;
    Node(int d = 0, Node* l = nullptr) : data(d), link(l) {}
};

class LinkedStack {
    Node* top;
public:
    LinkedStack() : top(nullptr) {}
    ~LinkedStack() { while (!isEmpty()) pop(); }
    bool isEmpty() { return top == nullptr; }
    void push(int val) {
        top = new Node(val, top);
    }
    int pop() {
        if (isEmpty()) { printf("스택 공백 에러\n"); exit(1); }
        Node* tmp = top;
        int   val = tmp->data;
        top = tmp->link;
        delete tmp;
        return val;
    }
    int peek() {
        if (isEmpty()) { printf("스택 공백 에러\n"); exit(1); }
        return top->data;
    }
    void display() {
        printf("[LinkedStack] top -> ");
        for (Node* p = top; p != nullptr; p = p->link)
            printf("<%d> ", p->data);
        printf("\n");
    }
};
