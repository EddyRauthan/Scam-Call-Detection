#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "blacklistdetection.h"
#include "suspiciouscallpattern.h"
#include "locationtracingmodule.h"

// File paths
#define BLACKLIST_FILE "blacklist.txt"
#define PREFIX_FILE "prefix_mappings.txt"
#define CALL_LOG_FILE "call_logs.txt"

// === Global Variables ===
TrieNode *root;       // For blacklist detection
CallGraph *callGraph;     // For suspicious pattern detection

// Function prototypes
void logCall(const char *number);
void displayMenu();
void handleOption(int option);
void displayCallHistory();

// === Menu Display ===
void displayMenu() {
    printf("\n===== Scam Call Detection System =====\n");
    printf("1. Check if Number is Blacklisted\n");
    printf("2. Check Call History for Suspicious Patterns\n");
    printf("3. Locate Caller Region\n");
    printf("4. Log New Call\n");
    printf("5. Display Call History\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

// === Call Logger ===
void logCall(const char *number) {
    FILE *file = fopen(CALL_LOG_FILE, "a");
    if (!file) {
        printf("Error opening call log file.\n");
        return;
    }
    fprintf(file, "%s\n", number);
    fclose(file);
    printf("Call logged successfully.\n");
}

// === Display Call History ===
void displayCallHistory() {
    printf("\n=== Call History ===\n");
    FILE *file = fopen(CALL_LOG_FILE, "r");
    if (!file) {
        printf("No call history available.\n");
        return;
    }
    char number[20];
    while (fscanf(file, "%s", number) != EOF) {
        printf("%s\n", number);
    }
    fclose(file);
}

// === Handle Menu Option ===
void handleOption(int option) {
    char query[20];

    switch (option) {
        case 1:
            printf("Enter number to check: ");
            scanf("%s", query);
            if (search(root, query))
                printf("Alert: Number is blacklisted!\n");
            else
                printf("Number is not blacklisted.\n");
            break;

        case 2:
            detectSuspiciousPatterns(callGraph);
            break;

        case 3:
            printf("Enter phone number to locate: ");
            scanf("%s", query);
            findRegion(query);
            break;

        case 4:
            printf("Enter number to log: ");
            scanf("%s", query);
            logCall(query);
            break;

        case 5:
            displayCallHistory();
            break;

        case 6:
            printf("Exiting...\n");
            exit(0);
            break;

        default:
            printf("Invalid option. Try again.\n");
    }
}

// === Main Function ===
int main() {
    // Initialize Trie for blacklist
        printf("Program started\n");  // Debug print

    root = createNode();
    loadBlacklist(root, BLACKLIST_FILE);

    // Initialize Graph for suspicious pattern detection
    callGraph = createGraph();

    // Load prefix mappings for location tracing
    loadPrefixMappings(PREFIX_FILE);

    // Menu loop
    int option;
    while (1) {
        printf("Waiting for user input...\n");  // Debug print
        displayMenu();
        if (scanf("%d", &option) != 1) {
            printf("Failed to read input. Exiting.\n");
            break;
        }
        handleOption(option);
    }

    return 0;
}
