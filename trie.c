// Source file of the trie data structure
// Chiho Kim
// CSE 374 Homework 5

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

// create a new node and return it
struct Node* getNode() {
  struct Node* current = (struct Node*)malloc(sizeof(struct Node));
  current->leaf = 0;
  current->vocab = NULL;
  for (int i = 0; i < 10; i++) {
    current->children[i] = NULL;
  }
  return current;
}

// insert a word into the dictionary
// Node* root: root of the trie dictionary
// char* word: word to insert
// int* num: array used to convert letters to the "keypad" digits
void insert(struct Node* root, char* word, int* num) {
  // this will become the keypad number
  int index = 0;
  struct Node* current = root;
  // change newline '\n' to end of string '\0'
  word[strlen(word)-1] = '\0';
  for (int i = 0; i < strlen(word); i++) {
    // convert a letter to a number, e.g. a -> 0, b -> 1, c -> 2,...
    index = word[i]+'0'-145;
    // set index to the keypad number by looking up the letter in the num array
    index = num[index];
    if (!current->children[index]) {
      current->children[index] = getNode();
    }
    // if the node has a child, it is no longer a leaf
    current->leaf = 1;
    current = current->children[index];
  }
  // if the given word has the same key sequence as another word
  // in the dictionary, go to children[0]
  // this will be called by #'s later
  while (current->vocab) {
    if (!current->children[0]) {
      current->children[0] = getNode();
    }
    current->leaf = 1;
    current = current->children[0];
  }
  // store word in the the current node's vocab
  current->vocab = malloc(strlen(word)+1);
  strncpy(current->vocab, word, strlen(word)+1);
}

// find the word in the dictionary from given key sequence
// Node* root: root of the trie dictionary
// char* key: key sequence
char* findWord(struct Node* root, char* key) {
  struct Node *current = root;
  for (int i = 0; i < strlen(key); i++) {
    // index of the key initialized at 1 because we don't use index 1
    int index = 1;
    // if key is "#", we will look at children[0] for a t9onym
    if (key[i] == '#') {
      index = 0;
      // else we will convert the character into integer
      // to go to the corresponding child
    } else if (key[i]-'0' > 1) {
      index = key[i]-'0';
    }
    // if the desired child node exists move pointer to the child
    // else return null and exit
    if (current->children[index]) {
      current = current->children[index];
    } else {
      return NULL;
    }
  }
  return current->vocab;
}

// completely remove the trie without memory leaks
// Node* root: root of the trie dictionary
void removeTrie(struct Node* root) {
  // base case is when a leaf node is reached
  if (root->leaf == 0) {
    free(root->vocab);
    free(root);
  } else {
    // search every existing nodes to free memory
    for (int i = 0; i < 10; i++) {
      if (root->children[i]) {
        removeTrie(root->children[i]);
      }
    }
    free(root->vocab);
    free(root);
  }
}


