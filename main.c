//
//  main.c
//  VCTest
//
//  Created by han on 7/23/20.
//  Copyright © 2020 Han. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

//Function declarations
typedef struct node node;
void init(char* file);
int SendMessengers(void);
bool MsgSpread(node* cities);
int CityWithLeastTravelTime(node* cities);
int getNumElements(int n);
int getIndex(int i, int j);

//Number of cities: n
//Adjacency array: adjArr
int n;
int *adjArr;

int main(int argc, const char * argv[]) {
    init("input.txt");
    printf("%d\n", SendMessengers());
    return 0;
}

//Read input file, create 1D array for travel times
void init(char* file) {
    FILE *f = fopen(file, "r");
    if (f == NULL) {
        printf("Couldn't open file\n");
        exit(1);
    }

    fscanf(f, "%d", &n);
    
    adjArr = malloc(getNumElements(n) * sizeof(int));
    char line[256];
    int count = 0;
    while (fscanf(f, "%256s", line) == 1) {
        if (line[0] == 'x') {
            adjArr[count] = -1;
        } else {
            adjArr[count] = (int) atoi(line);
        }
        count++;
    }
    fclose(f);
};

struct node {
    int index;
    int travelTime;
    bool visited;
};

int SendMessengers() {
    
    struct node cities[n];
    for (int i = 0; i < n; i++) {
        cities[i].travelTime = INT_MAX;
        cities[i].visited = false;
    }
    cities[0].travelTime = 0;
    
    int currIndex = 0;
    int minTime = INT_MAX;
    int adjArrIndex;
    while (!MsgSpread(cities)) {
        currIndex = CityWithLeastTravelTime(cities);
        cities[currIndex].visited = true;
        for (int i = 0; i < n; i++) {
            //Skips itself and cities already visited
            if (currIndex != i && !cities[i].visited) {
                adjArrIndex = getIndex(i > currIndex ? i : currIndex, i < currIndex ? i : currIndex);
                //Checks if there's a path to the city
                if (adjArr[adjArrIndex] > 0) {
                    minTime = cities[currIndex].travelTime + adjArr[adjArrIndex];
                    if (minTime < cities[i].travelTime) {
                        cities[i].travelTime = minTime;
                    }
                }
            }
        }
    }
    return cities[currIndex].travelTime;
}

//Checks to see if the message has been sent to all cities
bool MsgSpread(node* cities) {
    bool isSpread = true;
    for (int i = 0; i < n; i++) {
        if (!cities[i].visited) {
            isSpread = false;
            break;
        }
    }
    return isSpread;
}

//Chooses an unvisited city with the least travel time
int CityWithLeastTravelTime(node* cities) {
    int desiredCityIndex = -1;
    int minTime = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        if (cities[i].travelTime < minTime && !cities[i].visited) {
            desiredCityIndex = i;
            minTime = cities[i].travelTime;
        }
    }
    
    if (desiredCityIndex == -1) {
        printf("Couldn't find desired city");
        exit(1);
    }
    
    return desiredCityIndex;
}

//Gets index of adjArr based off the the pair of cities
int getIndex(int i, int j) {
    return (i * (i - 1) / 2 + j);
}

//Calculates adjArr size based off number of cities n
int getNumElements(int n) {
    return (n - 1) * n / 2;
}





