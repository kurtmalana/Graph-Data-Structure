
/*

   Kurt Malana
 
*/ 
 

#include "connectedcities.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
		// If you do comment this out, ignore the
		// "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    
    // Begin Testing
    
    /* 
        *    SD ---> DL <--------         
        *    ^                   |
        *    |                   |
        *    OD <--- JL <--------|--
        *                        |  |
        *    BV <---             |  |
        *    --->  LA ---> BU    |  |
        *          ^             |  |
        *          |             |  |
        *  SJ ---> SK ---> IV ---|  |
        *                           |
        *  <---------------         |
        *  SF ---> HT ---> NH ------|
        * */

    vector<string> cities_1 {"SD", "LA", "SK", "IV", "JL", "SF", 
                             "DL", "HT", "OD", "NH", "BV", "SJ", "BU"};

    vector<pair<string, string>> trainRoutes;

    trainRoutes.emplace_back("JL", "OD");
    trainRoutes.emplace_back("OD", "SD");
    trainRoutes.emplace_back("SD", "DL");
    trainRoutes.emplace_back("BV", "LA");
    trainRoutes.emplace_back("LA", "BV");
    trainRoutes.emplace_back("LA", "BU");
    trainRoutes.emplace_back("SK", "IV");
    trainRoutes.emplace_back("SK", "LA");
    trainRoutes.emplace_back("SJ", "SK");

    trainRoutes.emplace_back("IV", "DL");
    
    trainRoutes.emplace_back("SF", "HT");
    trainRoutes.emplace_back("HT", "NH");
    trainRoutes.emplace_back("NH", "SF");
    trainRoutes.emplace_back("NH", "JL");

    vector<CityNode> cities = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_1, trainRoutes);

    //cities returned from the above call are sorted according to 
    //the ascending order of the city names and 
    //the descending order of the size of reachableCities starting from those cities
    
    asserts(cities.at(0).getCity() == "HT", "First city should be HT");
    //Reachable cities from HT are [HT, NH, SF, JL, OD, SD, DL]
    asserts(cities.at(0).getReachableCities().size() == 7, "Train starting from city HT can reach 7 cities"); 
    
    asserts(cities.at(1).getCity() == "NH", "Second city should be NH");
    //Reachable cities from NH are [NH, SF, HT, JL, OD, SD, DL]
    asserts(cities.at(1).getReachableCities().size() == 7, "Train starting from city NH can reach 7 cities");
    
    asserts(cities.at(2).getCity() == "SF", "Third city should be SF");
    //Reachable cities from SF are [SF, HT, NH, JL, OD, SD, DL]
    asserts(cities.at(2).getReachableCities().size() == 7, "Train starting from city SF can reach 7 cities");
    
    asserts(cities.at(3).getCity() == "SJ", "Fourth city should be SJ");
    //Reachable cities from SJ are [SJ, SK, IV, DL, LA, BV, BU]
    asserts(cities.at(3).getReachableCities().size() == 7, "Train starting from city SJ can reach 7 cities");

    asserts(cities.at(4).getCity() == "SK", "Fifth city should be SK");
    //Reachable cities from SK are [SK, IV, DL, LA, BV, BU]
    asserts(cities.at(4).getReachableCities().size() == 6, "Train starting from city SK can reach 6 cities");
    
    asserts(cities.at(5).getCity() == "JL", "Sixth city should be JL");
    //Reachable cities from JL are [JL, OD, SD, DL]
    asserts(cities.at(5).getReachableCities().size() == 4, "Train starting from city JL can reach 4 cities");
    
    asserts(cities.at(6).getCity() == "BV", "Seventh city should be BV");
    //Reachable cities from BV are [BV, LA, BU]
    asserts(cities.at(6).getReachableCities().size() == 3, "Train starting from city BV can reach 3 cities");
        
    asserts(cities.at(7).getCity() == "LA", "Eighth city should be LA");
    //Reachable cities from LA are [LA, BV, BU]
    asserts(cities.at(7).getReachableCities().size() == 3, "Train starting from city LA can reach 3 cities");

    asserts(cities.at(8).getCity() == "OD", "Ninth city should be OD");
    //Reachable cities from OD are [OD, SD, DL]
    asserts(cities.at(8).getReachableCities().size() == 3, "Train starting from city OD can reach 3 cities");

    asserts(cities.at(11).getCity() == "BU", "Twelfth city should be BU");
    //Reachable cities from BU are [BU]
    asserts(cities.at(11).getReachableCities().size() == 1, "Train starting from city BU can reach 1 city");
    cout << endl;


    //-------------> next test
    
    
    // Graph with no connections
    vector<string> cities_3 {"SD", "LA", "SK", "IV"};
    vector<pair<string, string>> trainRoutes_3;
    
    cities = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_3, trainRoutes_3);
    
    asserts(cities.at(0).getCity() == "IV", "First city should be IV");
    //Reachable cities from IV are [IV]
    asserts(cities.at(0).getReachableCities().size() == 1, "Train starting from city IV can reach 1 city");
    
    asserts(cities.at(1).getCity() == "LA", "Second city should be LA");
    //Reachable cities from LA are [LA]
    asserts(cities.at(1).getReachableCities().size() == 1, "Train starting from city LA can reach 1 city");
    
    asserts(cities.at(2).getCity() == "SD", "Third city should be SD");
    //Reachable cities from SD are [SD]
    asserts(cities.at(2).getReachableCities().size() == 1, "Train starting from city SD can reach 1 city");
    
    asserts(cities.at(3).getCity() == "SK", "Fourth city should be SK");
    //Reachable cities from SK are [SK]
    asserts(cities.at(3).getReachableCities().size() == 1, "Train starting from city SK can reach 1 city");    
    cout << endl;
    
    
    
    //-------------> next test
    
    
    
    // Disconnected Graph
    vector<string> cities_4 {"SD", "LA", "SK", "IV", "SF"};
    vector<pair<string, string>> trainRoutes_4;
    
    /*
    SD--->LA  SK--->IV--->SF
               \          |
                <---------            
    */
    
    trainRoutes_4.emplace_back("SD", "LA");
    trainRoutes_4.emplace_back("SK", "IV");
    trainRoutes_4.emplace_back("IV", "SF");
    trainRoutes_4.emplace_back("SF", "SK");
    
    cities = ConnectedCities::citiesSortedByNumOf_Its_ReachableCities_byTrain(cities_4, trainRoutes_4);
    
    asserts(cities.at(0).getCity() == "IV", "First city should be IV");
    //Reachable cities from IV are [IV, SF, SK]
    asserts(cities.at(0).getReachableCities().size() == 3, "Train starting from city IV can reach 3 cities");
    
    asserts(cities.at(1).getCity() == "SF", "Second city should be SF");
    //Reachable cities from SF are [SF, SK, IV]
    asserts(cities.at(1).getReachableCities().size() == 3, "Train starting from city SF can reach 3 cities");
    
    asserts(cities.at(2).getCity() == "SK", "Third city should be SK");
    //Reachable cities from SK are [SK, IV, SF]
    asserts(cities.at(2).getReachableCities().size() == 3, "Train starting from city SK can reach 3 cities");
    
    asserts(cities.at(3).getCity() == "SD", "Fourth city should be SD");
    //Reachable cities from SD are [SD, LA]
    asserts(cities.at(3).getReachableCities().size() == 2, "Train starting from city SD can reach 2 cities");
    
    asserts(cities.at(4).getCity() == "LA", "Fifth city should be LA");
    //Reachable cities from LA are [LA]
    asserts(cities.at(4).getReachableCities().size() == 1, "Train starting from city LA can reach 1 city");
    

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}