#include "pyc.h"

PYC_VECTOR(int, IntList)

int main(void) {
    IntList xs = {0};
    for (int i = 0; i < 100; ++i) {
        if (!IntList_push(&xs, i)) return 1;
    }
    if (xs.len != 100 || xs.items[0] != 0 || xs.items[99] != 99) return 2;
    IntList_free(&xs);
    if (xs.items != NULL || xs.len != 0 || xs.cap != 0) return 3;
    return 0;
}
