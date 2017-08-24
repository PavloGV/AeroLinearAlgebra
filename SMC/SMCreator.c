/*
 * @Author: Pavlo Vlastos
 * 
 * @File name: SMCreator.c
 *
 * @Purpose: program to use text file as specification to write a statemachine main in c
 * 
 * @Date: 8/23/17
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


// Global Variables
char *execname = NULL;
int exit_status = EXIT_SUCCESS;

/*
 * Main
 */
int main (int argc, char *argv[] ) {

    printf("\n**** RUNNING SMCreator.c ****\n");

    // Second argument is the text file to be read
	char *fileName = argv[1];
	FILE *input = fopen(fileName, "r");

    if (input == NULL) {                            // Make this into function
    	fflush(NULL);
     	fprintf(stderr, "%s: %s: %s\n",
        	execname, fileName, strerror (errno));
   		fflush(NULL);
     	exit_status = EXIT_FAILURE;
        return 0;
	}

    // if file pointer "input" is not null continue
    printf("\nnumber of arguments: %d\n", argc);
    printf("file name: %s\n\n", fileName);

    // Read file, line by line.
    char buffer[1024];
	for (int lineRead = 1; ; ++lineRead) {
		char *fileLine = fgets(buffer, sizeof buffer, input);
		if (fileLine == NULL) break;
		fileLine = strchr(buffer, 'L');
		if (fileLine == NULL) {
			fflush(NULL);
			fprintf(stderr, "%s: %s[%d]: unterminated line\n",
		    	execname, fileName, lineRead);
		 	fflush(NULL);
		 	exit_status = EXIT_FAILURE;
        
		} else {
            // Begin generating state machine main file. 
            printf("line %d: %s\n", lineRead, fileLine);
            
            

			*fileLine = '\0';   // reset file line to NULL
		}
    }

    fclose(input);

    printf("\n**** SMCreator.c Finished ****\n\n");

    return 0;
}

/*
 *
 * EOF 
 */
