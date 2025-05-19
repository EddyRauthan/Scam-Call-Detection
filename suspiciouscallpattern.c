#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "blacklistdetection.h"
#include "suspiciouscallpattern.h"

#define MAX_CALLS 100
#define MAX_NUMBER_LENGTH 15

// Initialize a graph
CallGraph *createGraph() {
    CallGraph *graph = (CallGraph *)malloc(sizeof(CallGraph));
    graph->callCount = 0;
    for (int i = 0; i < MAX_CALLS; i++)
        graph->head[i] = NULL;
    return graph;
}

// Add a call to the graph
void addCall(CallGraph *graph, const char *number) {
    if (graph->callCount >= MAX_CALLS) {
        printf("Maximum call limit reached.\n");
        return;
    }

    CallNode *newNode = (CallNode *)malloc(sizeof(CallNode));
    strcpy(newNode->number, number);
    newNode->next = graph->head[graph->callCount];
    graph->head[graph->callCount] = newNode;
    graph->callCount++;
}

// Display call logs
void displayCallLogs(CallGraph *graph) {
    printf("Call Logs:\n");
    for (int i = 0; i < graph->callCount; i++) {
        CallNode *temp = graph->head[i];
        while (temp) {
            printf("%s -> ", temp->number);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Detect suspicious patterns (simple heuristic: repeated calls)
void detectSuspiciousPatterns(CallGraph *graph) {
    printf("Suspicious Patterns Detected:\n");
    for (int i = 0; i < graph->callCount; i++) {
        CallNode *temp = graph->head[i];
        while (temp && temp->next) {
            if (strcmp(temp->number, temp->next->number) == 0) {
                printf("Repeated call detected: %s\n", temp->number);
            }
            temp = temp->next;
        }
    }
}

// Main function for testing
// int main() {
//     CallGraph *graph = createGraph();
//     addCall(graph, "1234567890");
//     addCall(graph, "1234567890");
//     addCall(graph, "0987654321");
//     addCall(graph, "1234567890");

//     displayCallLogs(graph);
//     detectSuspiciousPatterns(graph);

//     return 0;
// }