#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "bithandler.h"
#include "errorhandler.h"

typedef struct node {
	unsigned int frequency;
	unsigned char value;
	struct node* left;
	struct node* right;
} node;

typedef struct tree {
	node* root;
	unsigned int frequency;
} tree;

tree* merge_trees(tree* t1, tree* t2);

void free_node(node* node);

void free_tree(tree* t);

void write_tree(bitwriter* writer, tree* t);

tree* read_tree(bitreader* reader);

void print_node(node* n, int index, int depth);

void print_tree(tree* t);

#endif