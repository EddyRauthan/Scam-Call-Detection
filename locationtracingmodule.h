#ifndef LOCATION_TRACING_MODULE_H
#define LOCATION_TRACING_MODULE_H

#define MAX_PREFIXES 100
#define MAX_REGION_NAME 50

// Structure to store prefix and its region
typedef struct {
    char prefix[10];
    char region[MAX_REGION_NAME];
} PrefixMapping;

// Function prototypes
void loadPrefixMappings(const char *filename);
void findRegion(const char *number);

#endif // LOCATION_TRACING_MODULE_H
