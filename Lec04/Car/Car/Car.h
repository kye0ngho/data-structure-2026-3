#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <cstdio>
#include <cstring>

class Car {
protected:
    int speed;
    char name[40];
public:
    int gear;

    Car() : speed(0), gear(1) { name[0] = '\0'; }
    ~Car() {}
    Car(int s, const char* n, int g) : speed(s), gear(g) {
        strcpy(name, n);
    }

    void changeGear(int g = 4) { gear = g; }
    void speedUp() { speed += 5; }
    void display() {
        printf("[%s] : gear=%d speed=%dkmph\n", name, gear, speed);
    }
    void whereAmI() {
        printf("address = %p\n", this);
    }
};

class SportsCar : public Car {
public:
    bool bTurbo;

    SportsCar() : Car(), bTurbo(false) {}
    SportsCar(int s, const char* n, int g) : Car(s, n, g), bTurbo(false) {}

    void setTurbo(bool bTur) { bTurbo = bTur; }
    void display() {
        printf("[%s] : gear=%d speed=%dkmph turbo=%s\n",
            name, gear, speed, bTurbo ? "ON" : "OFF");
    }

    void speedUp() {
        if (bTurbo) speed += 20;
        else Car::speedUp();
    }
};
