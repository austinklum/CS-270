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
	struct int_stack *myStack = make_stack(5);
//	printf("%d\n", top(myStack));
	push(myStack, 1);
	push(myStack, 2);
	push(myStack, 3);
	push(myStack, 4);
	print_stack(myStack);
	reset_stack(myStack);
	printf("Printing stack.\n");
	print_stack(myStack);
	push(myStack, 5);
	//print_stack(myStack);
	return 0;
}

struct int_stack *make_stack(size_t node_capacity){
	/*Allocate space for the stack*/
	struct int_stack *stack = malloc(sizeof(struct int_stack));

	/*Head is a sentinel node. Do not ask for the value of the head*/
	stack->head = newNode(node_capacity);

	/*Set default values*/
	stack->size = 0;
	stack->node_capacity = node_capacity;

	return stack;
}

/*This creates a single node doesn't use pointers
 * np -> spaceThatIsANode.
 * We want something like:
 * np -> addressToSpaceThatIsANode -> spaceThatIsANode
 * */
struct is_node *newNode(int node_capacity){
	/*Allocate space for the node*/
	struct is_node *np = malloc(sizeof(struct is_node));

	/*Allocate space for the array*/
	np->contents = malloc(node_capacity * sizeof(int));

	/*Set to default values*/
	np->next_index = 0;
	np->next = NULL;

	if(np->next == NULL){
			printf("My next is NULL\n");
		}else{
			printf("My next is a VALUE\n");
		}

	return np;
}

void free_stack(struct int_stack *stack){
	/*Free up the contents of the stack*/
	reset_stack(stack);

	/*Free up the head and the stack itself*/
	//freeUp(stack->head);
	//free(stack);
}

void reset_stack(struct int_stack *stack){
	struct is_node *curnode = stack->head;
	/*Loop through all the nodes and free them up as you go*/
	while(curnode->next != NULL){
		struct is_node *nextnode = curnode->next;
		/*Free the array and free the node*/
		freeUp(curnode);
		curnode = nextnode;
	}
	/*The last node didn't get freed*/
	freeUp(curnode);
	stack->head->next = NULL;
	stack->size = 0;
}

void push(struct int_stack *stack, int d){
	struct is_node *curnode = stack->head->next;
	/*We know only the first node will not be full
	 * Check if the first node is full.
	 * */
	printf("Stack size = %d\n", stack->size);
	if(is_empty(stack) || curnode->next_index == stack->node_capacity){
		/*The first node was full or didn't exist; Create a new node at the top of stack*/
		printf("Adding a new node!\n");
		curnode = newNode(stack->node_capacity);
		curnode->next = stack->head->next;
		stack->head->next = curnode;
	}
	printf("Inserting %d at %d\n",d,curnode->next_index);
	/*Add to the node content the new data d*/
	curnode->contents[curnode->next_index] = d;
	curnode->next_index++;
	stack->size++;
	if(curnode->next == NULL){
		printf("My next is NULL\n");
	}else{
		printf("My next is a VALUE\n");
	}
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
	struct is_node *curnode = stack->head;

	/*The first node may not be full*/
	if(curnode->next != NULL && !(curnode->next->next_index == stack->node_capacity)){
		printf("(");
		for(i = curnode->next->next_index-1; i > 0; i--){
			printf("%d, ",curnode->next->contents[i]);
		}
		printf("%d]",curnode->next->contents[0]);
		curnode = curnode->next;
	}

	/*Standard case: The node is full*/
	while(curnode->next != NULL){
		printf("[");
		for(i = curnode->next->next_index-1; i > 0; i--){
			printf("%d, ",curnode->next->contents[i]);
		}
		printf("%d]",curnode->next->contents[0]);
		curnode = curnode->next;
	}
}

