//=============================================================================
// bst.c - binary search tree, based on binary tree (bt.h/bt.c)
//=============================================================================
#include "global.h"
#include "bst.h"

//
// Local function prototypes
//

static void _preorder(BST T, int* pos, int* a);
static void _inorder(BST T, int* pos, int* a);
static void _postorder(BST T, int* pos, int* a);
static void _bfs(BST T, int* a, int pos, int max);

//
// Public functions
//

/**
 * @brief Creates a new BST with a value.
 * 
 * Initializes a new binary search tree with a single node containing
 * the specified value. 
 * 
 * @param val The value to store in the new tree.
 * @return New BST.
 */
BST new_BST(int val)
{
    return new_BT(val);
}

/**
 * @brief Adds a value to the BST unless it's a duplicate.
 * 
 * Ensures the binary search tree maintains its properties: if the value is smaller,
 * it goes to the left child, if the value is greater, it goes to the right child,
 * and if the value already exists, it does nothing to prevent duplicates.
 * 
 * @param T Pointer to the root.
 * @param v Value to add.
 * @return Updated BST.
 */
BST bst_add(BST T, int v)
{
    return !T ? new_BST(v) :
           v < get_val(T) ? cons(add(get_LC(T), v), T, get_RC(T)) :
           v > get_val(T) ? cons(get_LC(T), T, add(get_RC(T), v)) :
           /* duplicate */ T;
}

/**
 * @brief Removes a value from the BST.
 * 
 * This function handles the removal of nodes in the binary search tree. If the node
 * has no children, it is simply removed. If the node has one child, the child replaces
 * the node. If the node has two children, the in-order predecessor is used as a replacement
 * to ensure the tree remains ordered.
 * 
 * @param T Pointer to the root.
 * @param val Value to remove.
 * @return Updated BST.
 */
BST bst_rem(BST T, int val) {
    if (!T) return NULL;

    // Search for the value to remove
    if (val < get_val(T)) {
        return cons(bst_rem(get_LC(T), val), T, get_RC(T));
    } else if (val > get_val(T)) {
        return cons(get_LC(T), T, bst_rem(get_RC(T), val));
    }
    // Case 1: Node has no children
    if (!get_LC(T) && !get_RC(T)) {  
        free(T);
        return NULL;
    }
	// Case 2: Node has only left or right child
    if (!get_LC(T)) {  
        BST temp = get_RC(T);  
        free(T);
        return temp;
    }
    if (!get_RC(T)) {  
        BST temp = get_LC(T);  
        free(T);
        return temp;
    }
    // Case 3: Node has two children
    BST maxNode = get_LC(T);
    while (get_RC(maxNode)) maxNode = get_RC(maxNode); 
    set_val(T, get_val(maxNode));
    set_LC(T, bst_rem(get_LC(T), get_val(maxNode)));
    return T;
}

/**
 * @brief Preorder traversal, stores values in array.
 * 
 * Preorder traversal visits the root first, then recursively visits
 * the left and right subtrees. This order is useful for tasks like copying
 * the tree or saving its structure.
 * 
 * @param T Pointer to the root.
 * @param a Array to store results.
 */
void preorder(BST T, int* a)
{
    int pos = 0;
    _preorder(T, &pos, a);
}

/**
 * @brief Inorder traversal, stores values in array.
 * 
 * Inorder traversal visits the left subtree, then the root, then
 * the right subtree. 
 * 
 * @param T Pointer to the root.
 * @param a Array to store results.
 */
void inorder(BST T, int* a)
{
    int pos = 0;
    _inorder(T, &pos, a);
}

/**
 * @brief Postorder traversal, stores values in array.
 * 
 * Postorder traversal visits the left and right subtrees first, 
 * then the root. This order is useful when deleting nodes or performing 
 * cleanup tasks on the tree.
 * 
 * @param T Pointer to the root.
 * @param a Array to store results.
 */
void postorder(BST T, int* a)
{
    int pos = 0;
    _postorder(T, &pos, a);
}

/**
 * @brief Performs BFS traversal and stores results in array.
 * 
 * Breadth-first search (BFS) explores the tree level by level, 
 * starting from the root. This traversal is useful for visualizing 
 * the tree structure or performing level-order operations.
 * 
 * @param T Pointer to the root.
 * @param a Array to store BFS results.
 * @param max Max size of the array.
 */
void bfs(BST T, int* a, int max) {
    _bfs(T, a, 0, max);
}

/**
 * @brief Checks if a value exists in the BST.
 * 
 * This function searches the tree recursively for the given value.
 * It ensures the value exists by checking the left and right subtrees.
 * 
 * @param T Pointer to the root.
 * @param val Value to search for.
 * @return True if found, false otherwise.
 */
bool is_member(BST T, int val)
{
    return !T ? false :
           get_val(T) == val ? true :
           val < get_val(T) ? is_member(get_LC(T), val) : is_member(get_RC(T), val);
}

/**
 * @brief Computes the height of the BST.
 * 
 * The height of a tree is the longest path from the root to a leaf.
 * This function calculates the maximum height recursively by comparing
 * the heights of the left and right subtrees.
 * 
 * @param T Pointer to the root.
 * @return Height of the tree.
 */
int height(BST T)
{
    return !T ? 0 : 1 + (height(get_LC(T)) > height(get_RC(T)) ? height(get_LC(T)) : height(get_RC(T)));
}

/**
 * @brief Computes the size of the BST.
 * 
 * The size of the tree is the total number of nodes. This function
 * recursively calculates the size by summing the nodes in the left and 
 * right subtrees and adding one for the current node.
 * 
 * @param T Pointer to the root.
 * @return Size of the tree.
 */
int size(BST T)
{
    return !T ? 0 : 1 + size(get_LC(T)) + size(get_RC(T));
}

//
// Private helper functions
//

/**
 * @brief Preorder traversal of the tree.
 * 
 * This function is used by `preorder` to recursively visit the root,
 * then left subtree, then right subtree. It stores values in the array
 * in this order.
 * 
 * @param T Pointer to the root.
 * @param pos Position in the array.
 * @param a Array to store results.
 */
static void _preorder(BST T, int* pos, int* a)
{
    if (T) {
        a[(*pos)++] = get_val(T);
        _preorder(get_LC(T), pos, a);
        _preorder(get_RC(T), pos, a);
    }
}

/**
 * @brief Inorder traversal of the tree.
 * 
 * This function is used by `inorder` to recursively visit the left
 * subtree, then root, then right subtree. It stores values in the array
 * in this order, which results in values being stored in ascending order.
 * 
 * @param T Pointer to the root.
 * @param pos Position in the array.
 * @param a Array to store results.
 */
static void _inorder(BST T, int* pos, int* a)
{
    if (T) {
        _inorder(get_LC(T), pos, a);
        a[(*pos)++] = get_val(T);
        _inorder(get_RC(T), pos, a);
    }
}

/**
 * @brief Postorder traversal of the tree.
 * 
 * This function is used by `postorder` to recursively visit the left
 * and right subtrees, then root. It stores values in the array in this
 * order.
 * 
 * @param T Pointer to the root.
 * @param pos Position in the array.
 * @param a Array to store results.
 */
static void _postorder(BST T, int* pos, int* a)
{
    if (T) {
        _postorder(get_LC(T), pos, a);
        _postorder(get_RC(T), pos, a);
        a[(*pos)++] = get_val(T);
    }
}

/**
 * @brief BFS traversal of the tree.
 * 
 * Breadth-first traversal stores the nodes level by level in an array.
 * The non-value nodes are marked with `X` (as defined in `global.h`).
 * 
 * @param T Pointer to the root.
 * @param a Array to store results.
 * @param pos Position in the array.
 * @param max Max size of the array.
 */
static void _bfs(BST T, int* a, int pos, int max)
{
    if (pos >= max) return;
    a[pos] = T ? get_val(T) : X;
    _bfs(get_LC(T), a, pos * 2 + 1, max);
    _bfs(get_RC(T), a, pos * 2 + 2, max);
}
