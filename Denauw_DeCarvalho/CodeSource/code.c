#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //Pour sbrk
#include "code.h"


void* my_malloc(int size)
{
	if (size % 4 !=0)
	{
		size=size+(4-(size%4));
	}	

	int notFound=0;
	void *position=debut_workspace_m;
	while(notFound==0)
	{	if(position==fin_workspace_m)
		{
			notFound=1;
			return NULL;
		}
		struct block_header* block_position=(struct block_header*)position;
		if(block_position->alloc==0 && (block_position->size) >= (size+4)) //si on peut allouer et assez grand
		{
			unsigned int block_size=(block_position->size)-size-4;
			block_position->size=size+4;	//on donne la taille au block
			block_position->alloc=1;	//on dit que le block est alloue
			void* final_position=position;	//on stocke la position du bloc libéré voulu
			struct block_header* header= (struct block_header*) position;
			position+=header->size;		//on va a la fin du block que l'on vient d'allouer
			struct block_header* new_header=(struct block_header*)position;
			new_header->size=block_size;
			new_header->zero=0;
			new_header->alloc=0;	
//on met le block header contenant les info sur ce qu'il reste du block initial

			notFound=1;	//inutile mais pour faire propre
			return final_position+4; //retourne la position du block voulu
		}
		else
		{
			struct block_header* header= (struct block_header*) position;
			position+=header->size;		
		}
	}

}


void myfree(void *ptr)
{

}

