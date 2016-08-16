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
	int depth_down;
} ;

typedef struct {
	
	node_t *head;
	int num_nodes;
	int tree_depth;
	
} tree_t;

tree_t* make_empty_avl_tree(void);
node_t *create_node(void);
tree_t* insert_into_avl_tree(tree_t *tree, data_t value);
int height_tree(node_t *head);
int is_in_tree(node_t *node, data_t value);

void depth_down_values(node_t *node, int top);



tree_t *right_rotate(tree_t *tree, node_t *pivot);
void print_tree(node_t *head);




int main(int argc, char *argv[]) {
	
	int i;
	
	
	printf("Making a new tree\n");
	tree_t *tree;
	tree = make_empty_avl_tree();
	
	printf("Enter intergers to insert inton tree: ");
	while ((scanf("%d", &i)==1)) {
		insert_into_avl_tree(tree, i);
		printf("Inserted i = %d\n", i);
	}
	
	
	printf("The height of the tree is %d, the number of nodes is %d\n", height_tree(tree->head), tree->num_nodes);
	
	printf("Enter a value to check if it is in the tree: ");
	if (scanf("%d", &i) == 1) {
		if (is_in_tree(tree->head, i)) {
			printf("%d is in the tree\n", i);
		} else {
			printf("%d is not in tree\n", i);
		}
		
	} else {
		printf("Unsuccessful Insertion\n");
	}
	
	tree->head->depth_down = 0;
	
	depth_down_values(tree->head, 0);
	
	tree->tree_depth = tree->head->depth;
	print_tree(tree->head);
	
	return 0;
	
}


tree_t* make_empty_avl_tree(void) {
	
	
	tree_t *tree;
	tree = (tree_t*)malloc(sizeof(tree_t)); // Allocating space for the tree 
	assert(tree != NULL);					// Checking malloc worked
	tree->head = NULL;
	tree->num_nodes = 0;
	return tree; 
	
}

node_t *create_node(void) {
	
	node_t *node;
	node = (node_t*)malloc(sizeof(node_t));
	assert(node != NULL);
	node->previous = NULL;
	node->left = NULL;
	node->right = NULL;
	node->depth = 1;
	node->balance = 0;
	
	return node;
}

tree_t* insert_into_avl_tree(tree_t *tree, data_t value) {
	
	node_t *ptr = tree->head;
	node_t *above;
	node_t *newnode;
	
	int lastdirection = 0;
	
	newnode = create_node();
	newnode->data = value;
	tree->num_nodes++;

	
	if (tree->head == NULL) {
		tree->head = newnode;
		return tree;
	}
	
	
	// Using -1 to indictate ptr last moved left and 1 for last moved right
	// Above is the node above ptr
	while (ptr != NULL) {
		above = ptr;
		if (value <= ptr->data) {
			ptr = ptr->left;
			lastdirection = -1;
		} else {
			ptr = ptr->right;
			lastdirection = 1;
		}
		
	}
	
	newnode->previous = above;
	if (lastdirection == -1) {
		above->left = newnode;
	} else if (lastdirection == 1) {
		above->right = newnode;
	} else {
		printf("Fatal Error");
		exit(EXIT_FAILURE);
	}
	
	
	return tree;
	
	
}

// Node inserted should be the trees head
int is_in_tree(node_t *node, data_t value) {
	
	if (value == node->data) {
		return 1;
		
	} else if (value <= node->data && node->left != NULL) {
		return is_in_tree(node->left, value);
		
	} else if (value > node->data && node->right != NULL) {
		return is_in_tree(node->right, value);
		
	} else {
		return 0;
	}

	
}

tree_t *right_rotate(tree_t *tree, node_t *pivot) {
	
	if (pivot->previous == NULL) {		 // Case when pivot is the head of tree
		
		if (pivot->left !=NULL) { 							// Left Left case
			pivot->previous = pivot->left;
			pivot->left->previous = NULL;
			pivot->left->right = pivot;
			pivot->left = NULL;
			tree->head = pivot->previous;
		} else {											// Right Left Case
			pivot->right->previous = pivot->right->left;
			pivot->right->left->right = pivot->right;
			pivot->right = pivot->right->left;
			pivot->right->right->left = NULL;
			pivot->right->previous = pivot;
		}
		
		
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
	
	int i;
	
	if (head->right != NULL) {
		print_tree(head->right);
	} else {
		for (i = 0; i <= head->depth_down + 1; i++) {
			printf("____");
		}
	}
	
	
	
	printf("\n");
	
	for (i = 0; i <= head->depth_down; i++) {
		printf("____");
	}
	printf("%d\n", head->data);
		
		
		
		
		
		
	if (head->left != NULL) {
		print_tree(head->left);
	} else {
		for (i = 0; i <= head->depth_down + 1; i++) {
			printf("____");
		}
	}
	
	return;
}

void depth_down_values(node_t *node, int top) {
	
	node->depth_down = top;
	
	if (node->left != NULL) {
		depth_down_values(node->left, top+1);
	}
	
	if (node->right != NULL) {
		depth_down_values(node->right, top+1);
	}
	
	return;
}

