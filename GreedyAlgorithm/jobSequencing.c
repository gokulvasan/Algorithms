#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct job {
	int jid;
	int dl;
	int profit;
}job_t;

job_t j[] = {
		{13, 5, 20},
		{1, 4, 25},
		{2, 4, 20},
		{3, 4, 15},
		{4, 4, 35},
		{5, 3, 45},
		{6, 3, 10},
		{7, 2, 5},
		{8, 2, 3},
		{9, 2, 20},
		{10, 2, 1},
		{11, 1, 30},
		{12, 1, 15}
	};

void swap(job_t *A, job_t *B)
{
	job_t c;

	c.jid = A->jid;
	c.dl = A->dl;
	c.profit = A->profit;

	A->jid = B->jid;
	A->dl = B->dl;
	A->profit = B->profit;

	B->jid = c.jid;
	B->dl = c.dl;
	B->profit = c.profit;

}

void selection(job_t *jo, int cnt)
{
	int i, j, max;

	for(i=0; i<cnt; i++) {
		max = i;
		for(j=i; j<cnt; j++) {
			if(jo[max].profit < jo[j].profit)
				max = j;
		}
		if(i != max)
			swap(&jo[max], &jo[i]);
	}
}

/* job scheduling with deadline*/
void jsd(job_t *jo, int cnt, int *tslot, int max)
{
	int i = 0;
	int j, k=0;
	int profit, dl;
	int suc = 0;

	memset(tslot, 0x00, sizeof(*tslot)*max);
	while((i < max) && (k < cnt)) {

		profit = jo[k].profit;
		dl = jo[k].dl;
 
		if(dl > max)
			dl = max;

		for(j=dl; j>=0; j--) {				
			if(!tslot[j]) {
				tslot[j] = jo[k].jid; 
				k++;
				i++;
				break;
			}
		}
	}
}

int jobSequencing(job_t *j, int cnt, int *tslot, int max)
{
	int i;

	selection(j, cnt);
	jsd(j, cnt, tslot, max );
	
	for(i=0; i<max; i++) {
		printf("%d ", tslot[i]);
	}
	printf("\n");
}

#define ARR_SIZE(X) (sizeof(X)/sizeof(X[0]))

int main()
{
	int ts[5];
	jobSequencing(j, ARR_SIZE(j), ts, ARR_SIZE(ts));
}

