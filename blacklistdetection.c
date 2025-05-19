#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "blacklistdetection.h"

TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->isEndOfNumber = false;
    for (int i = 0; i < CHAR_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode *root, const char *number) {
    TrieNode *curr = root;
    while (*number) {
        int index = *number - '0';
        if (curr->children[index] == NULL)
            curr->children[index] = createNode();
        curr = curr->children[index];
        number++;
    }
    curr->isEndOfNumber = true;
}

bool search(TrieNode *root, const char *number) {
    TrieNode *curr = root;
    while (*number) {
        int index = *number - '0';
        if (curr->children[index] == NULL)
            return false;
        curr = curr->children[index];
        number++;
    }
    return curr != NULL && curr->isEndOfNumber;
}

void loadBlacklist(TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return;
    }
    char number[20];
    while (fscanf(file, "%s", number) != EOF) {
        insert(root, number);
    }
    fclose(file);
}
