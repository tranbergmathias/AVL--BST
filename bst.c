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
static BST find_predecessor(BST T);
static BST find_successor(BST T); 
static BST remove_node(BST T, int val);  
       
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
 * @brief Remove a node with the specified value from a binary search tree.
 *
 * Searches for the node with the given value and calls `remove_node` 
 * to handle the deletion.
 *
 * @param T The root of the binary search tree.
 * @param val The value to remove from the tree.
 * @return BST The updated binary search tree with the node removed.
 */
BST bst_rem(BST T, int val) {
    if (!T) return NULL;

    // Search for the value to remove
    if (val < get_val(T)) {
        set_LC(T, rem(get_LC(T), val));
    } else if (val > get_val(T)) {
        set_RC(T, rem(get_RC(T), val));
    } else {
        // Found
        T = remove_node(T, val);
    }

    return T;
}


/**
 * @brief Preorder traversal, stores values in array.
 * 
 * Preorder traversal visits the root first, then recursively visits
 * the left and right subtrees. 
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
 * then the root.
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
 * starting from the root. 
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
 * This function recursively calculates the size by summing the nodes in the left and 
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
 * then left subtree, then right subtree. 
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
 * subtree, then root, then right subtree. 
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
 * and right subtrees, then root. 
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
 * The non-value nodes are marked with `X` as defined in global.h.
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

/**
 * @brief Find the in-order predecessor of a node in a binary search tree.
 *
 * @param T The current node in the binary search tree.
 * @return BST The predecessor node (rightmost node in the left subtree), or NULL if none exists.
 */
static BST find_predecessor(BST T) 
{
    if (!T || !get_LC(T)) return NULL;

    T = get_LC(T);
    while (get_RC(T))
        T = get_RC(T);

    return T;
}

/**
 * @brief Find the in-order successor of a node in a binary search tree.
 *
 * @param T The current node in the binary search tree.
 * @return BST The successor node (leftmost node in the right subtree), or NULL if none exists.
 */
static BST find_successor(BST T) 
{
    if(!T || !get_RC(T)) return NULL;
    
    T = get_RC(T);
    while(get_LC(T))
        T = get_LC(T);

    return T;
}

/**
 * @brief Remove a node with the given value from the binary search tree.
 *
 * Handles three cases: 
 * 1. Node has no children (leaf node).
 * 2. Node has one child.
 * 3. Node has two children: Replacement is based on subtree heights.
 *
 * @param T The node to remove.
 * @param val The value of the node to be removed.
 * @return BST The updated subtree with the specified node removed.
 */
static BST remove_node(BST T, int val)
{
 // Case 1:
    if (!get_LC(T) && !get_RC(T)) {
        free(T);
        return NULL;
    }
    // Case 2:
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

    // Case 3:
    int left_height = height(get_LC(T));
    int right_height = height(get_RC(T));

    if(left_height >= right_height) 
    {
        BST predecessor = find_predecessor(T);
        set_val(T, get_val(predecessor));
        set_LC(T, rem(get_LC(T), get_val(predecessor)));
    } 
        else 
    {

        BST successor = find_successor(T);
        set_val(T, get_val(successor));
        set_RC(T, rem(get_RC(T), get_val(successor))); 
    }

    return T;
}