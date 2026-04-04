#include "Car.h"

int main() {
    Car c(0, "Sonata", 1);
    c.display();
    c.speedUp();
    c.changeGear();
    c.display();

    printf("\n");

    SportsCar ferrari(0, "Ferrari", 1);
    ferrari.display();
    ferrari.setTurbo(false);
    ferrari.speedUp();   
    ferrari.display();

    printf("\n");

    ferrari.setTurbo(true);
    ferrari.speedUp();    
    ferrari.display();

    return 0;
}