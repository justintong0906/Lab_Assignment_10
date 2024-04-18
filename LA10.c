#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int count;
	struct Trie* letter[26];
};


// Initializes a trie structure
struct Trie* createTrie()
{
	struct Trie* newtree = (struct Trie*)calloc(1, sizeof(struct Trie));
	return newtree;
}

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
	int letterdex;
	struct Trie* temp = pTrie;
	for (int i = 0;i < strlen(word); i++) {
		letterdex = (word[i] - 'a');
		if (temp->letter[letterdex] == NULL) {
			struct Trie* newnode = createTrie();
			temp->letter[letterdex] = newnode;
		}
		temp = temp->letter[letterdex];
	}
	temp->count++;

	return;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word)
{
	struct Trie* temp = pTrie;
	int letterdex;

	for (int i = 0;i < strlen(word);i++) {
		letterdex = (word[i] - 'a');

		if (temp->letter[letterdex] == NULL)
			return 0;
		temp = temp->letter[letterdex];
	}
	return temp->count;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{

	for (int i = 0;i < 26;i++) {
		if (pTrie->letter[i] != NULL) 
			deallocateTrie(pTrie->letter[i]);
	}
	free(pTrie);
	pTrie = NULL;

	return pTrie;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords) {
	FILE* f1 = fopen(filename, "r");
	if (f1 == NULL) 
		return -1;
	int n;
	char word[50];
	fscanf(f1, "%d", &n);
	for (int i = 0;i < n;i++) {
		fscanf(f1, "%s", word);
		pInWords[i] = (char*)calloc(strlen(word)+1, sizeof(char));
		strcpy(pInWords[i], word);
	}

	fclose(f1);
	return n;
}


int main(void)
{
	char* inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0;i < numWords;++i)
	{
		printf("%s\n", inWords[i]);
	}

	struct Trie* pTrie = createTrie();
	for (int i = 0;i < numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
	for (int i = 0;i < 5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}