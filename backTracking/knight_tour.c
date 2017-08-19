
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))

typedef struct matrix {
	int m;
	int n;
	int *matrix;
}matrix_t;

#define matrix_size(x,y) ((sizeof(int)) * (x) * (y))

int matrix_is_pos_valid(matrix_t *p, int i, int j)
{
	if((i > p->m-1) || (j > p->n-1) || (i < 0) || (j < 0) )
		return 0;

	return 1;
}

void matrix_init(matrix_t *k, int m, int n)
{

	k->matrix = malloc(matrix_size(m, n));
	if(!k->matrix)
		exit(1);

	memset(k->matrix, 0x00, matrix_size(m, n));
	k->m = m;
	k->n = n;

	return;	
}

int matrix_pos(matrix_t *p, int i, int j)
{
	return (*(p->matrix + ((p->m * i) + j)));
}

void matrix_set_val(matrix_t *p, int i, int j, int val)
{
 	*(p->matrix + ((p->m * i) + j)) = val;
}

typedef struct pos {
	int i;
	int j;
}pos_t;

pos_t move[] = {
		{-2,  1},
		{-2, -1},
		{2,  -1},
		{2,   1},
		{-1, -2},
		{-1,  2},
		{1,  -2},
		{1,   2},
	};

static int goto_nxt_pos(matrix_t *m, int curr_i, int curr_j, pos_t *r)
{
	int i, j, k=-1;
	//pos_t *r = NULL;

	while(1) {

		k++;
		if(k >= ARR_SIZE(move))
			break;

		i = curr_i+move[k].i;
		j = curr_j+move[k].j;

		printf("iter: i:%d j:%d\n", i, j);

		if(!matrix_is_pos_valid(m, i, j) ) {
			continue;				
		}
		if(matrix_pos(m, i, j)) {
			continue;
		}
		break;
	}

	if(matrix_is_pos_valid(m, i, j) && k < ARR_SIZE(move)) {
		r->i = i;
		r->j = j;
		return 1;
	}
	return 0;
}

static int cnt = 0;

void ktour(matrix_t *m, int posi, int posj) 
{
	int i, j;

	cnt++;
	matrix_set_val(m, posi, posj, cnt);

	while(1) {

		pos_t t;

		if(goto_nxt_pos(m, posi, posj, &t)) {
			printf("i:%d, j:%d\n", t.i, t.j);
			ktour(m, t.i, t.j);
		}
		else {
			break;
		}
	}
}

void print(matrix_t *m)
{
	int i, j;

	for(i=0; i < m->m; i++) {
		printf("[ ");
		for(j=0; j < m->n; j++)
			printf("%d, ", matrix_pos(m, i, j));
		printf("]\n");
	}
}

int main() 
{
	matrix_t m;

	matrix_init(&m, 8, 8);
	ktour(&m, 0, 0);
	print(&m);	
}
