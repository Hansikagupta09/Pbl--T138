#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTNode *insertFood(BSTNode *root, Food food) {
    if (root == NULL) {
        BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
        if (newNode == NULL) return NULL;

        newNode->food = food;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (food.id < root->food.id)
        root->left = insertFood(root->left, food);
    else if (food.id > root->food.id)
        root->right = insertFood(root->right, food);

    return root;
}

BSTNode *searchFood(BSTNode *root, int id) {
    if (root == NULL || root->food.id == id)
        return root;

    if (id < root->food.id)
        return searchFood(root->left, id);

    return searchFood(root->right, id);
}

void inorderFood(BSTNode *root) {
    if (root == NULL) return;

    inorderFood(root->left);
    printf("Food ID: %d | %s | Qty: %d | Expiry: %d days\n",
           root->food.id,
           root->food.name,
           root->food.quantity,
           root->food.days_to_expire);
    inorderFood(root->right);
}

void freeBST(BSTNode *root) {
    if (root == NULL) return;

    freeBST(root->left);
    freeBST(root->right);
    free(root);
}
