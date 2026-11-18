#include "pyc.h"

/* Python classes map naturally to C structs + functions. */
typedef struct {
    const char *name; /* borrowed; this example does not own the string */
    int age;
} Person;

static void person_greet(const Person *self) {
    printf("Hello, %s (age %d)\n", self->name, self->age);
}

PYC_VECTOR(int, IntList)

int main(void) {
    Person person = { .name = "Ada", .age = 36 };
    person_greet(&person);
    print("A tiny Python-inspired C17 starter");
    print((bool)true); /* C17 true is an int macro; cast for bool dispatch. */
    print(3.14);

    IntList xs = {0};
    if (!IntList_push(&xs, 10) || !IntList_push(&xs, 20)) {
        fputs("allocation failed\n", stderr);
        IntList_free(&xs);
        return 1;
    }
    print(xs.items[0]);
    IntList_free(&xs);

    /* Opt-in interactive input:
       char *name = pyc_input("Your name: ");
       if (name) { print(name); free(name); }
    */
    return 0;
}
