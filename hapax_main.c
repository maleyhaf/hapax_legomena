#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_tally.h"


/** function to be passed in to llFree to delete allocated keys */
void deleteKey(LLNode *node, void *userdata)
{
	if (node->key != NULL) {
		free(node->key);
	}
}


/** Delete the contents of all of the word lists
 *
 * This function assumes that both the nodes and
 * the keys within the nodes have been allocated
 * using malloc() and need to be freed.
 */
void
deleteWordLists(LLNode *wordListHeads[], int maxLen)
{
	int i;

	for (i = 0; i < maxLen; i++) {
		if (wordListHeads[i] != NULL) {
			llFree(wordListHeads[i], deleteKey, NULL);
			wordListHeads[i] = NULL;
		}
	}
}


/** print out all of the data in a word list */
int
printData(char *filename, LLNode *wordListHeads[], int maxLen)
{
	LLNode *node;
	int i;

	printf("All word count data from file '%s':\n", filename);

	/**
	 * For each length, if the list is not null, print out
	 * the values in the list
	 */
	for (i = 0; i < maxLen; i++) {
		node = wordListHeads[i];
		if (node != NULL) {
			printf("Length %d:\n", i);
			while (node != NULL) {
				printf("    '%s' %d\n", node->key, node->value);
                node = node->next;
			}
		}
	}
	return 1;
}

/** TODO: print out only the hapax legomena in a word list */
int
printHapax(char *filename, LLNode *wordListHeads[],
		int maxLen, int hapaxLength) 
{
	//heading statement 
	if (hapaxLength == -1){
		printf("Hapax legomena from file '%s':\n", filename);

	}
	else{
		printf("Hapax legomena of length '%d' from file '%s':\n", hapaxLength, filename);

	}
	
	//loop to print out keys with only 1 value
	LLNode *temp;
	for(int i = 0; i < maxLen; i++){
		temp = wordListHeads[i];
		if(temp != NULL){
			while(temp != NULL){
				//if user did not specify hapax length
				if(hapaxLength == -1){
					if(temp->value == 1){
					printf("     %s \n", temp->key);
					}
					temp = temp->next;
				}
				//if user specified hapax length
				else{
					if(temp->value == 1 && strlen(temp->key) == hapaxLength){
					printf("     %s \n", temp->key);
					}
					temp = temp->next;
				}
			}
		}
	
	}


	return 1;
}

/* print out the command line help */
void
usage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Find and print the hapax legomena in one or more files.\n");
	fprintf(stderr, "A \"hapax legomenon\" is a word that occurs only once in the file\n");

	fprintf(stderr, "\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "    hapax [<options>] <datafile> [ <datafile> ...]\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-d     : print out all data loaded before printing hapax legomena.\n");
	fprintf(stderr, "-h     : this help.  You are looking at it.\n");
	fprintf(stderr, "-l <N> : only print hapax legomena of length <N>.\n");
	fprintf(stderr, "       : If no -l option is given, all hapax legomena are printed.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Sample command line:\n");
	fprintf(stderr, "    hapax -l5 smalldata.txt");
	fprintf(stderr, "\n");
	fprintf(stderr, "This example would print all words of length 5 that exist in the\n");
	fprintf(stderr, "file \"smalldata.txt\".\n");
	fprintf(stderr, "\n");

	// exit the program
	exit(1);
}


/**
 * Program mainline
 */

// define the maximum length of word we will look for, and by extension,
// the number of entries that must be in the array of word lists
#define	MAX_WORD_LEN	24

int
main(int argc, char **argv)
{
	int i, shouldPrintData = 0, didProcessing = 0, printHapaxLength = -1, skip = 0;

	/** TODO: allocate an array of list heads of the required size */
	struct LLNode **wordListHeads = (struct LLNode **) malloc (sizeof(struct LLNode *) * MAX_WORD_LEN);
	for (i = 0; i < MAX_WORD_LEN; ++i) {
        *(wordListHeads + i) = NULL;
    }

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			// TODO: Put your code to process the command line options here
			if(argv[i][1] == 'd'){
				shouldPrintData = 1;
			}
			else if(argv[i][1] == 'h'){
				//freeing the head list before it exits the program
				free(wordListHeads);
				usage();
			}
			//getting the length of hapax
			else if(argv[i][1] == 'l'){
				if (i + 1 < argc && strcmp(argv[i+1], "-d") != 0 && atoi(argv[i+1]) != 0) {
                    printHapaxLength = atoi(argv[i+1]);
					skip = 1;
                }

			}

		} else {

//			// Once you have set up your array of word lists, you
//			// should be able to pass them into this function
			//tallyWordsInFile(argv[i], wordListHeads, MAX_WORD_LEN);
	

			//skipping if length -l is given
			if(skip){
				skip = 0;
				continue;
			}
			/*if(skip == 1){
				strcpy(fileIn, argv[i+1]);
			} else{
				strcpy(fileIn, argv[i]);
			}*/

			if (tallyWordsInFile(argv[i], wordListHeads, MAX_WORD_LEN) == 0) {
			fprintf(stderr, "Error: Processing '%s' failed -- exitting\n",
				argv[i]);
				return 1;
			}

			didProcessing = 1;

			printf("Tally loaded\n");

			/**
			 * conditionally print out all the words loaded, based
			 * on the command line option
			 */

			if (shouldPrintData) {	
				//printing all data
				printData(argv[i], wordListHeads, MAX_WORD_LEN);
			}

			/** print out all the hapax legomena that we have found */
			printHapax(argv[i], wordListHeads, MAX_WORD_LEN, printHapaxLength);


		}
	}

	if ( ! didProcessing ) {
		fprintf(stderr, "No data processed -- provide the name of"
				" a file on the command line\n");
		usage();
		return 1;
	}

	// TODO: clean up any remaining memory that we have allocated
	deleteWordLists(wordListHeads, MAX_WORD_LEN);

	free(wordListHeads);

	return 0;
}



