/**
 * Reference: based on code-along, updated. 
* Solution Code for Adjacency List Representation of Graph Code Along
* @author Albert Lionelle
* @date 2025-05-20
**/



#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node_t {
    char* city; //city
    int distance;
    struct node_t* next;
} AdjListNode;

typedef struct {
    int numVertices;
    int capacity;
    AdjListNode** adjList;
    bool directed;
} AdjListGraph;

#define SCALE_FACTOR 2


AdjListGraph* createGraph(int capacity, bool directed); 
void freeGraph(AdjListGraph* graph);

void addEdge(AdjListGraph* graph, char* src, char* dest, int distance);
int getDegree(AdjListGraph* graph, char* city);
//char* getNeighbors(AdjListGraph* graph, char* city);
int getDistance(AdjListGraph* graph, char* src, char* dest);
void printGraph(AdjListGraph* graph);
void loadFromFile(AdjListGraph* graph, const char* verticesFilename, const char* distanceFilename);
int findCityIndex(AdjListGraph* graph, char* city);
AdjListNode* findNode(AdjListGraph* graph, char* city);
int addCityVertex(AdjListGraph* graph, char* city);
void printCityVertices(AdjListGraph* graph);



#endif /* ADJ_LIST_H */