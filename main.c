// Main file of the t9 program
// Chiho Kim
// CSE Homework 5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#define WORDSIZE 100

// array used to convert a letter to a keypad digit
// int* num: this array is given to be modified
// and returned so that we can use it in the main
int* numbers(int* num) {
  // multiplier
  int mult = 1;
  // of the first 15 alphabets, each 3 elements will have
  // keypad digits 2, 3, 4, 5 and 6
  for (int i = 0; i < 15; i++) {
    if (3*mult == i) {
      mult++;
    }
    num[i] = mult+1;
  }
  // PQRS will have 7
  for (int i = 15; i < 19; i++) {
    num[i] = 7;
  }
  // TUV will have 8
  for (int i = 19; i < 22; i++) {
    num[i] = 8;
  }
  // WXYZ will have 9
  for (int i = 22; i < 26; i++) {
    num[i] = 9;
  }
  return num;
}

// create the trie dictionary
// Node* root: root of the trie dictionary
// FILE* file: file containing the dictionary words
void makeDict(struct Node* root, FILE* file) {
  // prepare conversion of 26 letters to keypad digits
  int* num = (int*)malloc(26 * sizeof(int));
  num = numbers(num);
  char line[WORDSIZE];
  // insert all words from the dictionary file to the trie
  while (fgets(line, sizeof(line), file)) {
    insert(root, line, num);
  }
  free(num);
}

// look up a word for the given sequence
// Node* root: root of the trie dictionary
void lookUp(struct Node* root) {
  printf("Enter \"exit\" to quit.\n");
  printf("Enter Key Sequence (or \"#\" for next word):\n");
  // seq: key sequence from user input
  // prev: previous sequence
  // word: vocabulary word retrieved from the sequence
  char seq[WORDSIZE];
  char prev[WORDSIZE];
  char* word;
  // scan the user input to find the vocab word
  // exit when user types ctrl+d or "exit"
  while (scanf("%s", seq) != EOF) {
    if (strncmp(seq, "exit", WORDSIZE) == 0) {
      break;
    }
    // if the sequence is "#", append it to the previous sequence
    // and set the appended sequence to the current sequence
    if (strncmp(seq, "#", WORDSIZE) == 0) {
      strncat(prev, "#", WORDSIZE);
      strncpy(seq, prev, WORDSIZE);
    }
    strncpy(prev, seq, WORDSIZE);
    // find the word corresponding to the sequence
    word = findWord(root, seq);
    if (word) {
      printf("'%s'\n", word);
      // if the word doesn't exist while the sequence contained '#',
      // say that there is no more t9onyms
    } else if (strstr(seq, "#")) {
      printf("There are no more T9onyms\n");
      // if the word doesn't exist and the sequence doesn't have '#',
      // say that the word converted from the sequence is not found
    } else {
      printf("Not found in the current directory.\n");
    }
    printf("Enter Key Sequence (or \"#\" for next word):\n");
  }
}

// open the file from the first argument, create a trie dictioniary,
// look up the sequence provided by the user, and then remove the trie
int main(int argc, char** argv) {
  if (argc > 0) {
    FILE* file;
    file = fopen(argv[1], "r");
    // if file exists, create the dictionary trie
    if (file) {
      struct Node* root = getNode();
      makeDict(root, file);
      lookUp(root);
      removeTrie(root);
      fclose(file);
    } else {
      // if file doesn't exist, print an error message.
      fprintf(stderr, "Error: file '%s' does not exist.\n", argv[1]);
    }
  }
  return 0;
}
