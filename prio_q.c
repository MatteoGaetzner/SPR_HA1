#include "prio_q.h"

/*
 / struct representing the priority queue
struct prio_q {
        int size;                   // number of elements in queue
        struct prio_q_elem *front;  // first element in queue
};

// struct representing an element in the priority queue
struct prio_q_elem {
    void * data;                // user data
    int priority;               // priority of the element
    struct prio_q_elem * next;  // pointer to next element in the queue
};
  */

struct prio_q * prio_q_create()
{
	struct prio_q *q = malloc(sizeof *q);
	q->front = NULL;
	return q;
}

void prio_q_enqueue(struct prio_q *q, void *data, int prio)
{
	struct prio_q_elem *new_ele = malloc(sizeof *q);
	new_ele->priority = prio;
	new_ele->next = NULL;
	new_ele->data = malloc(sizeof(data));
	new_ele->data = data;

	if(q->front == NULL){
		q->front = new_ele;
		q->size = 1; 
	} else {
		struct prio_q_elem *current_ele = q->front;
		struct prio_q_elem *last_ele = NULL;

		while(current_ele->next != NULL){		
			if(current_ele->priority < new_ele->priority && last_ele == NULL){
				printf("first if");
				break;
			} else if(current_ele->priority < new_ele->priority){
				printf("last_ele->priority = %d", last_ele->priority); 
				last_ele->next = new_ele;
				break;
			} else {
				printf("in else, with current = %d\n, next = %d\n", current_ele->priority, current_ele->next->priority);
				last_ele = current_ele;
				current_ele = current_ele->next;				
			}
		}

		if(current_ele->priority < new_ele->priority){
			printf("q->front->priority = %d, current_ele->priority = %d, new_ele->priority = %d\n", 
					q->front->priority, current_ele->priority, new_ele->priority);
			new_ele->next = current_ele;
			if(current_ele == q->front) q->front = new_ele;
		} else {	// current_ele->priority >= new_ele->priority
			current_ele->next = new_ele;
		}
		
		q->size += 1;
	}
}

void * prio_q_dequeue(struct prio_q *q)
{
	// TODO
}

void * prio_q_front(struct prio_q *q)
{
	// TODO
}

int prio_q_destroy(struct prio_q *q, void ** data)
{
	// TODO
}

void prio_q_print(struct prio_q * q, void (*print_data)(void*))
{
	struct prio_q_elem *e = q->front;
	while(e->next != NULL)
	{
		printf("x ");
		print_data(e->data);
		e = e->next;
		printf("\n");
	}

}
