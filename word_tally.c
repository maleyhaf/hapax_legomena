#include <stdio.h>
#include <stdlib.h> // for malloc(), free()
#include <string.h>

#include "word_extractor.h"
#include "word_tally.h"

/**
 * A tool to hold the words we care about in an array, and
 * provide a method for processing the file.
 *
 */

// forward declarations
static int updateWordInTallyList(LLNode **wordLists, int maxLen, char *word);

/*
 * Here we do all the work, processing the
 * file and determining what to do for each word as we
 * read it.  Once we are done reading, we can then
 * examine our wordsToCheck list and see what their
 * state is
 */
int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen)
{
	struct WordExtractor *wordExtractor = NULL;
	char *aWord = NULL;
	// add any more variables that you need


	// create the extractor and open the file
	wordExtractor = weCreateExtractor(filename, maxLen);

	if (wordExtractor == NULL) {
		fprintf(stderr, "Failed creating extractor for '%s'\n", filename);
		return 0;
	}

	/** TODO: ensure that all of the word list heads are NULL */
	for (int i = 0; i < maxLen; ++i) {
        *(wordLists + i) = NULL;
    }
	// read each word from the file using the WordExtractor,
	// and for each tally how often it has been used in
	// the appropriate list

	// In the loop, figure out whether we have seen this
	// word before, and do the appropriate thing if we have

	int totalWordCount = 0;

	while (weHasMoreWords(wordExtractor)) {
		aWord = weGetNextWord(wordExtractor);
		totalWordCount++;

		// figure out whether we have seen this word before,
		// and do the appropriate thing if we have
		if (strlen(aWord) <= 25){
				updateWordInTallyList(wordLists, maxLen, aWord);
		}
	}

	// is there anything else you need to do at the end of the loop?
	printf("Total word count %d\n", totalWordCount);

	// Close the file when we are done
	weDeleteExtractor(wordExtractor);

	return 1;
}

/**
 * TODO: Either update the tally in the list, or add it to the list
 */
static int
updateWordInTallyList(LLNode **wordListHeads, int maxLen, char *word)
{

	/* TODO: look up the word in the correct list to see
	 * if we have already seen it */

	
	int wordPos = strlen(word);
	//searching the correct list for the word
	LLNode *temp = llLookupKey(wordListHeads[wordPos], word);

	//if word is found in the list
	if(temp != NULL){
		temp->value++;
		return 1;
	}
	//if word is not found in list/list is empty
	else{

		//new node to put in the list since word doesnt exist yet
		struct LLNode *newWord =  llNewNode(strdup(word), 1);
		//adding it to the end of the list
		wordListHeads[wordPos] = llAppend(wordListHeads[wordPos], newWord);

	}
	
	/** return success if no error */
	return 1;
}

