//=============================================================================
// avl.c - AVL-tree based on binary search tree (bst.h/bst.c)
//=============================================================================
#include "avl.h"
#include "bst.h"
#define DEBUG 0

//
// Local prototypes
//

static AVL srr(AVL T);  // Single right rotation (LL imbalance)
static AVL slr(AVL T);  // Single left rotation (RR imbalance)
static AVL drr(AVL T);  // Double right rotation (RL imbalance)
static AVL dlr(AVL T);  // Double left rotation (LR imbalance)

//
// Public functions
//

/**
 * @brief Adds a value to the AVL tree and balances the tree.
 *
 * Inserts the value into the AVL tree using BST logic and then balances the tree.
 *
 * @param T The root of the AVL tree.
 * @param val The value to add to the tree.
 * @return The root of the balanced AVL tree.
 */
AVL avl_add(AVL T, int val)
{
    if(DEBUG) printf("avl_add (%d)\n", val);
    T = bst_add(T, val);  
    return balance(T);     
}

/**
 * @brief Removes a value from the AVL tree and balances the tree.
 *
 * Removes the value from the AVL tree using BST logic and then balances the tree.
 *
 * @param T The root of the AVL tree.
 * @param val The value to remove from the tree.
 * @return The root of the balanced AVL tree.
 */
AVL avl_rem(AVL T, int val)
{
    if(DEBUG) printf("avl_rem (%d)\n", val);
    T = bst_rem(T, val);  
    return balance(T);     
}

/**
 * @brief Balances the AVL tree if needed.
 *
 * Checks balance factor and applies the appropriate rotation to restore AVL property.
 *
 * @param T The root of the AVL tree.
 * @return The root of the balanced AVL tree.
 */
AVL balance(AVL T)
{
	if (T == NULL) return T;
    int balanceFactor = height(get_LC(T)) - height(get_RC(T));  

    // Left-Left Case 
    if (balanceFactor > 1) {
        if (height(get_LC(get_LC(T))) >= height(get_LC(get_RC(T)))) {
            return srr(T);  
        } else {
            return dlr(T); 
        }
    }

    // Right-Right Case 
    if (balanceFactor < -1) {
        if (height(get_RC(get_RC(T))) >= height(get_RC(get_LC(T)))) {
            return slr(T); 
        } else {
            return drr(T);  
        }
    } 
    return T;  
}

//
// Private functions
//

/**
 * @brief Single right rotation to fix a Left-Left imbalance.
 *
 * @param T The root of the subtree.
 * @return The new root of the subtree after the rotation.
 */
static AVL srr(AVL T)
{
    if(DEBUG) printf("srr\n");
    AVL newRoot = get_LC(T);  
    set_LC(T, get_RC(newRoot)); 
    set_RC(newRoot, T);  

    return newRoot;  
}

/**
 * @brief Single left rotation to fix a Right-Right imbalance.
 *
 * @param T The root of the subtree.
 * @return The new root of the subtree after the rotation.
 */
static AVL slr(AVL T)
{
    if(DEBUG) printf("slr\n");
    AVL newRoot = get_RC(T);  
    set_RC(T, get_LC(newRoot)); 
    set_LC(newRoot, T); 

    return newRoot;  
}

/**
 * @brief Double right rotation to fix a Right-Left imbalance.
 *
 * @param T The root of the subtree.
 * @return The new root of the subtree after the double rotation.
 */
static AVL drr(AVL T)
{
    if(DEBUG) printf("drr\n");
    T = slr(get_RC(T));  
	return srr(T);  
}

/**
 * @brief Double left rotation to fix a Left-Right imbalance.
 *
 * @param T The root of the subtree.
 * @return The new root of the subtree after the double rotation.
 */
static AVL dlr(AVL T)
{
    if(DEBUG) printf("dlr\n");
    T = srr(get_LC(T));  
	return slr(T);  
}