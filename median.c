#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

static FILE *f;
static int nbins = 100;

void make_hist(int *bins,int *num_of_students);

int main(int argc, char *argv[]){
	
	/*implementing linux reading convention*/ 
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
	
	//pre-step, build an histogram
	
	int *bins = (int*)malloc(sizeof(int)*nbins);
	for(int i=0; i<nbins; i++){
		bins[i] = 0;
	}
        int init_num_of_students = 0;
	int *num_of_students = &init_num_of_students;	
	make_hist(bins,num_of_students);
	/*calculate the median:*/
	int med_idx = (*num_of_students+1)/2;
	int cnt = 0;
	for(int i=0; i<nbins; i++){
		cnt += bins[i];
		if(cnt >= med_idx){
			fprintf(stdout,"Median is: %d\n", i);
			exit(0);
		}
	}


	fclose(f);
	free(bins);
	return 0; 
}



/*
 * @function making the final histogram
 * @get an emtpy histogram
 * @initiate total num of students
 * @update final bins array and number of students
 */
void make_hist(int *bins, int *num_of_students){
	int grade;
	int retval;
	double pace;
	int line=1;

	while(1){
		retval = fscanf(f, "%d", &grade);
		if(retval == EOF){
			break;/*finish getting grades*/

		} else if(retval != 1){
			/*error*/
			fprintf(stderr, "Error, not a number\n");
			exit(1);
		}
		if(grade<0 || grade>100){
			fprintf(stderr,"insensible grade in line No.%d\n",line);
			exit(1);
		}
	  
		line++;
		/*Find bin*/
		int required_bin = grade / (100 / nbins);
		if(grade == 100){
			bins[required_bin-1]++;
		}
		else{
			bins[required_bin]++;
		}
	}

	*num_of_students = line - 1;
	

}


