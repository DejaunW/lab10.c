/*Dejaun Wilmott, lab 10*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int isWord;
    struct Trie *next[26];
};


// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	 if (*word == '\0')
	 {
        pTrie->isWord = 1;
        return;
    }

    int nextIndex = *word - 'a';
	//cehck if next place exists, if not, make one
    if (pTrie->next[nextIndex] == NULL)
        pTrie->next[nextIndex] = createTrie();

    insert(pTrie->next[nextIndex], word + 1);


}




// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	//int k = 0;

    // if (k == strlen(word))
	// {
    //     return pTrie->isWord;
	// }

	if (*word == '\0')
    {
        return pTrie->isWord;
    }

    //int nextIndex = word[k] - 'a';

	int nextIndex = *word - 'a';

    if (pTrie->next[nextIndex] == NULL)
	{
        return 0;
	}

    return numberOfOccurances(pTrie->next[nextIndex], word + 1 );
}


// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
	{
        return;
	}

    for (int i = 0; i < 26; i++)
	{
		deallocateTrie(pTrie->next[i]);
	}

    free(pTrie);
}



// Initializes a trie structure
struct Trie *createTrie()
{
    // Create the struct, not a word.
    struct Trie *pTrie = malloc(sizeof (struct Trie));
    
    pTrie->isWord = 0;

    // Set each pointer to NULLL.
    int i;
    for (i=0; i<26; i++)
    pTrie->next[i] = NULL;

    return pTrie;

}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE *file = fopen(filename, "r");

	if(file == NULL)
	{
		return -1;
	}

	int count = 0;

	fscanf(file, "%d\n", &count);
	char word[100];
	for(int i = 0; i< count; i++)
	{
		fscanf(file, "%s\n", word);
		pInWords[i] = (char*)calloc(strlen(word)+1, sizeof(char));
		strcpy(pInWords[i], word);

	}

	return count;

}




int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}