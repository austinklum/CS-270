/*
 * int_stack.c
 *
 *  Created on: Oct 20, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include "int_stack.h"

struct is_node *newNode();
void freeUp(struct is_node *curnode);

int main(int argc, char **argv){
	struct int_stack *myStack = make_stack(1);
	push(myStack, 1);
	push(myStack, 2);
	push(myStack, 3);
	push(myStack, 4);
	print_stack(myStack);
	return 0;
}

struct int_stack *make_stack(size_t node_capacity){
	struct int_stack *stack = malloc(sizeof(struct int_stack));

	/*But I WILL need space for multiple nodes*/
	stack->size = 1;
	stack->node_capacity = node_capacity;
	stack->head = newNode(node_capacity);
	stack->head->next = newNode(node_capacity);
	stack->head->next->contents = 42;

	return stack;
}

/*This creates a single node doesn't use pointers
 * np -> spaceThatIsANode.
 * We want something like:
 * np -> addressToSpaceThatIsANode -> spaceThatIsANode
 * */
struct is_node *newNode(int node_capacity){
	struct is_node *np = malloc(sizeof(struct is_node));

	np->contents = malloc(node_capacity * sizeof(int));
	np->next_index = 0;
	np->next = NULL;

	return np;
}
/*When reset_stack is implemented call reset_stack in here and delete the head*/
void free_stack(struct int_stack *stack){
	struct is_node *curnode = stack->head;
	/*Loop through all the nodes and free them up as you go*/
	while(curnode->next != NULL){
		struct is_node *nextnode = curnode->next;
		/*Free the array and free the node*/
		freeUp(curnode);
		curnode = nextnode;
	}
	free(stack);
}

void push(struct int_stack *stack, int d){
	struct is_node *curnode = stack->head->next;
	/*We know only the first node will not be full
	 * Check if the first node is full well.
	 * */
	if(curnode->next_index > stack->node_capacity){
		/*The first node was full; Create a new node at the top of stack*/
		curnode = newNode(stack->node_capacity);
		curnode->next = stack->head->next;
		stack->head = curnode;
	}

	/*Add to the node content the new data d*/
	curnode->contents[curnode->next_index] = d;
	curnode->next_index++;
	stack->size++;
}

int pop(struct int_stack *stack){
	int retVal = -1;
	if(!is_empty(stack)){
		struct is_node *curnode = stack->head->next;

		/*Save the return value, we may have to delete this node*/
		retVal = curnode->contents[curnode->next_index-1];

		/*Decrement values for we used 1 less index and now have 1 less element*/
		curnode->next_index--;
		stack->size--;

		if(curnode->next_index < 0){
			/*Delete the node*/
			/*Link up head to the next node*/
			stack->head->next = curnode->next;

			/*Manage memory*/
			freeUp(curnode);
		}
	}
	return retVal;
}

/*Return the last index used in the first node
 * If empty return -1
 * */
int top(struct int_stack *stack){
	return !is_empty(stack) ? stack->head->next->contents[stack->head->next->next_index-1] : -1;
}

/*Frees up both the array inside the node and the node itself*/
void freeUp(struct is_node *curnode){
	free(curnode->contents);
	free(curnode);
}

int is_empty(struct int_stack *stack){
	return stack->size == 0;
}

void print_stack(struct int_stack *stack){
	int i;
	/*Nodes are structs; Structs dont point to the actual data*/
	struct is_node *curnode = stack->head->next;
	while(curnode->next != NULL){
		for(i = curnode->next_index; i >= 0; i--){
			printf("%d, ",curnode->contents[i]);
		}
	}
}

