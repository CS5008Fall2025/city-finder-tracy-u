/**
 * 
 * 
 * 
 * 
 * References: Guessing Game Code Alongs. 
 * whitespace input: https://www.geeksforgeeks.org/c/taking-string-input-space-c-3-different-methods/
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_INPUT_LIMIT 20


char* getInput() {
    char* str = malloc(MAX_INPUT_LIMIT * sizeof(char));
    scanf("%[^\n]%*c", str);
    
    // TODO: string handling?
    return str;
}

void printHelp() {
    printf("Commands:\n");
    printf("\t\tlist - list all cities\n");
    printf("\t\t<city1> <city2> - find the shortest path between two cities\n");
    printf("\t\thelp - print this help message\n");
    printf("\t\texit - exit the program\n");
}

void printCityList() {
    // TODO
    printf("printing a city list\n");
}

void validateCities(char* city1, char* city2) {
    // confirm cities are in list before proceeding
    // TODO
}

void start() {
    // TODO
    printf("Welcome ...\n"); // UPDATE
    printHelp();
    char* menuChoice;

    while(strcmp(menuChoice, "exit") != 0) {
        printf("Where do you want to go today? ");
        menuChoice = getInput();

        // if (menuChoice has two parts) { 
        //     if (validateCities(city1, city2)) {
        //         findShortestPath();
        //     }
        // }

        if (strcasecmp(menuChoice, "list") == 0) {
            printCityList();
        } else if (strcasecmp(menuChoice, "help") == 0) {
            printHelp();
        } else if (strcasecmp(menuChoice, "exit") == 0) {
            printf("Byyyyeeeee!\n");
        } else {
            printf("Invalid Command\n");
            printHelp();
        }
    } 
}


void findShortestPath(char* city1, char* city2) {
    // TO DO 
}

// todo : update to parse arguments
int main() {
    start();

    return 0;
}

/* EXPECTED OUTPUT


*****Welcome to the shortest path finder!******
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
*******************************************************
Where do you want to go today? what do i do?
Invalid Command
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
Where do you want to go today? list
a
b
c
d
e
f
g
x
Where do you want to go today? a f
Path Found...
        a
        c
        e
        f
Total Distance: 10
Where do you want to go today? f a
Path Found...
        f
        e
        c
        a
Total Distance: 10
Where do you want to go today? a x
Path Not Found...
Where do you want to go today? boston maine
Invalid Command
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
Where do you want to go today? help
Commands:
        list - list all cities
        <city1> <city2> - find the shortest path between two cities
        help - print this help message
        exit - exit the program
Where do you want to go today? exit
Goodbye!

*/
