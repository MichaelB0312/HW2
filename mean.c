#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void operate(FILE *f);

int main(int argc, char *argv[]){
	
	/*implementing linux reading convention*/ 
	FILE *f;
	if((argc == 1) || !strcmp("-",argv[1])){
		f = stdin;
	}else{
		f = fopen(argv[1],"r");
	}
	/*find errors in fopen*/
	if(!f){
		fprintf(stderr,"File %s not found",argv[1]);
		return 1;
	}

	operate(f);//do the mean operation
	fclose(f);
	return 0; 
}

/**
 * @doing mean
 * @f- get grades from file
 * @printing the mean
 */
void operate(FILE *f){
	int grade;
	int retval;
	double avg;
	int line_n;
	
	avg = 0;
	line_n = 0;
	while(1){
		retval = fscanf(f, "%d", &grade);
		if(retval == EOF){
			break;/*finished*/
		} else if((retval != 1)){
			/* Error */
			fprintf(stderr, "Error,not a number");
			exit(1);
		}
		else if(grade<0||grade>100){
			fprintf(stderr, "Error,insensible grade in line No.%d",line_n);
			exit(1);

		}
		avg += grade;
		line_n++;
	}
	printf("%.2lf",avg/line_n);

	
}	


