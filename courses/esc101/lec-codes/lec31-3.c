#include <stdio.h>

void copy_file(FILE *fromfp, FILE *tofp)
{
	  char ch;
	
	  while ( !feof ( fromfp ) ) {
	    fscanf  ( fromfp, "%c", &ch );
	    fprintf ( tofp, "%c", ch );
	  }
}


int main()
{
	  FILE *fp;  char filename1[128], filename2[128];
	  scanf("%s", filename1);
  	  scanf("%s", filename2);
                  fp = fopen( filename1, "r" );
	  if(fp == NULL) {
	    	fprintf(stderr, "Opening File %s failed\n", filename1);
	    	return -1;
	  }
	  copy_file(fp, stdout);
	  fclose(fp);
  	  fp = fopen( filename2, "r" );
	  if (fp == NULL) {
	    	fprintf(stderr, "Opening File %s failed\n", filename2);
    		return -1;
	  }
	  copy_file (fp, stdout);
	  fclose(fp);
  	  return 0;
} 
