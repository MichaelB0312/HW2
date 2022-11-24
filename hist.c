#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

static FILE *f;
static int nbins = 10;

void make_hist(int *bins);

/*
 * @function getting input in linux convention
 * @ argc,argc - the regular main function's input
 */
void parse_arg(int argc, char **argv){
	f=stdin;
	for(int i=1;i<argc;i++){
		if(!strcmp(argv[i],"-")){
			f=stdin;
		}else if(!strcmp(argv[i],"-n_bins")){
			nbins = i<argc-1 ? atoi(argv[i+1]) : 10;
			i++;

		} else {
			f = fopen(argv[i], "r");
		}

		

	}

}

int main(int argc, char **argv){
	parse_arg(argc,argv);
	/*failure of fopen*/
	if(!f){
		fprintf(stderr,"File not found: \"%s\"\n", argv[1]);
		return 1;
	}

	/*initiaite the final resulit's histogram array*/
	int *bins = (int*)malloc(sizeof(int)*nbins);
	for(int i=0; i<nbins; i++){
		bins[i] = 0;
	}

	make_hist(bins);
	fclose(f);

	free(bins);
	return 0;

}

/*
 * @function making the final histogram
 * @get an emtpy histogram
 */
void make_hist(int *bins){
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

	/*print bins*/
        pace = 100.0/nbins;
	for(int i=0; i<nbins; i++){
		double left = i*pace;
		double right = (i < nbins - 1) ? ((i+1)*pace - 1) : 100;
		printf("%.0lf-%.0lf\t%d\n",left,right,bins[i]);
	}


}





