# Dictionary-Trie

'make' will produce a t9 file that will be run with dictionary.txt as its argument.

The program will create a trie of the dictionary words from the input file. Each letter of each word will be converted to the corresponding digit, from 1 to 9, and two different words of the same number sequence will be distinguished by a '#' at the end of the latter word's sequence.

The user will then be prompted to type a number sequence, with which it will find the vocabulary word it has stored in the trie.

When the user exits, the program completely removes the trie with no memory leaks.
