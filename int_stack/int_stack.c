/*
 * int_stack.c
 *
 *  Created on: Oct 20, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include <stdlib.h>
#include "int_stack.h"

struct is_node *newNode();
void freeUp(struct is_node *curnode);

struct int_stack *make_stack(int node_capacity){
	/*Allocate space for the stack*/
	struct int_stack *stack = malloc(sizeof(struct int_stack));

	/*Head is a sentinel node. Do not ask for the value of the head*/
	stack->head = newNode(node_capacity);

	/*Set default values*/
	stack->size = 0;
	stack->node_capacity = node_capacity;

	return stack;
}

/*
 * Creates a new node.
 * */
struct is_node *newNode(int node_capacity){
	/*Allocate space for the node*/
	struct is_node *np = malloc(sizeof(struct is_node));

	/*Allocate space for the array*/
	np->contents = malloc(node_capacity * sizeof(int));

	/*Set to default values*/
	np->next_index = 0;
	np->next = NULL;

	return np;
}

void free_stack(struct int_stack *stack){
	/*Free up the contents of the stack*/
	reset_stack(stack);

	/*Free up the head and the stack itself*/
	freeUp(stack->head);
	free(stack);
}

void reset_stack(struct int_stack *stack){
	/*Skip the head*/
	struct is_node *curnode = stack->head->next;
	/*Loop through all the nodes and free them up as you go*/
	while(curnode != NULL){
		struct is_node *nextnode = curnode->next;
		/*Free the array and free the node*/
		freeUp(curnode);
		curnode = nextnode;
	}
	/*Make the head "believe" it is nothing*/
	stack->head->next = NULL;
	stack->head->next_index = 0;
	stack->size = 0;
}

void push(struct int_stack *stack, int d){
	struct is_node *curnode = stack->head;
	/*We know only the first node will not be full
	 * Check if the first node is full.
	 * */
	if(curnode->next_index == stack->node_capacity){
		/*The first node was full; Create a new node at the top of stack*/
		curnode = newNode(stack->node_capacity);
		curnode->next = stack->head;
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
		struct is_node *curnode = stack->head;

		/*Save the return value, we may have to delete this node*/
		retVal = curnode->contents[curnode->next_index-1];

		/*Decrement values for we used 1 less index and now have 1 less element*/
		curnode->next_index--;
		stack->size--;

		if(curnode->next_index == 0 && curnode->next != NULL){
			/*Delete the node*/
			/*Link up head to the next node*/
			stack->head = curnode->next;

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
	return !is_empty(stack) ? stack->head->contents[stack->head->next_index-1] : -1;
}

/*Frees up both the array inside the node and the node itself*/
void freeUp(struct is_node *curnode){
	curnode->next = NULL;
	free(curnode->contents);
	free(curnode);
}

int is_empty(struct int_stack *stack){
	return stack->size == 0;
}

/*
 * This is a little ugly, but it works.
 * */
void print_stack(struct int_stack *stack){
	int i;
	struct is_node *curnode = stack->head;
	if(!is_empty(stack)){
		/*The first node may not be full*/
		if(curnode->next_index < stack->node_capacity){
			printf("(");
			for(i = curnode->next_index-1; i > 0; i--){
				printf("%d,",curnode->contents[i]);
			}
			printf("%d]",curnode->contents[0]);
			curnode = curnode->next;
		}

		/*Standard case: The node is full*/
		while(curnode != NULL){
			printf("[");
			for(i = curnode->next_index-1; i > 0; i--){
				printf("%d,",curnode->contents[i]);
			}
			printf("%d]",curnode->contents[0]);
			curnode = curnode->next;
		}
	} else {
		printf("(]");
	}
	printf("\n");
}

