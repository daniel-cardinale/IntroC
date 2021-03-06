#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	if(argc != 6) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return EX_USAGE;  	
	}
	
	int ret_code = EX_OK;	

	FILE *fp1 = fopen(argv[2], "r");
	if(!fp1){
		perror("unable to open file 1");
		ret_code = EX_NOINPUT;
		goto leave;
	}
	
	FILE *fp2 = fopen(argv[3], "r");
	if(!fp2){
		perror("unable to open file 2");
		ret_code = EX_NOINPUT;
		goto fp1_cleanup;
	
	}
	
	FILE *fp3 = fopen(argv[5], "w");
	if(!fp3){
		perror("unable to write to file 3");
		ret_code = EX_NOINPUT;
		goto cleanup;
	}
	int c;
	char a;
	char buf1[128];

	
	if((!strcmp(argv[1], "glue")) && (!strcmp(argv[4], "+output"))) {

		while(fgets(buf1, sizeof(buf1), fp1)) {
			fputs(buf1, fp3); 			
		}
		while(fgets(buf1, sizeof(buf1), fp2)) {
			fputs(buf1, fp3);
		}

	}

	if(!strcmp(argv[4], "+")) {
		
		
		while(fgets(buf1, sizeof(buf1), fp1)) {
			fputs(buf1, fp3); 
		}	
		while(fgets(buf1, sizeof(buf1), fp2)) {
			fputs(buf1, fp3); 		
		}
	}



cleanup:
	if(fclose(fp2)){
		perror("Unable to close file");
		ret_code = EX_IOERR;
	}

fp1_cleanup:
	if(fclose(fp1)){
		perror("Unable to close file");
		ret_code = EX_IOERR;
	}
leave:
	return ret_code;

	
}
