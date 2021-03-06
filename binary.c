#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

typedef int data_t;
typedef struct node node_t;

struct node{
	
	data_t data;
	node_t *left;
	node_t *right;
} ;

typedef struct {
	
	node_t *head;
	
} tree_t;

tree_t* make_empty_tree(void);
tree_t* insert_into_tree(tree_t *tree, data_t value);
void print_tree(node_t *head);



int main(int argc, char *argv[]) {
	
	printf("Making a new tree\n");
	
	tree_t *tree;
	
	tree = make_empty_tree();
	int i;
	
	
	// make_empty_list should return a pointer to a tree that is not NULL
	if (tree != NULL) {
		printf("Made tree successfully\n");
	} else {
		printf("Failure");
	}
	
	// Head should equal NULL after making an empty tree 
	if (tree->head == NULL) {
		printf("Head is NULL\n");
	} else {
		printf("Head is not null, points to %p\n", tree->head);
	}
	
	while ((scanf("%d", &i)==1)) {
		insert_into_tree(tree, i);
		printf("Inserted i = %d\n", i);
	}
	
	
	print_tree(tree->head);
	free(tree);
	return 0;
	
}

tree_t* make_empty_tree(void) {
	
	
	tree_t *tree;
	tree = (tree_t*)malloc(sizeof(tree_t)); // Allocating space for the tree 
	assert(tree != NULL);					// Checking malloc worked
	tree->head = NULL;
	return tree; 
	
}

tree_t* insert_into_tree(tree_t *tree, data_t value) {
	
	node_t *ptr = tree->head;
	node_t *prev;
	node_t *newnode;
	
	int lastdirection = 0;
	
	newnode = (node_t*)malloc(sizeof(node_t));
	assert(newnode != NULL);
	newnode->data = value;
	newnode->left = NULL;
	newnode->right = NULL;
	
	if (tree->head == NULL) {
		tree->head = newnode;
		return tree;
	}
	
	while (ptr != NULL) {
		prev = ptr;
		if (value <= ptr->data) {
			ptr = ptr->left;
			lastdirection = -1;
		} else {
			ptr = ptr->right;
			lastdirection = 1;
		}
		
	}
	if (lastdirection == -1) {
		prev->left = newnode;
	} else if (lastdirection == 1) {
		prev->right = newnode;
	} else {
		printf("Fatal Error");
		exit(EXIT_FAILURE);
	}
	
	
	return tree;
	
	
}

void print_tree(node_t *head){
	
	if (head == NULL) {
		printf("Empty Tree\n");
		return;
	} 
	
	printf("%d\t", head->data);
	
	if (head->left != NULL) {
		print_tree(head->left);
	} 
	
	if (head->right != NULL ) {
		print_tree(head->right);
	}
	
	
	return;
}

