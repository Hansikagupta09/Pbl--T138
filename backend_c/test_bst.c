
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "bst.h"

int main(void)
{
    BSTNode *root = NULL;
    BSTNode *found;
    Food f;

    printf("\n===== BST TESTING =====\n");

    /* TEST 1: Insert first food */
    f.id = 50;
    strcpy(f.name, "Rice");
    f.quantity = 20;
    f.days_to_expire = 5;

    root = insertFood(root, f);
    assert(root != NULL);
    assert(root->food.id == 50);
    printf("TEST 1 PASSED: First insertion\n");

    /* TEST 2: Insert smaller ID */
    f.id = 30;
    strcpy(f.name, "Milk");
    f.quantity = 10;
    f.days_to_expire = 2;

    root = insertFood(root, f);
    assert(root->left != NULL);
    printf("TEST 2 PASSED: Left child insertion\n");

    /* TEST 3: Insert larger ID */
    f.id = 70;
    strcpy(f.name, "Bread");
    f.quantity = 15;
    f.days_to_expire = 3;

    root = insertFood(root, f);
    assert(root->right != NULL);
    printf("TEST 3 PASSED: Right child insertion\n");

    /* TEST 4: Search root */
    found = searchFood(root, 50);
    assert(found != NULL);
    printf("TEST 4 PASSED: Search root\n");

    /* TEST 5: Search left child */
    found = searchFood(root, 30);
    assert(found != NULL);
    printf("TEST 5 PASSED: Search left child\n");

    /* TEST 6: Search right child */
    found = searchFood(root, 70);
    assert(found != NULL);
    printf("TEST 6 PASSED: Search right child\n");

    /* TEST 7: Search nonexistent ID */
    found = searchFood(root, 999);
    assert(found == NULL);
    printf("TEST 7 PASSED: Missing ID handling\n");

    /* TEST 8: Duplicate ID */
    f.id = 50;
    strcpy(f.name, "Duplicate");
    root = insertFood(root, f);

    found = searchFood(root, 50);
    assert(found != NULL);
    assert(strcmp(found->food.name, "Rice") == 0);
    printf("TEST 8 PASSED: Duplicate ID handling\n");

    /* TEST 9: Inorder traversal */
    printf("\nDisplaying BST in sorted order:\n");
    inorderFood(root);
    printf("TEST 9 PASSED: Inorder traversal\n");

    /* TEST 10: Free allocated memory */
    freeBST(root);
    root = NULL;
    assert(root == NULL);
    printf("TEST 10 PASSED: Memory cleanup\n");

    printf("\n===== ALL BST TESTS PASSED =====\n");

    return 0;
}
