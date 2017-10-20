/*
 * LinkedLists.c
 *
 *  Created on: Oct 17, 2017
 *      Author: Austin Klum
 */

#include <stdio.h>

struct Person{
	int age;
	char *name;
	char *ssn;
};

struct Node{
	struct Person data;
	struct Node *next;
};

struct List{
	struct Node head;
	int size;
};

int main(int argc, char **argv){
	printf("Foo!");
	return 0;
}

struct List init(){
	struct List *myList = NULL;
	myList = malloc(sizeof(struct List));
	myList->size = 0;
	myList->head = newNode();
	return myList;
}

void add(struct List *myList, struct Person d){
	struct Node temp = myList->head;
	int cmp;
	if(temp->next != NULL && (cmp = compareto(temp->data,d))){
		/*if *p1 > *p2*/
	}
	while(temp->next != NULL && compareto(temp->next->data, d) > 0){
		temp = temp->next;
	}
	/*Copy old next value*/
	struct Node t = temp->next;
	/*Create new node and data, Link the new node with the rest of the list*/
	temp->next = newNode;
	temp->next->data = d;

	temp->next->next = t;
	myList->size++;
}

void List viewList(struct List *myList){
//	temp = myList->head->next
//	while(){

	//}
}

struct Node *newNode(){
	struct Node *np = malloc(sizeof(struct Node));
	np->next = NULL;

	return np;
}

int compareto(struct Person *p1, struct Person *p2){
	return strcmp(*(*p1).name, p2->name);
}
