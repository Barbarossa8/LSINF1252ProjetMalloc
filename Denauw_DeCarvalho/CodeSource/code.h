struct block_header
{
	unsigned int size : 29,
		     zero : 2,
		     alloc : 1;
};

void* fin_workspace_m;
void* debut_workspace_m;

void* my_malloc(int size);
void* my_calloc(int size);
void my_free(void *ptr);
