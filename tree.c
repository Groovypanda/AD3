#include "tree.h"

tree* merge_trees(tree* t1, tree* t2) {
	tree* t = (tree*)allocate_memory(sizeof(tree));
	t->frequency = t1->frequency + t2->frequency;
	t->root = (node*)allocate_memory(sizeof(node));
	t->root->frequency = t->frequency;
	t->root->left = t1->root;
	t->root->right = t2->root;
	free(t1);
	free(t2);
	return t;
}

void print_tree(tree* t) {
	if (t->root) {
		print_node(t->root, 0, 0);
	}
	else {
		printf("The tree is completely empty");
	}
}


void print_node(node* n, int index, int depth) {
	if (n->left && n->right) {
		printf("Node  %d (%d)\n", index, depth);
		print_node(n->left, 2 * index + 1, depth+1);
		print_node(n->right, 2 * index + 2, depth+1);
	}
	else {
		printf("Leaf %d (%d) has value %d\n", index, depth, n->value);
	}

}

void free_node(node* node) {
	if (node->left) {
		free_node(node->left);
	}
	if (node->right) {
		free_node(node->right);
	}
	free(node);
}

void free_tree(tree* t) {
	free_node(t->root);
	free(t);
}

void write_tree_recurse(bitwriter* writer, node* n) {
	if (n->left && n->right) {
		write_bits(writer, 0, 1);
		write_tree_recurse(writer, n->left);
		write_tree_recurse(writer, n->right);
	}
	else {
		write_bits(writer, 1, 1);
		write_bits(writer, n->value, 8);
	}
}

void write_tree(bitwriter* writer, tree* t) {
	if (t->root) {
		write_tree_recurse(writer, t->root);
	}
}

void read_tree_recurse(bitreader* reader, node* n) {
	n->frequency = 0;
	unsigned int bit = read_bits(reader, 1);
	if (bit) {
		n->value = read_bits(reader, 8);
		n->left = NULL;
		n->right = NULL;
	}
	else {
		n->left = (node*)allocate_memory(sizeof(node));
		n->right = (node*)allocate_memory(sizeof(node));
		read_tree_recurse(reader, n->left);
		read_tree_recurse(reader, n->right);
	}
}

tree* read_tree(bitreader* reader) {
	tree* t = (tree*)allocate_memory(sizeof(tree));
	t->root = (node*)allocate_memory(sizeof(node));
	read_tree_recurse(reader, t->root);
	return t;
}
