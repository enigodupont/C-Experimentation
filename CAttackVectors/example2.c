#include <stdio.h>

int main(int argc, char** argv){

	if(argc < 2){
		fprintf(stderr,"%s [string here]\n",argv[0]);
		return -1;
	}

	printf(argv[1]);

	return 0;
}
