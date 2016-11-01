#ifndef TREE_H
#define TREE_H

/**
	tree.h
	A data structure for representing a huffman tree.
	This is a binary tree in which every node either has 0 children or 2 children. 
	If a node is a leaf it also has a value. Every node also has a frequency.
*/

#include <stdio.h>
#include <stdlib.h>
#include "bithandler.h"
#include "errorhandler.h"

/**
	A struct for representing a node in a huffman tree. 
*/
typedef struct node {
	//The frequency of a node. This is the sum of the frequency of the left and right child. 
	//If the the left and right child is NULL, the frequency is equal to the frequency of a value in a block of text.  
	unsigned int frequency; 
	unsigned char value; //The value of a node, this is only set for leaves. 
	struct node* left; //The left child, this is NULL if there is no left child.
	struct node* right; //The right child, this is NULL if there is no right child.
} node;

/**
	A struct for representing a huffman tree. 
*/
typedef struct tree {
	node* root; //The root of the tree. 
	unsigned int frequency;  //The frequency of a root. (This is redundant but helps keep the code cleaner.)
} tree;

/**
	The merge tree operation. It merges 2 huffman trees into one. 
	Basically it makes a new tree and adds the root of the both trees as children to the new tree. 
	The frequency of the root of the new tree is the sum of the frequencies of the roots given trees. 
	@param t1, t2 The trees to be merged.
	@return A merged tree with t1 and t2 as children. 
*/
tree* merge_trees(tree* t1, tree* t2);

/**
	Recursive function to free all memory starting from node in the tree and going down. 
	@param node Root of subtree to be freed. 
*/
void free_node(node* node);

/**
	Frees all of the memory taken by a tree.
	@param The tree to be freed. 
*/
void free_tree(tree* t);

/**
	Writes the tree recursively to a bitwriter. 
	It writes 0 if the node is not a leaf and its children, otherwise 1 will be written and the value of the leaf.
	@param bitwriter The bitwriter which should eventually write the bits to an output file. 
	@param t The tree which should be written.
*/
void write_tree(bitwriter* writer, tree* t);

/**
	Reads a tree recursively from a bitreader. The tree should be written with write_tree or formatted in the same way. 
	@param reader The bitwriter from which the tree should be read. 
	@return The tree which was read from the file.
*/
tree* read_tree(bitreader* reader);

/**
	Recursive function which prints a subtree starting from node to stdout.
	@param n The root of the subtree
	@param index The place of the node in the complete huffman tree. 
	@param depth The depth of the node in the complete huffman tree.
*/
void print_node(node* n, int index, int depth);

/**
	Prints a huffman tree to stdout.
	@param t The tree which will be written to stdout.
*/
void print_tree(tree* t);

#endif