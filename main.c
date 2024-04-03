/* 
* @author: Nathaniel Barajas
* Panther ID: 6201802
*
* I affirm that I wrote this program without any help
* from any other people or sources on the internet.
*
* This assignment is meant to teach how to use dynamic
* 
*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "bmplib.h"
//added headers to get getopt to work
/*
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 *
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 */
int enlarge(PIXEL* original, int rows, int cols, int scale,
	    PIXEL** new, int* newrows, int* newcols) {
	/* THIS IS THE METHOD THAT YOU SHOULD WRITE */
	int row, col, i, j;
	//instance variables 
	
	if ((rows <= 0) || (cols <= 0)) return -1; // checks if rows and cols are positive
	
	*newrows = scale*rows;
	*newcols = scale*cols; 
	*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));
	// variab
	for (row=0; row < rows; row++) //for loop for each pixel in row
		for (i = 0; i < scale; i++) { //for loop to scale rows
			for (col=0; col < cols; col++) { //for loop for each col
				for (j = 0; j < scale; j++) { //for loop to scale cols
					PIXEL* o = original + row*cols + col; //the original pixel
					PIXEL* n = (*new) + row*cols*scale*scale + cols*scale*i + col*scale + j; //the new pixel
					*n = *o; //replaces original pixel with new pixel
				} 
			}//end of for loop
		}//end of for loop
	

  return 0; //return 0 if function was a success
} //end of enlarge function

/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been read
 * in using readFile(). The rotation is expressed in degrees and can be
 * positive, negative, or 0 -- but it must be a multiple of 90 degrees
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - a positive or negative rotation,
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */
int rotate(PIXEL* original, int rows, int cols, int rotation,
	   PIXEL** new, int* newrows, int* newcols) {
	/* THIS IS THE METHOD THAT YOU SHOULD WRITE */
	int row, col;
	//instance variables for the function.
	
	if ((rows <= 0) || (cols <= 0)) return -1; //
	
	if (rotation % 360 == 0) { //rotation is a full 360 degrees
		*newrows = rows;
		*newcols = cols;
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL)); //allocate memory to get each pixel of image
		for (row=0; row < rows; row++) //for loop for each pixel in row
			for (col=0; col < cols; col++) {
				PIXEL* o = original + row*cols + col; //the original pixel
				PIXEL* n = (*new) + rows*cols + col; //the new pixel
				*n = *o; //replaces original pixel with new pixel
			} //end of for loop
	} else if ((rotation > 0 && rotation % 270 == 0) || (rotation < 0 && rotation % 90 == 0 && rotation % 180 != 0 && rotation % 270 != 0)) { //rotation is 270 degrees
		*newrows = cols;
		*newcols = rows;
		//new rows and cols are set to cols and rows respectively in order to turn
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));  //allocate memory to get each pixel of image
		for (row=0; row < rows; row++) //for loop for each pixel in row
			for (col=0; col < cols; col++) {
				PIXEL* o = original + row*cols + col;  //the original pixel
				PIXEL* n = (*new) + (cols-col-1)*rows + row; //the new pixel
				*n = *o; //replaces the original pixel with the new one.
			} //end of for loop
	} else if ((rotation > 0 && rotation % 180 == 0) || (rotation < 0 && rotation % 180 == 0)) { //rotation is 180 degrees
		*newrows = rows;
		*newcols = cols;
		//new rows and cols are set to cols and rows respectively in order to turn
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));  //allocate memory to get each pixel of image
		for (row=0; row < rows; row++) //for loop for each pixel in row
			for (col=0; col < cols; col++) {
				PIXEL* o = original + row*cols + col; //the original pixel
				PIXEL* n = (*new) + (rows-row)*cols - (col+1); //the new pixel
				*n = *o; //replaces the original pixel with the new one.
			} //end of for loop
	} else if ((rotation > 0 && rotation % 90 == 0) || (rotation < 0 && rotation % 270 == 0)) { //rotation is 90 degrees
		*newrows = cols;
		*newcols = rows; 
		//sets new to old/
		
		*new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));  
		//allocate memory to get each pixel of image
		
		for (row=0; row < rows; row++) //for loop for each pixel in row
			for (col=0; col < cols; col++) { //for loop for each pixel in col
				PIXEL* o = original + row*cols + col; //the original pixel
				PIXEL* n = (*new) + col*rows + (rows-row-1); //the new pixel
				*n = *o; //replaces the original pixel with the new one.
			} //end of for loop
	}//end of if else if statements
	
	return 0; //return 0 if rotate function is a success
} //end of rotate function

/*
 * This method Vertically flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */

int verticalflip (PIXEL *original, PIXEL **new, int rows, int cols) { 
	/* THIS IS THE METHOD THAT YOU SHOULD WRITE */
	
	int row, col;
	//instance variable needed for this program
	
	if ((rows <= 0) || (cols <= 0)) return -1; //return -1 if rows or cols are negative
	
	*new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL)); //allocate memory to get each pixel of image
	
	for (row=0; row < rows; row++) //for loop for each row 
		for (col=0; col < cols; col++) { //for loop for each col
			PIXEL* o = original + row*cols + col; //the original pixel
			PIXEL* n = (*new) + (rows-row)*cols - (col+1); //the new pixel
			*n = *o; //replaces the original pixel with the new one.
		}//end of for loop

	return 0; //return 0 if function was a success
} //end of verticalflip function 


/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * THIS IS GIVEN TO YOU SOLELY TO LOOK AT AS AN EXAMPLE
 * TRY TO UNDERSTAND HOW IT WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, PIXEL **new, int rows, int cols)
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++) //for loop for each pixel in row
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col; //the original pixel
      PIXEL* n = (*new) + row*cols + (cols-1-col); //takes the new pixel
      *n = *o; //replaces the original pixel with the new one.
    }

  return 0;
}

int main(int argc, char **argv) {
	
	int r, c, nrow, ncol;
	PIXEL *b, *nb;
	extern char *optarg;
	extern int optind;
	int g, err = 0; 
	int sflag = 0, rflag = 0, fflag = 0, vflag = 0, oflag = 0;
	int scale = 0, rotation = 0;
	FILE *outFile = stdout;	
	FILE *inFile = stdin; 
	char *iName = "example.bmp";
	char *oName = "result.bmp"; 
	static char usage[] = "usage: %s [-s scale | -r degree | -f | -v] [-o outputfile] [inputfile]\n"; 
	//instance variables needed for the main function  
	
	while ((g = getopt(argc, argv, "s:r:fvo:")) != 1) //while loop for getopt
		switch (g) { //switch for getopt 
			case 's': //checks if s option is chosen
				sflag = 1; //raise sflag
				scale = atoi(optarg); //value of scale 
				break;
			case 'r':
				rflag = 1; //raise rflag
				rotation = atoi(optarg); //value of rotation 
				break;
			case 'f': //checks if f option is open
				fflag = 1; //raise fflag
				break;
			case 'v': //checks if v option is chosen
				vflag = 1; //raise vflag
				break;
			case 'o':
				oflag = 1; //raise vflag
				if (optarg != NULL) {
					strcpy(oName, argv[optind]);
				}
				break;
			case '?':
				err = 1; //raises error flag
				break;
		} //switch  statement
		
		
	if (err) { //checks for error flag
		fprintf(stderr, usage, argv[0]); //prints error message
		 exit(1); //exits 100
	} //end if statemnt

	if(argv[optind] != NULL) { //checks if there is an input file
		inFile = fopen(argv[optind], "r+");
	} //end of if stat
	
	readFile(iName, &r, &c, &b);
	if (sflag == 1) { //checks if sflag has been raised
		if (scale < 1) { //checks to see if scale is not a positive integer 
			printf("Scale must be a positive integer (i.e. 1,2,3 ...) \n"); //print error message
			return -1; //exit with -1
		}  else {
			enlarge(b, r, c, scale, &nb, &nrow, &ncol); //call enlarge function
			r = nrow; //set rows equal to new rows
			c = nrow; //set cols to equal new rols			
		} //end of if else statement
	} //end of sflag
	
	if (rflag == 1) { //checks if rFlag is raised
		if (rotation % 90 == 0) { //checks if rotation is divisible by 90
			rotate(b, r, c, rotation, &nb, &nrow, &ncol); //call enlarge function
			//r = nrow; //set rows equal to new rows
		//	c = nrow; //set cols to equal new rols
		} else { 
			printf("Rotation must be divisible by 90 \n");
			return -1;
		} //end of if else statement
	} //end of rflag
	
	if (fflag == 1) { //checks if sflag has been raised
		flip(b, &nb, r, c); //call flip function
	} //end of fflag
	
	if (vflag == 1) { //checks if sflag has been raised
		verticalflip(b, &nb, r, c); //call verticalflip function
	} //end of vflag
	
	if (oflag == 1) {
		writeFile("resulter.bmp", r, c, nb); //creates file name exapmle
	} else {
		writeFile("result.bmp", r, c, nb);
	}
	
	/*
	readFile("example.bmp", &r, &c, &b);
	rotate(b, r, c, 90, &nb, &nrow, &ncol);
	r = nrow;
	c = nrow;
	writeFile("result1.bmp", r, c, nb);
	
	readFile("example.bmp", &r, &c, &b);
	flip(b, &nb, r, c);
	writeFile("result1.bmp", r, c, nb);
	*/
	
	free(b); //free bmp 
	free(nb); //free new bmp
	
	return 0; //return 0 if main function was a success
	
} //end of main
