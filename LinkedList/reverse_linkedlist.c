
#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
	int data;
	struct linked_list *nxt;
}ll;

ll* ll_node_init(int data)
{
	ll *tmp = malloc(sizeof(*tmp));
	if(tmp) {
		tmp->data = data;
		tmp->nxt = NULL;
	}
	return tmp;
}

void ll_insert_head(ll **head, ll *node)
{
	if(!head) {
		*head = node;
	}
	else {
		node->nxt = *head;
		*head = node;
	}
}

void ll_insert_tail(ll **head, ll *node)
{
	ll* trv = *head;
	
	if(!trv) {
		*head = node;
	}

	while(trv->nxt) {
		trv = trv->nxt;
	}

	trv->nxt = node;
}

void ll_print(ll *head)
{
	ll *t = head;
	while(t) {
		printf("%d, ", t->data);
		t = t->nxt;
	}
	printf("\n");
}

ll* ll_reverse(ll *head) 
{
	ll *h = head;
	ll *tmp;
	ll *th = NULL;

	while(h) {
		tmp = h;
		h = h->nxt;
		tmp->nxt = th;
		th = tmp;
	}

	return th;
}

int main() 
{
	ll *tmp;
	ll *head = NULL;
	
	tmp = ll_node_init(5);
	ll_insert_head(&head, tmp);
	tmp = ll_node_init(1);
	ll_insert_head(&head, tmp);
	tmp = ll_node_init(7);
	ll_insert_head(&head, tmp);
	
	ll_print(head);
	head = ll_reverse(head);
	ll_print(head);

}
