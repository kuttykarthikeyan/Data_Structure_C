#include <stdio.h>
#include <stdlib.h>

// Define a structure for a key-value pair
struct KeyValuePair {
    int key;
    int value;
    struct KeyValuePair* next; // Pointer to the next element in the chain
};

// Define the hash table
#define TABLE_SIZE 10
struct KeyValuePair* hashTable[TABLE_SIZE];

// Hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(int key, int value) {
    int index = hash(key);

    // Create a new key-value pair
    struct KeyValuePair* newPair = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
    newPair->key = key;
    newPair->value = value;
    newPair->next = NULL;

    // If the index is not yet occupied, insert the new pair
    if (hashTable[index] == NULL) {
        hashTable[index] = newPair;
    } else {
        // If the index is already occupied, add the new pair to the beginning of the chain
        newPair->next = hashTable[index];
        hashTable[index] = newPair;
    }
}

// Function to retrieve the value associated with a key from the hash table
int get(int key) {
    int index = hash(key);
    struct KeyValuePair* current = hashTable[index];

    // Traverse the chain at the given index
    while (current != NULL) {
        if (current->key == key) {
            return current->value; // Found the key, return its associated value
        }
        current = current->next;
    }

    return -1; // Key not found
}

int main() {
    // Example usage
    insert(5, 42);
    insert(10, 99);
    insert(15, 7);

    printf("Value for key 5: %d\n", get(5));
    printf("Value for key 10: %d\n", get(10));
    printf("Value for key 15: %d\n", get(15));

    // Clean up: Free allocated memory
    for (int i = 0; i < TABLE_SIZE; ++i) {
        struct KeyValuePair* current = hashTable[i];
        while (current != NULL) {
            struct KeyValuePair* next = current->next;
            free(current);
            current = next;
        }
        hashTable[i] = NULL;
    }

    return 0;
}
