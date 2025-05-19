#ifndef SUSPICIOUS_CALL_PATTERN_H
#define SUSPICIOUS_CALL_PATTERN_H

#include <stdbool.h>

#define MAX_CALLS 100
#define MAX_NUMBER_LENGTH 15

// Graph Node structure
typedef struct CallNode {
    char number[MAX_NUMBER_LENGTH];
    struct CallNode *next;
} CallNode;

// Graph structure
typedef struct {
    CallNode *head[MAX_CALLS];
    int callCount;
} CallGraph;

// Function prototypes
CallGraph *createGraph();
void addCall(CallGraph *graph, const char *number);
void displayCallLogs(CallGraph *graph);
void detectSuspiciousPatterns(CallGraph *graph);

#endif // SUSPICIOUS_CALL_PATTERN_H
