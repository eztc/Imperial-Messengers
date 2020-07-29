# Imperial-Messengers
Solution to "Imperial Messengers" problem

This program is reads a text file as input and outputs a solution to the Imperial Messengers challenge.

Imperial Messengers challenge:
An empire has certain number of cities and has a network of limitless messengers set up between the cities. The challenge is to find the least amount of time required for all cities to receive the message.

Model:
Nodes - Cities
Edges - Travel time

Since the edges represent travel time, smaller edges could be traversed before larger edges. No limit was given on messengers, so the problem became a shortest path first algorithm.

Algorithm:
Initialize an array of city nodes and set the first node as the capital

While all cities haven’t been visited:
Set the current city to the city with the least travel time
Mark that city as visited
For each of that city’s neighbors:
x <- Add current city travel time with travel time to neighbor
If x is less than neighbor’s travel time
Update neighbor’s travel time
Return the last travel time when all cities have been visited

Note:
When I first started writing this algorithm, I wanted to reduce the 2D adjacency matrix to a 1D array. Since the described adjacency matrix had redundancies in the upper triangle, it seemed unnecessary to create the entire matrix.
Instead I loaded the input values from top to bottom, left to right into a 1D array. To access the time costs, I used the formula (i * (i - 1) / 2 + j) with the greater index as i and the lesser index as j. 
This effectively reduced the space complexity from O(N^2) to O(N).

Time Complexity:
Init                         O(N)
SendMessengers             O(N^2)
CityWithLeastTravelTime     O(N)
MsgSpread                 O(N)
