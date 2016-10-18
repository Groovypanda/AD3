#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "errorhandler.h"

typedef struct node {
	unsigned int frequency;
	unsigned char value; //This is zero if not a root
	struct node* left;
	struct node* right;
} node;

typedef struct tree {
	node* root;
	unsigned int frequency;
} tree;

tree* merge_trees(tree* t1, tree* t2);

void print_tree(node* n, int index);

void free_node(node* node);

void free_tree(tree* t);

#endif