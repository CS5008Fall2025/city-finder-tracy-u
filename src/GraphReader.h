/**
 * 
 * 
 * References: From graphs codealong 
 * 
 * 
 */

#ifndef GRAPH_READER_H
#define GRAPH_READER_H

/* 
 * GraphReader.h
 * Header file for reading graph data from files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Edge structure to read into 
typedef struct edge_t
{
    char* src;
    char* dest;
    int distance;
} edge_t;

// Structure to hold the file pointer and current line data
typedef struct GraphReader {
    FILE* file;
    edge_t* currentLine;
} GraphReader;


GraphReader* reader_open(const char* filename);
edge_t* reader_next(GraphReader* reader);
void reader_close(GraphReader* reader);

#endif /* GRAPH_READER_H */