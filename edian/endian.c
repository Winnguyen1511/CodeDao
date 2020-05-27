#include <stdio.h>
#include <stdlib.h>

int main(void){
	int num = 1;
	char *c_ptr;
	int *i_ptr;
	printf("num:%d \n", num);
	//scanf('%d', &num);
		
	c_ptr =(char*)&num;
	i_ptr = &num;
	printf("char addr:%p, val: %d\n",c_ptr, *c_ptr);
	printf("int  addr:%p, val: %d\n",i_ptr, *i_ptr);
	if(*c_ptr == *i_ptr)
		printf("> Little-endian\n");
	else{
		printf("> Big-endian\n");
	}
	
	printf("Exit...\n");
	return 0;
}
