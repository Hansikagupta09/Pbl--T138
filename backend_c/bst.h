#ifndef BST_H
#define BST_H

#include "models.h"

typedef struct BSTNode {
    Food food;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *insertFood(BSTNode *root, Food food);
BSTNode *searchFood(BSTNode *root, int id);
void inorderFood(BSTNode *root);
void freeBST(BSTNode *root);

#endif
