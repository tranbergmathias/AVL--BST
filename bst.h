#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bt.h"

typedef BT* BST;

// Public function declarations
BST new_BST(int val);                  // Creates a new binary search tree with a given value
BST bst_add(BST T, int v);             // Adds a value to the binary search tree
BST bst_rem(BST T, int val);           // Removes a value from the binary search tree
int height(BST T);                     // Returns the height of the binary search tree
int size(BST T);                       // Returns the size of the binary search tree
bool is_member(BST T, int val);        // Checks if a value is present in the binary search tree
void preorder(BST T, int* a);          // Preorder traversal 
void inorder(BST T, int* a);           // Inorder traversal 
void postorder(BST T, int* a);         // Postorder traversal 
void bfs(BST T, int* a, int max);      // BFS traversal

#endif