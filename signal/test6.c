#include <stdio.h>

int t;

// Swap two integers
void swap(int *x, int *y) {
    t = *x;
    *x = *y;
    *y = t;
}

// Interrupt service routine (ISR)
void isr(void) {
    int x = 7, y = 9;
    swap(&x, &y);
    // Other ISR code here...
    //return;
}

int main(void) {
    int x = 3, y = 4;

    // Some other code...
    isr();

    // Call the swap function to swap the values of x and y in the main function
    swap(&x, &y);

    // Some other code...
    isr();
    printf("y: %d, t: %d", y, t);

    return 0;
}

