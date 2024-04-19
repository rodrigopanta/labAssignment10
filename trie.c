#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
  int count;
  struct Trie *children[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
  struct Trie *root = pTrie;

  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';

    if (root->children[index] == NULL) {
      struct Trie *newNode = (struct Trie *)malloc(sizeof(struct Trie));

      for (int j = 0; j < 26; j++) {
        newNode->children[j] = NULL;
      }
      newNode->count = 0;
      root->children[index] = newNode;
    }
    root = root->children[index];
  }
  root->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
  int count = 0;
  struct Trie *root = pTrie;

  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';

    if (root->children[index] == NULL) {
      return 0;
    }
    root = root->children[index];
  }
  count = root->count;

  return count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
  for (int i = 0; i < 26; i++) {
    if (pTrie->children[i] != NULL) {
      deallocateTrie(pTrie->children[i]);
    }
  }
  free(pTrie);
  return NULL;
}

// Initializes a trie structure
struct Trie *createTrie() {
  struct Trie *newTrie = (struct Trie *)malloc(sizeof(struct Trie));

  for (int i = 0; i < 26; i++) {
    newTrie->children[i] = NULL;
  }
  newTrie->count = 0;

  return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    fprintf(stderr, "Error opening file\n");
    exit(1);
  }

  int count = 0;
  char temp[100];

  while (fscanf(file, "%s", temp) != EOF) {
    pInWords[count] = malloc(strlen(temp) + 1);
    strcpy(pInWords[count], temp);
    count++;
  }
  fclose(file);
  return count;
}

int main(void) {
  char *inWords[256];

  // read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i = 0; i < numWords; ++i) {
    printf("%s\n", inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i = 0; i < numWords; i++) {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i = 0; i < 5; i++) {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}
