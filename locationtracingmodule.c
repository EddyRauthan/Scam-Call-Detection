#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "blacklistdetection.h"
#include "suspiciouscallpattern.h"
#include "locationtracingmodule.h"


#define MAX_PREFIXES 100
#define MAX_REGION_NAME 50

PrefixMapping prefixDB[MAX_PREFIXES];
int prefixCount = 0;

// Function to load prefix mappings from a file
void loadPrefixMappings(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return;
    }
    while (fscanf(file, "%s %s", prefixDB[prefixCount].prefix, prefixDB[prefixCount].region) != EOF) {
        prefixCount++;
    }
    fclose(file);
}

// Function to find the region of a given number
void findRegion(const char *number) {
    for (int i = 0; i < prefixCount; i++) {
        if (strncmp(number, prefixDB[i].prefix, strlen(prefixDB[i].prefix)) == 0) {
            printf("Location: %s\n", prefixDB[i].region);
            return;
        }
    }
    printf("Location not found.\n");
}

// Main function for testing
// int main() {
//     loadPrefixMappings("prefix_mappings.txt");

//     char query[20];
//     printf("Enter phone number to locate: ");
//     scanf("%s", query);

//     findRegion(query);
//     return 0;
// }