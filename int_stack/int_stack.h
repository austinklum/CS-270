/*
 * Interface for operating and using a stack of integers.
 * (Do NOT modify this file.)
 *
 * Author: Jason Sauppe, based on earlier version by Steve Senger
 * Date: 2017-10-17
 */

/* Structure definitions */
struct is_node {
    int *contents;
    int next_index;
    struct is_node *next;
};

struct int_stack {
    size_t size;
    size_t node_capacity;
    struct is_node *head;
};

/* Operations on a stack */
struct int_stack *make_stack(int node_capacity);
void free_stack(struct int_stack *stk);
void reset_stack(struct int_stack *stk);
void print_stack(struct int_stack *stk);

int is_empty(struct int_stack *stk);
void push(struct int_stack *stk, int v);
int pop(struct int_stack *stk);
int top(struct int_stack *stk);

