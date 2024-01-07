#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the AVL tree
struct node {
    struct node *lc;  // Left child
    int data;         // Data value
    int height;       // Height of the node
    struct node *rc;  // Right child
};

// Global root of the AVL tree
struct node *root = NULL;

// Function to create a new node with a given value
struct node *newnode(int val) {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->lc = temp->rc = NULL;
    temp->data = val;
    temp->height = 0;
    return temp;
}

// Function to find the maximum of two integers
int maximum(int a, int b) {
    return (a > b) ? a : b;
}

// Function to get the height of a node
int height(struct node *t) {
    if (t == NULL)
        return -1;
    else
        return t->height;
}

// Right-Right rotation
struct node *RR(struct node *K2) {
    struct node *K1 = K2->lc;
    K2->lc = K1->rc;
    K1->rc = K2;
    K2->height = maximum(height(K2->lc), height(K2->rc)) + 1;
    K1->height = maximum(height(K1->lc), height(K1->rc)) + 1;
    return K1;
}

// Left-Left rotation
struct node *LL(struct node *K2) {
    struct node *K1 = K2->rc;
    K2->rc = K1->lc;
    K1->lc = K2;
    K2->height = maximum(height(K2->lc), height(K2->rc)) + 1;
    K1->height = maximum(height(K1->lc), height(K1->rc)) + 1;
    return K1;
}

// Right-Left rotation
void RL(struct node *K3) {
    K3->rc = RR(K3->rc);
    K3 = LL(K3);
}

// Left-Right rotation
void LR(struct node *K3) {
    K3->lc = LL(K3->lc);
    K3 = RR(K3);
}

// Binary search tree insertion
struct node *bsinsert(struct node *root, int val) {
    if (root == NULL)
        return newnode(val);

    if (root->data > val)
        root->lc = bsinsert(root->lc, val);
    else if (root->data < val)
        root->rc = bsinsert(root->rc, val);

    // Update height of current node
    root->height = maximum(height(root->lc), height(root->rc)) + 1;

    // Calculate balance factor directly
    int balance = height(root->lc) - height(root->rc);

    // Perform rotations if needed
    if (balance > 1 && val < root->lc->data)
        return RR(root);
    if (balance > 1 && val > root->lc->data) {
        LR(root);
        return RR(root);
    }
    if (balance < -1 && val > root->rc->data)
        return LL(root);
    if (balance < -1 && val < root->rc->data) {
        RL(root);
        return LL(root);
    }

    return root;
}

// In-order traversal of the AVL tree
void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->lc);
        printf("%d ", root->data);
        inorder(root->rc);
    }
}

// Post-order traversal of the AVL tree
void postorder(struct node *root) {
    if (root != NULL) {
        postorder(root->lc);
        postorder(root->rc);
        printf("%d ", root->data);
    }
}

// Main function with a menu-driven interface
int main() {
    int opt, val;
    while (1) {
        printf("\n1.Insert\n2.Inorder\n3.Postorder\n4.Exit\n");
        printf("Enter the option: ");
        scanf("%d", &opt);

        switch (opt) {
        case 1:
            printf("\nEnter value: ");
            scanf("%d", &val);

            if (root == NULL)
                root = newnode(val);
            else
                root = bsinsert(root, val);

            break;
        case 2:
            if (root == NULL)
                printf("No values to display\n");
            else
                inorder(root);
            printf("\n");
            break;
        case 3:
            if (root == NULL)
                printf("No values to display\n");
            else
                postorder(root);
            printf("\n");
            break;
        case 4:
            return 0;
        }
    }
}
