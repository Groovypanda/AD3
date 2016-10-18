#include "tree.h"

tree* merge_trees(tree* t1, tree* t2) {
	tree* t = (tree*)allocate_memory(sizeof(tree));
	t->frequency = t1->frequency + t2->frequency;
	t->root = (node*)allocate_memory(sizeof(node));
	t->root->frequency = t->frequency;
	t->root->left = t1->root;
	t->root->right = t2->root;
	t->root->value = '\0';
	free(t1);
	free(t2);
	return t;
}

void print_tree(node* n, int index) {
	if (n->value == '\0') {
		printf("Node  %d has frequency %d\n", index, n->frequency);
		if (n->left) {
			print_tree(n->left, 2 * index + 1);
		}
		if (n->right) {
			print_tree(n->right, 2 * index + 2);
		}
	}
	else {
		printf("Leaf %d has value %d and frequency %d\n", index, n->value, n->frequency);
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