#include "ui.h"
#include "global.h"
static bool echo = false;

/**
 * @brief Prints the Binary Search Tree (BST) in various formats.
 * @param T The root of the BST.
 */
void print_tree(BST T)
{
	int max_n = pow(2, height(T));
	int* arr = (int*)calloc(MAX, sizeof(int));
	bfs(T, arr, max_n);
	if (!T)
		printf("\nTree is empty\n\n\n");
	else
		print_2d(arr, max_n - 1);

	printf("Size:\t\t%d\n", size(T));
	printf("Height:\t\t%d\n", height(T));
	printf("Preorder:\t"); preorder(T, arr); print_array(arr, size(T));
	printf("Inorder:\t"); inorder(T, arr); print_array(arr, size(T));
	printf("Postorder:\t"); postorder(T, arr); print_array(arr, size(T));
	printf("BFS star:\t"); bfs(T, arr, max_n); print_array(arr, max_n - 1);
	free(arr);
}

/**
 * @brief Prints the contents of an integer array.
 * @param a The array to print.
 * @param size The number of elements in the array.
 */
void print_array(int* a, int size)
{
	printf("[");
	if (size == 0) { printf("]\n"); return; }
	for (int i = 0; i < size; i++)
		if (a[i] != X)
			printf("%d%s", a[i], i < size - 1 ? ", " : "]");
		else
			printf("'*'%s", i < size - 1 ? ", " : "]");
	printf("\n");
}

/**
 * @brief Prints a binary tree in a 2D.
 * @param a The BFS array representing the tree.
 * @param maxnodes The maximum number of nodes in the tree.
 */
void print_2d(int* a, int maxnodes)
{
    printf("\nTree 2D\n");

    int max_level = (int)log2(maxnodes); 
    int space_between_nodes = (int)pow(2, max_level + 1) - 1; 

    for (int i = 0; i <= max_level; i++) {
        int leading_spaces = space_between_nodes / 2;
        for (int j = 0; j < leading_spaces; j++) printf(" ");

        for (int j = 0; j < (int)pow(2, i); j++) {
            int idx = (int)(pow(2, i) - 1 + j);
            if (idx < maxnodes && a[idx] != X) printf("%d", a[idx]);
            else printf("*");

            if (j < (int)pow(2, i) - 1)
                for (int k = 0; k < space_between_nodes; k++) printf(" ");
        }
        space_between_nodes = space_between_nodes / 2;
        printf("\n");
    }
}

/**
 * @brief Prints the menu options.
 */
void print_menu()
{
	printf("********************************\n");
	printf("m : menu\n");
	printf("t : display tree\n");
	printf("a : add value\n");
	printf("d : delete value\n");
	printf("f : test membership\n");
	printf("q : quit\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/**
 * @brief Gets a single character input from the user.
 * @param prompt The message to display before input.
 * @return The character input by the user.
 */
char get_choice(char* prompt)
{
	printf("%s", prompt);
	char buf[BUFSIZE];
	fgets(buf, BUFSIZE - 1, stdin);
	if (echo) printf("%c\n", buf[0]);
	return buf[0];
}

/**
 * @brief Gets an integer input from the user.
 * @param prompt The message to display before input.
 * @return The integer input by the user, or X if invalid.
 */
int get_int(char* prompt)
{
	printf("%s", prompt);
	char buf[BUFSIZE];
	fgets(buf, BUFSIZE - 1, stdin);
	if (!isdigit(buf[0])) return X;
	return atoi(buf);
}

/**
 * @brief Prompts the user to add an element to the BST.
 * @param T The root of the BST.
 * @return The updated BST with the new element added.
 */
BST ui_add(BST T)
{
	int val;
	do {
		val = get_int("Enter value to be added> ");
		if (val == X) printf("Error: not allowed in tree\n");
	} while (val == X);
	if (echo) printf("%d\n", val);
	return add(T, val);
}

/**
 * @brief Prompts the user to remove an element from the BST.
 * @param T The root of the BST.
 * @return The updated BST with the specified element removed.
 */
BST ui_rem(BST T)
{
	int val;
	do {
		val = get_int("Enter value to be deleted> ");
		if (val == X) printf("Error: not allowed in tree\n");
	} while (val == X);
	if (echo) printf("%d\n", val);
	return rem(T, val);
}

/**
 * @brief Prompts the user to search for an element in the BST.
 * @param T The root of the BST.
 */
void ui_find(BST T)
{
	int val;
	do {
		val = get_int("Enter value to search for> ");
		if (val == X) printf("Error: not allowed in tree\n");
	} while (val == X);
	if (echo) printf("%d\n", val);
	printf("%d is a%smember\n", val, is_member(T, val) ? " " : " non-");
}

/**
 * @brief Runs the main menu system for BST/AVL operations.
 * @param m Mode: 'a' for AVL mode, any other value for BST mode.
 * @param e Echo mode: true to enable input echo, false otherwise.
 */
void run(char m, bool e)
{
	char val;
	BST T = NULL;
	add = (m == 'a') ? avl_add : bst_add; // setting "polymorphic" function for add
	rem = (m == 'a') ? avl_rem : bst_rem; // setting "polymorphic" function for rem
	echo = e;

	printf("[INFO] running in %s mode\n", m == 'a' ? "AVL" : "BST");
	print_menu();
	do {
		val = get_choice("menu> ");
		switch (val) {
			case 'm': print_menu(); break;
			case 't': print_tree(T); break;
			case 'a': T = ui_add(T); break;
			case 'd': T = ui_rem(T); break;
			case 'f': ui_find(T); break;
			case 'q': break;
			default: printf("Unknown command (%c)\n", val); break;
		}
	} while (val != 'q');
}
