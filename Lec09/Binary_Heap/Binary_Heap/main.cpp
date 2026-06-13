#include "MinHeap.h"

int main() {
    MinHeap h;
    int vals[] = { 3, 10, 5, 2, 10, 4, 18, 15, 17, 6 };
    for (int v : vals) h.insert(v);
    h.display();
    printf("remove: %d\n", h.remove());
    printf("remove: %d\n", h.remove());
    printf("remove: %d\n", h.remove());
    h.display();
    return 0;
}
