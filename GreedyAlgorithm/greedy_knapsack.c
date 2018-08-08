#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	profit per weight
*/
typedef struct object {
	int obj;
	float profit;
	float weight;
} object_t;

typedef struct obj_lst {
	int cnt;
	object_t *obj;
}obj_lst_t;

typedef struct ksf {
	float ppw;	/// profit per weight
	object_t *d;
	struct ksf *nxt;
}ksf_t;

obj_lst_t* object_init(int cnt)
{
	object_t *obj = malloc(sizeof(*obj) * cnt);
	obj_lst_t *lst;
	
	lst->obj = obj;
	lst->cnt = 0;

	return lst;
}


void object_insert(obj_lst_t *lst, float profit, float weight) 
{
	lst->obj[cnt].obj = cnt;
	lst->obj[cnt].profit = profit;
	lst->obj[cnt].weight = weight;

	lst->cnt++;
}

ksf_t* ks_convert(obj_lst_t *lst)
{
	float frac;
	int i;

	while(i < cnt) {

		ksf_t *t = malloc(sizeof(*t));
		t->ppw = lst->obj[i].profit / lst->obj[i].weight;
				
		i++;
	}

}

void knapsack(obj_lst_t *lst, int m)
{
	

}

int main()
{
	float a = 3.0/5;
	obj_lst_t *lst;
	
	lst = object_init(7);
	object_insert(lst, 10, 2);
	object_insert(lst, 5, 3);
	object_insert(lst, 15, 5);
	object_insert(lst, 7, 7);
	object_insert(lst, 6, 1);
	object_insert(lst, 18, 4);
	object_insert(lst, 3, 1);

	printf("%f\n", a);

}
