/**
 * Name: Tracy U
 * CS 5008, Fall 2025
 * Homework: City Finder
 * 
 * References: Initial code Graphs Codealong videos and Lab code
 * 
* Graph Reader - helps read in files of the format
* <source> <destination> <distance>
* Each time a line is read, it returns an edge
* representing the source, destination, and distance.

* The GraphReader structure contains a file pointer and a buffer for the current line.
* It handles its own memory management, freeing the previous line when a new one is read.
*
* Example usage:
* GraphReader* reader = reader_open("graph.txt");
* if (reader != NULL) {
*     edge_t* line;
*     while ((line = reader_next(reader)) != NULL) {
*         printf("Source: %s, Destination: %s, Distance: %d\n", line->src, line->dest, line->distance);
*     }
*     reader_close(reader);
* }
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "GraphReader.h"

#define BUFFER_SIZE 255

/**
* GraphReader - structure to hold the file pointer and current line data
* Opens a file for reading in graphe data. The file 
* should contain lines of the format:
* <source> <destination> <distance>
* Each time a line is read, it returns an edge_t 
* representing the source, destination, and distance.
* @param filename - the name of the file to read
* @return - a pointer to a GraphReader structure, or NULL if the file cannot be opened
**/
GraphReader* reader_open(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    
    GraphReader* reader = (GraphReader*)malloc(sizeof(GraphReader));
    if (reader == NULL) {
        fclose(file);
        return NULL;
    }
    
    reader->file = file;
    reader->currentLine = NULL;
    
    return reader;
}

/**
* reader_next - reads the next line from the graph file
* @param reader - a pointer to the GraphReader structure
* @return - an edge_t with 3 values representing the source, destination, and distance,
*           or NULL if end of file or error
**/
edge_t* reader_next(GraphReader* reader) {

    if (reader == NULL || reader->file == NULL) {
        return NULL;
    }
    
    // Free previous line if exists
    if (reader->currentLine != NULL) {
        free(reader->currentLine->src);
        free(reader->currentLine->dest);
        free(reader->currentLine);
        reader->currentLine = NULL;
    }
    
    // Allocate memory for the new line (now edge)
    reader->currentLine = (edge_t*)malloc(sizeof(edge_t));
    if (reader->currentLine == NULL) {
        return NULL;
    }

    // Allocate memory for edge parts to be read in
    char src[BUFFER_SIZE];
    char dest[BUFFER_SIZE];
    int distance;
    
    // Reference: https://www.geeksforgeeks.org/c/scanf-and-fscanf-in-c/
    if (fscanf(reader->file, "%s %s %d", 
               src,
               dest,
               &distance) != 3) {
        // If we couldn't read 3 values, clean up and return NULL
        free(reader->currentLine);
        reader->currentLine = NULL;
        return NULL;
    }

    // allocate memory for edge
    reader->currentLine->src = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char));
    reader->currentLine->dest = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char));

    if (reader->currentLine->src == NULL || reader->currentLine->dest == NULL) {
        // memory allocation issue
        free(reader->currentLine->src);
        free(reader->currentLine->dest);
        free(reader->currentLine);
        reader->currentLine = NULL;
        return NULL;
    }

    // set the values in the edge to those we read in
    strcpy(reader->currentLine->src, src);
    strcpy(reader->currentLine->dest, dest);
    reader->currentLine->distance = distance;
    
    return reader->currentLine;
}


/**
* reader_next - reads the next line from the graph file for vertices
* @param reader - a pointer to the GraphReader structure
* @return - a vertex 
**/
edge_t* reader_next_vertices(GraphReader* reader) {

    if (reader == NULL || reader->file == NULL) {
        return NULL;
    }
    
    // Free previous line if exists
    if (reader->currentLine != NULL) {
        free(reader->currentLine->src);
        free(reader->currentLine->dest);
        free(reader->currentLine);
        reader->currentLine = NULL;
    }
    
    // Allocate memory for the new line (now edge)
    reader->currentLine = (edge_t*)malloc(sizeof(edge_t));
    if (reader->currentLine == NULL) {
        return NULL;
    }

    // Allocate memory for vertex to be read in
    char vertex[BUFFER_SIZE];

    
    // Reference: https://www.geeksforgeeks.org/c/scanf-and-fscanf-in-c/
    if (fscanf(reader->file, "%s", 
               vertex
               ) != 1) {
        // If we couldn't read vertex, clean up and return NULL
        free(reader->currentLine);
        reader->currentLine = NULL;
        return NULL;
    }

    reader->currentLine->src = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char));

    if (reader->currentLine->src == NULL) {
        free(reader->currentLine);
        reader->currentLine = NULL;
        return NULL;
    }

    // set the values in the edge to those we read in or other values
    strcpy(reader->currentLine->src, vertex);
    reader->currentLine->dest = NULL;
    reader->currentLine->distance = 0;    
    return reader->currentLine;
}

/**
* reader_close - closes the GraphReader and frees allocated memory
* This function should be called when done with the GraphReader
* to avoid memory leaks.
* It closes the file and frees the memory allocated for the current line.
* @param reader - a pointer to the GraphReader structure
**/
void reader_close(GraphReader* reader) {
    if (reader != NULL) {
        if (reader->file != NULL) {
            fclose(reader->file);
        }
        if (reader->currentLine != NULL) {
            free(reader->currentLine);
        }
        free(reader);
    }
}