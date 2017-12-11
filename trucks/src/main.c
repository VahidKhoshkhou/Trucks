#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct {
	int weight;
	int truckId;
} pack_t;
//each pack is loaded in which truck

pack_t *load(char *, int *);
void display(pack_t *, int, int);
int place_r_oneSol(pack_t *, int , int *, int , int);
int main(int argc, char *argv[]) {
	int packnum, neededTruck;
	int *trucks,i;
	pack_t *packs;
	if (argc != 2) {
		printf("error in C.L parameter!\n");
		exit(0);
	}
	packs = load(argv[1], &packnum);
	trucks = (int *) calloc(packnum, sizeof(int));

	for(i=1;i<=packnum;i++){
		if( place_r_oneSol(packs,packnum,trucks,i,0)){
			neededTruck=i;
			display(packs, packnum,neededTruck);
			break;
		}
	}
	free(packs);
	free(trucks);
	printf("%d", neededTruck);
	return 0;
}

pack_t *load(char *fn, int *num) {
	int n, i;
	FILE *fp;
	pack_t *packs;
	fp = fopen(fn, "r");
	if (fp == NULL) {
		printf("error in opening file!\n");
		exit(0);
	}
	fscanf(fp, "%d", &n);
	packs = (pack_t *) malloc(n * sizeof(pack_t));
	if (fp == NULL) {
		printf("error in allocation!\n");
		exit(0);
	}
	for (i = 0; i < n; i++) {
		fscanf(fp, "%d", &packs[i].weight);
		 packs[i].truckId = -1;
	}
	*num = n;
	return packs;
}


int place_r_oneSol(pack_t *packs, int packnum, int *trucks, int ntcurr, int level) {
	int i;
	if (level >= packnum) {
		return 1;
	}
	
	for (i = 0; i < ntcurr; i++) {
		if (trucks[i] + packs[level].weight <= MAX) {
			packs[level].truckId = i;
			trucks[i] += packs[level].weight;
			if (place_r_oneSol(packs, packnum, trucks, ntcurr, level + 1)== 1) {
				return 1;
			}
			packs[level].truckId = -1;
			trucks[i] -= packs[level].weight;
		}
	}
	return 0;
}

void display(pack_t *packs, int packnum, int neededTruck) {
	int i, j, weight;
	printf("%d trucks are needed.\n", neededTruck);
	for (i = 0; i < neededTruck; i++) {
		weight = 0;
		for (j = 0; j < packnum; j++) {
			if (packs[j].truckId == i) {
				weight += packs[j].weight;
			}
		}
		printf("#Truck %d , Weight %d\n", i, weight);
		for (j = 0; j < packnum; j++) {
			if (packs[j].truckId == i) {
				printf("package %d, weight %d\n", j, packs[j].weight);
			}
		}
	}

	return;
}
