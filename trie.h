// Header file of the trie data structure
// Chiho Kim
// CSE 374 Homework 5

#ifndef TRIE_H
#define TRIE_H

// declare the data type Node which will compose a trie
// leaf: shows whether the node has any children
// e.g. leaf = 0 if there is no children, leaf = 1 if there is a child
// vocab: stores the dictionary word
// node will have 10 children from 0 to 9
typedef struct Node {
  int leaf;
  char* vocab;
  struct Node * children[10];
} Node;

// declare functions in the trie.c source file
Node* getNode();
void insert(Node* root, char* word, int* num);
char* findWord(Node* root, char* key);
void removeTrie(Node* root);

#endif
