

/*
 
   Kurt Malana
 
*/

#include "connectedcities.h"

/**
 * <p>
 * Part A 
 * ---------------------------------------------------------------------------------------
 * For each city in a city list, find the list of reachable cities starting from the city 
 * following the train routes, and sort the cities in the descending order based on the 
 * number of their reachable cities.  
 * 
 * Required specifications - 
 *
 * Given a list of cities, and a list of one-way train routes from one city to another:
 *
 * 1) Create a graph with each node in the graph as an instance of the CityNode class,
 *    the graph can use any STL collection by your choice.
 *
 * 2) Populate the direct routes information to each CityNode's directRoutedCities collection.
 *    This is like an adjacency list graph representation.
 *
 * 3) For each city node in the graph, use Depth First Search algorithm to find all reachable 
 *    cities starting from the city following the train routes and store those reachable cities to 
 *    the CityNode's reachableCities collection. 
 *
 *    IMPORTANT: The reachable cities must include the starting city itself.  
 *
 *    Note: The train route can go from the starting city and stop at several cities 
 *          before reaching the destination city, all cities including the starting city and 
 *          the destination city along the path would be counted as reachable cities from 
 *          the city where the train starts.
 *
 * 4) Sort the cities in the descending order based on the number of their reachable cities,
 *    so that after sorting, starting from the first city in the sorted order, the train can 
 *    reach the greatest number of destination cities following the given one-way routes. 
 *
 * 5) You must use a RECURSIVE algorithm to implement the Depth First Search part to find
 *    all reachable cities from a starting city given the train routes, using an iterative 
 *    approach would result in a 30% penalty to your assignment 4 grade.  
 *
 * 6) You may add necessary helper functions as needed. Follow the comments for hints.
 * 
 * Assumptions - 
 * 1) Each city is represented by a unique two-letter code like "SD", "LA", 
 *    "SF", "SJ", "NY", etc.
 * 2) Each one-way train route is represented by a pair of city codes; for example, 
 *    route {"SD", "LA"} means train can drive one-way from San Diego (SD) to 
 *    Los Angeles (LA). 
 *
 * <p>
 * Part B
 * ---------------------------------------------------------------------------------------
 * Show the upper bound of the time complexity of this function would be O(c^2 + c * r) 
 * where:
 * c is the number of cities
 * r is the number of direct routes between cities
 * 
 * ---------------------------------------------------------------------------------------
 * @param  cities  a list of cities with each city identified by a two letter code
 * @param  routes  pairs of one-way train routes with each one-way train route represented 
 *                 by a pair of city codes; for example, route {"SD", "LA"} means train 
 *                 can go one-way from San Diego (SD) to Los Angeles (LA).
 *
 *                 NOTE: examples of routes are { {"SD", "LA"},
 *                                                {"LA", "SJ"},
 *                                                {"SJ", "SF"}
 *                                              }   
 *                       refer to driver.cpp for more examples.  
 *
 * @return       A list of CityNode in the descending order based on the number of their 
 *               reachable cities following the train routes
 
* @see         
*/
vector<CityNode> ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(
                                    vector<string> cities, 
                                    vector<pair<string, string>> trainRoutes) {

    unordered_map<string, CityNode> cityGraph; // graph map
    unordered_map<string, bool> visitedCities; // for dfs use
    vector<CityNode> returnVector; // returnVector
    
    // sets cityGraph map with keys of city names
    makeCityMap(cityGraph, cities); 
    
    // populates a city in cityGraph with it's adjacent cities
    makeAdjacencyGraph(cityGraph, trainRoutes); 
    
    // dfs of reachable cities and populates a vector of reachableCities
    depthFirstSearchReachableCities(cityGraph, cities, visitedCities); 

    // Populates returnVector with all cities in cityGraph
    for(auto city : cities){
        returnVector.push_back(cityGraph.at(city));
    }
    
    // sort returnVector based on city name
    sort(returnVector.begin(), returnVector.end(),
    [](CityNode& x, CityNode& y)
    {
        return x.getCity() < y.getCity();
    }
    );
    
    // sort returnVector based on reachableCities numbers
    sort(returnVector.begin(), returnVector.end(),
    [](CityNode& x, CityNode& y)
    {
        return x.getReachableCities().size() > y.getReachableCities().size();
    }
    );
    
  return returnVector; // returns a vector of cites with populated CityNode
}

// makeCityMap populates a map that contains
// city name as the key and CityNode as the data
void ConnectedCities::makeCityMap(unordered_map<string, CityNode> &cityGraph,
                                    vector<string> cities){
    
        for(int i = 0; i < cities.size(); i++){
            CityNode currCity = CityNode(cities[i]);
            cityGraph.emplace(pair<string, CityNode>(cities[i], currCity));
        }
}

// makeAdjacencyGraph populates the adjacency vector
// of the CityNode using a map
void ConnectedCities::makeAdjacencyGraph(unordered_map<string, CityNode> &cityGraph, 
                                            vector<pair<string, string>> trainRoutes){
        
    for(auto& pair: trainRoutes){
        cityGraph.at(pair.first).addADirectRoutedCity(pair.second);
    }
}


// Traverses through cities in cities vector to
// populate reachableCities for each city in cityGraph
void ConnectedCities::depthFirstSearchReachableCities(unordered_map<string, CityNode> &cityGraph, 
                                                        vector<string> cities,
                                                        unordered_map<string, bool> &visitedCities){
    for(int i = 0; i < cities.size(); i++){
        vector<string> reachableCities = cityGraph.at(cities[i]).getReachableCities();
        dfsHelper(cityGraph, cities[i], reachableCities, visitedCities);
        cityGraph.at(cities[i]).setReachableCities(reachableCities);
        visitedCities.clear();
    }   
}

// dfs helper of all reachableCities with a starting city.
void ConnectedCities::dfsHelper(unordered_map<string, CityNode> &cityGraph, string startingCity,
                                                        vector<string> &reachableCities,
                                                        unordered_map<string, bool> &visitedCities){
    visitedCities[startingCity] = true;
    reachableCities.push_back(startingCity);
    for(auto& city : cityGraph.at(startingCity).getDirectRoutedCities()){
       if(!visitedCities[city]){
           dfsHelper(cityGraph, city, reachableCities, visitedCities);
       }
    }
}





