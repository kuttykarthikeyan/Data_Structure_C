#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7
#define EMPTY -1

int keys = 7;
int values[TABLE_SIZE];
int new_index;

int hash1(int value) {
    return value % keys;
}

int hash2(int value) {
    return (value +5 )%9;
}

void insert(int value) {
    int index = hash1(value);
    int step = hash2(value);

    if (values[index] == EMPTY) {
        values[index] = value;
    } else {
        int i = 1;
        new_index = (index + i * step) % keys;

        while (values[new_index] != EMPTY) {
            i++;
            new_index = (index + i * step) % keys;
        }

        values[new_index] = value;
    }
}

void printTable() {
    printf("Hash Table:\n");
    for (int i = 0; i < keys; ++i) {
        printf("Key %d: %d\n", i, values[i]);
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        values[i] = EMPTY;
    }

    // Example usage
    insert(42);
    insert(99);
    insert(7);

    // Print the hash table
    printTable();

 
    return 0;
}
