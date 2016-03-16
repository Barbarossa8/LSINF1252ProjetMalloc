#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "code.h"

void *debut_workspace_m;
void *fin_workspace_m;


int main(int argc, char *argv[])
{
	unsigned int capacity=atoi(argv[1]);
	debut_workspace_m = sbrk(capacity);

	fin_workspace_m = sbrk(0);
	struct block_header *header=(struct block_header*)debut_workspace_m;
	header->size=capacity;
	header->zero=0;
	header->alloc=0;
	
	//mini tests
	void* a=my_malloc(8);
	void* b=a;
	printf("\nadresse malloc(8): %p \n",a);
	
	a-=4;
	printf("adresse malloc(8)-4: %p \n",a);
	struct block_header *header2=(struct block_header*) a;
	printf("alloué: %d \n",header2->alloc);
	printf("size: %d \n",header2->size);
	a+=header2->size;
	struct block_header *header3=(struct block_header*) a;
	printf("\nadresse bloc suivant après 12: %p \n",a);
	printf("alloué: %d \n",header3->alloc);
	printf("size: %d \n",header3->size);
	a-=header2->size;
	
	printf("\npointeur debut block_header: %p \n",a);
	a+=4;
	my_free(a);	
	a-=4;
	struct block_header *header4=(struct block_header*) a;
	//header4->alloc=0;
	printf("alloué: %d \n",header4->alloc);
	printf("size: %d \n",header4->size);
	//free(a);
	/*b-=4;
	struct block_header *header4=(struct block_header*) b;
	printf("\nadresse bloc suivant après free: %p \n",b);
	printf("alloué: %d \n",header4->alloc);
	printf("size: %d \n",header4->size);*/
	return 0;
}


