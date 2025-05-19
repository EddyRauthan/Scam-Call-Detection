#ifndef BLACKLIST_DETECTION_H
#define BLACKLIST_DETECTION_H

#include <stdbool.h>

#define CHAR_SIZE 10  // Digits 0-9

// Trie node structure
typedef struct TrieNode {
    struct TrieNode *children[CHAR_SIZE];
    bool isEndOfNumber;
} TrieNode;

// Function prototypes
TrieNode *createNode();
void insert(TrieNode *root, const char *number);
bool search(TrieNode *root, const char *number);
void loadBlacklist(TrieNode *root, const char *filename);

#endif // BLACKLIST_DETECTION_H
