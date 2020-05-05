#include "prio_q.h"

struct prio_q * prio_q_create()
{
	struct prio_q *q = malloc(sizeof *q);
	q->front = NULL;
	q->size = 0;
	return q;
}

void prio_q_enqueue(struct prio_q *q, void *data, int prio)
{
	if(q == NULL) return;

	struct prio_q_elem *new_ele = malloc(sizeof *new_ele);
	new_ele->priority = prio;
	new_ele->next = NULL;
	new_ele->data = data;
	
	if(q->front == NULL){
		q->front = new_ele;
		q->size = 1; 
	} else {
		struct prio_q_elem *current_ele = q->front;
		struct prio_q_elem *last_ele = NULL;

		while(current_ele->next != NULL){		
			if(current_ele->priority < new_ele->priority && last_ele == NULL){
				break;
			} else if(current_ele->priority < new_ele->priority){
				last_ele->next = new_ele;
				break;
			} else {
				last_ele = current_ele;
				current_ele = current_ele->next;				
			}
		}

		if(current_ele->priority < new_ele->priority){
			new_ele->next = current_ele;
			if(last_ele != NULL) last_ele->next = new_ele;
			if(current_ele == q->front) q->front = new_ele;
		} else {	// current_ele->priority >= new_ele->priority
			current_ele->next = new_ele;
		}
		
		q->size += 1;
	}
}

void * prio_q_dequeue(struct prio_q *q)
{
	void *data = NULL;
	if(q != NULL && q->front != NULL)
	{
		struct prio_q_elem *ele = q->front;	
		if(ele->next != NULL)
			q->front = ele->next;
		else 
			q->front = NULL;
		if(ele->data != NULL)
		{	
			data = ele->data;		
		}
		q->size -= 1;	
		free(ele);
	}	
	return data;
}

void * prio_q_front(struct prio_q *q)
{
	if(q != NULL && q->front != NULL) 
		return q->front->data;
	else
		return NULL;
}

int prio_q_destroy(struct prio_q *q, void ** data)
{
	int k = 0;
	if(q != NULL && q->front != NULL) 
	{
		struct prio_q_elem *current_ele = q->front;
		struct prio_q_elem *tmp = NULL; 
		while(current_ele->next != NULL)
		{	
			tmp = current_ele;
			if(current_ele->data != NULL)
			{
				void *ele_data = current_ele->data;
				data[k++] = ele_data;
			}
			current_ele = current_ele->next;
			free(tmp);
		}

		if(current_ele->data != NULL)
		{
			void *ele_data = current_ele->data;
			data[k++] = ele_data;
		}
		free(current_ele);
		free(q);
	}
	return k;
}

void prio_q_print(struct prio_q * q, void (*print_data)(void*))
{
	printf("Priority Queue (size=%d): \n", q->size);
	if(q != NULL && q->front != NULL)
	{
		struct prio_q_elem *e = q->front;
		while(e->next != NULL)
		{
			printf("Prio: %d, Data: ", e->priority);
			if(e->data != NULL)
				print_data(e->data);
			e = e->next;
			printf("\n");
		}
		printf("Prio: %d, Data: ", e->priority);
		if(e->data != NULL)
			print_data(e->data);
		printf("\n");
	}
	printf("\n");	
}
