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
	node_t *previous;
	int depth;
	int balance;
} ;

typedef struct {
	
	node_t *head;
	
} tree_t;

tree_t* make_empty_avl_tree(void);
int height_tree(node_t *head);
tree_t* insert_into_avl_tree(tree_t *tree, data_t value);
tree_t *right_rotate(tree_t *tree, node_t *pivot);
void print_tree(node_t *head);

int main(int argc, char *argv[]) {
	
	printf("Making a new tree\n");
	
	tree_t *tree;
	
	tree = make_empty_avl_tree();
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
		insert_into_avl_tree(tree, i);
		printf("Inserted i = %d\n", i);
	}
	
	
	
	//Demonstrating right rotation at head of tree (Use input 3 2 1 to test )
	print_tree(tree->head);
	tree = right_rotate(tree, tree->head);
	printf("\n");
	print_tree(tree->head);
	free(tree);
	return 0;
	
}


tree_t* make_empty_avl_tree(void) {
	
	
	tree_t *tree;
	tree = (tree_t*)malloc(sizeof(tree_t)); // Allocating space for the tree 
	assert(tree != NULL);					// Checking malloc worked
	tree->head = NULL;
	return tree; 
	
}

tree_t* insert_into_avl_tree(tree_t *tree, data_t value) {
	
	node_t *ptr = tree->head;
	node_t *prev;
	node_t *newnode;
	
	int lastdirection = 0;
	
	newnode = (node_t*)malloc(sizeof(node_t));
	assert(newnode != NULL);
	newnode->data = value;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->previous = NULL;
	
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
	
	newnode->previous = prev;
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

tree_t *right_rotate(tree_t *tree, node_t *pivot) {
	
	if (pivot->previous == NULL) {		 // Case when pivot is the head of tree
		
		if (pivot->left !=NULL) { 							// Left Left case
			pivot->previous = pivot->left;
			pivot->left->previous = NULL;
			pivot->left->right = pivot;
			pivot->left = NULL;
		} else {											// Right Left Case
			pivot->previous = pivot->right;
			pivot->right->previous = pivot->right->left;
			pivot->right->left->right = pivot->right;
			pivot->right = pivot->right->left;
			pivot->right->right->right = NULL;
		}
		tree->head = pivot->previous;
		
	} else { 							// Cases when pivot is not head of tree
		
		pivot->left->previous = pivot->previous;
		pivot->left->right = pivot;
		
		if (pivot->previous->left == pivot) { 				// Left Left Case
			pivot->previous->left = pivot->left;
			
		} else {											// Right Left Case
			pivot->previous->right = pivot->left;
		}
		pivot->previous = pivot->left;
		pivot->left = NULL;
		
	}
	return tree;
	
}

int height_tree(node_t *head) {
	int left, right;
	
	if ((head->left == NULL) && (head->right == NULL)) { //When end of branch reached
		head->depth = 1;
		return 1;
		
	} else if ((head->left == NULL) && (head->right != NULL)) {
		head->depth = height_tree(head->right);
		return  head->depth + 1;
		
	} else if ((head->left != NULL) && (head->right == NULL)) {
		head->depth = height_tree(head->left);
		return head->depth + 1;
	} else {
		left  = height_tree(head->left) + 1;
		right = height_tree(head->right) +1;
		if (left >= right) {
			head->depth = left;
			return left;
		} else {
			head->depth = right;
			return right;
		}
	}
	
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

