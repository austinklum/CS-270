/*
 * int_stack.c
 *
 *  Created on: Oct 20, 2017
 *      Author: Austin Klum
 */
#include <stdio.h>
#include "int_stack.h"

struct is_node *newNode();

int main(int argc, char **argv){
	struct int_stack *myStack = make_stack(1);
	printf("myStack cap: %d\n", myStack->node_capacity);
	printf("myStack size: %d\n", myStack->size);
	printf("myStack head: %d\n", myStack->head->next->contents);

	return 0;
}

struct int_stack *make_stack(size_t node_capacity){
	struct int_stack *stack = NULL;
	/*I only need space for a single list*/
	stack = malloc(sizeof(struct int_stack));

	/*But I WILL need space for multiple nodes*/
	stack->size = 0;
	stack->node_capacity = node_capacity;
	stack->head = newNode();
	stack->head->next = newNode();
	stack->head->next->contents = 42;

	return stack;
}

/*This creates a single node doesn't use pointers
 * np -> spaceThatIsANode.
 * We want something like:
 * np -> addressToSpaceThatIsANode -> spaceThatIsANode
 * */
struct is_node *newNode(){
	struct is_node *np = malloc(sizeof(struct is_node));
	np->next = NULL;

	return np;
}
