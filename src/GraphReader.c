/**
 * 
 * 
 * References: From graphs codealong 
 * 
 * TODO: modify for string, string, int (currently int, int, int)
 */



/**
* Graph Reader - helps read in files of the format
* <source> <destination> <weight>
* Each time a line is read, it returns an array of 3 integers
* representing the source, destination, and weight.

* The GraphReader structure contains a file pointer and a buffer for the current line.
* It handles its own memory management, freeing the previous line when a new one is read.
*
* Example usage:
* GraphReader* reader = reader_open("graph.txt");
* if (reader != NULL) {
*     int* line;
*     while ((line = reader_next(reader)) != NULL) {
*         printf("Source: %d, Destination: %d, Weight: %d\n", line[0], line[1], line[2]);
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
* <source> <destination> <weight>
* Each time a line is read, it returns an array of 3 integers
* representing the source, destination, and weight.
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
* @return - an array of 3 values representing the source, destination, and distance,
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
    
   // Read data of file in specific formats
    // while (fscanf(reader->file, "%s %s %d", 
    //            src,
    //            dest,
    //            distance) == 3) {
    //     printf("src: %s\t dest: %s\t distance: %d\n", src, dest, *distance);
    // }



    // TODO -- this needs to be updated?
    // https://www.geeksforgeeks.org/c/scanf-and-fscanf-in-c/
    if (fscanf(reader->file, "%255s %255s %d", 
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
    

    // if (!(reader->currentLine == NULL)) {
    //     printf("[0]: %s\t [1]: %s\t [2]: %s\n", 
    //         reader->currentLine[0], 
    //         reader->currentLine[1], 
    //         reader->currentLine[2]);
    // }

    // if (fscanf(reader->file, "%s %s %d", 
    //            src,
    //            dest,
    //            distance) != 3) {
    //     // If we couldn't read 3 values, clean up and return NULL
    //     free(reader->currentLine);
    //     reader->currentLine = NULL;
    //     return NULL;
    // }

    // while (fscanf(reader->file, "%255s %255s %d", 
    //            src,
    //            dest,
    //            &distance) == 3) {
    //     // If we couldn't read 3 values, clean up and return NULL
    //     printf("Source: %s, Destination: %s, Distance: %d\n", src, dest, distance);
    // }


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