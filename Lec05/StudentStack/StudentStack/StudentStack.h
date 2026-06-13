#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_STRING   40
#define MAX_STACK_SIZE 20

inline void error(const char* message) {
    printf("%s\n", message);
    exit(1);
}

class Student {
    int  id;
    char name[MAX_STRING];
    char dept[MAX_STRING];
public:
    Student(int i = 0, const char* n = "", const char* d = "") { set(i, n, d); }
    void set(int i, const char* n, const char* d) {
        id = i;
        strcpy(name, n);
        strcpy(dept, d);
    }
    void display() {
        printf(" 학번:%-15d 성명:%-10s 학과:%-20s\n", id, name, dept);
    }
};

class StudentStack {
    int     top;
    Student data[MAX_STACK_SIZE];
public:
    StudentStack() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == MAX_STACK_SIZE - 1; }
    void push(Student e) {
        if (isFull()) error("스택 포화 에러");
        data[++top] = e;
    }
    Student pop() {
        if (isEmpty()) error("스택 공백 에러");
        return data[top--];
    }
    Student peek() {
        if (isEmpty()) error("스택 공백 에러");
        return data[top];
    }
    void display() {
        printf("[스택 항목의 수 = %2d] ==>\n", top + 1);
        for (int i = 0; i <= top; i++)
            data[i].display();
    }
};
