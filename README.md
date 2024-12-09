# Lab: tree-based data structures
This document provides a cheat-sheet on how to work with the provided
start-code.

## Use available options
```
$ ./tree -h
USAGE: tree [flags]
	-h	-- help
	-m avl	-- AVL mode
	-e	-- echo input
```

As shown above, you can specify if the program should use a BST or an AVL tree.
The default is BST, and you can change it by setting the AVL mode:
- Run in BST mode: `./tree`
- Run in AVL mode: `./tree -m avl`

The echo option is useful if you want to redirect input from a file. It will
cause each input to be printed to stdout.
- Run normally: `./tree`
- Run with input from file: `./tree -e < data/some_input.txt`
- Run with input from file and output to another file:
	`./tree -e < data/some_input.txt > data/output.txt` 

## Structure
```
AVL-BST/
│
├── Makefile
├── src/
│   ├── global.c
│   ├── main.c
│   ├── ui.c
│   ├── bt.c
│   ├── bst.c
│   ├── avl.c
│   └── main_test.c
│
├── header/
│   ├── global.h
│   ├── ui.h
│   ├── bt.h
│   ├── bst.h
│   └── avl.h
│
├── build/
│   ├── global.o
│   ├── main.o
│   ├── ui.o
│   ├── bt.o
│   ├── bst.o
│   ├── avl.o
│   ├── main_test.o
│   ├── tree        # Main executable
│   └── test        # Test executable
└── data/

```
