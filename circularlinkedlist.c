#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to insert a new node at the end of the circular linked list
void insert(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        // If the list is empty, make the new node the head and form a loop
        *head = newNode;
        newNode->next = *head;
    } else {
        // Traverse the list to find the last node and update its next pointer
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

// Function to delete a node with a specific value from the circular linked list
void deleteNode(struct Node** head, int value) {
    if (*head == NULL) {
        // If the list is empty, cannot delete
        printf("Circular Linked List is empty. Cannot delete.\n");
        return;
    }

    struct Node* current = *head;
    struct Node* prev = NULL;

    // Find the node to be deleted and its previous node
    while (current->data != value && current->next != *head) {
        prev = current;
        current = current->next;
    }

    // If the node is found
    if (current->data == value) {
        // If it's the only node in the list
        if (current->next == *head) {
            if (prev == NULL) {
                // It's the only node, make the list empty
                *head = NULL;
            } else {
                // Update the previous node's next pointer to the head
                prev->next = *head;
            }
        } else {
            // If it's not the only node, update the previous node's next pointer
            if (prev == NULL) {
                // It's the first node, update the head
                *head = current->next;
            } else {
                prev->next = current->next;
            }
        }

        // Reuse the memory of the deleted node (optional, but not freeing it)
        // You can perform additional operations on the node if needed

        printf("Node with value %d deleted successfully.\n", value);
    } else {
        printf("Node with value %d not found in the Circular Linked List.\n", value);
    }
}

// Function to display the circular linked list
void display(struct Node* head) {
    if (head == NULL) {
        // If the list is empty, print a message
        printf("Circular Linked List is empty.\n");
        return;
    }

    struct Node* temp = head;
    while (temp->next != head) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    // Print the last node
    printf("%d\n", temp->data);
}

// Main function
int main() {
    struct Node* myList = NULL;
    int choice, value;

    printf("Menu:\n");
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Display\n");
    printf("4. Exit\n");

    while (1) {
        // Display menu options
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert a new node
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insert(&myList, value);
                break;

            case 2:
                // Delete a node
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                deleteNode(&myList, value);
                break;

            case 3:
                // Display the circular linked list
                printf("Circular Linked List: ");
                display(myList);
                break;

            case 4:
                // Exit the program
                printf("Exiting the program.\n");
                exit(0);

            default:
                // Invalid choice
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
