#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "Location.h"  // Assuming your Location class is defined in "Location.h"
#include <vector>
#include <algorithm>
#include "DistanceCalculation.h"


std::map<std::string, Location> cities;

void readFile(std::string file)
{
    std::ifstream inputFile(file);  // Assuming the input file is named "data.txt"

    std::string name;
    double latitude;
    double longitude;

    while (std::getline(inputFile, name)) {
        std::string locationLine;

        // Read latitude and longitude line
        if (!std::getline(inputFile, locationLine)) {
            break;  // Exit the loop if there are no more lines to read
        }

        // Extract latitude and longitude from the location line
        std::stringstream locationStream(locationLine);
        locationStream >> latitude;
        locationStream.ignore(3);  // Ignore the ' - ' separator (space dash space)
        locationStream >> longitude;

        // Create a Location object
        Location location;
        location.setRow(latitude);
        location.setCol(longitude);

        // Add the location to the multimap with the city name as the key
        cities.emplace(name, location);
    }

    // Print data to the screen
    //for (const auto& city : cities) 
    //    std::cout << "City: " << city.first << ", Location: " << city.second << "\n";
}

std::vector<Location> searchCitiesWithinRadius(const std::string& cityName, double radius, int normChoice)
{
    auto iter = cities.find(cityName);

    // Check if the city exists in the multimap
    if (iter == cities.end()) {
        std::cout << "City not found." << std::endl;
        return {};
    }

    // Get the coordinates of the given city
    Location givenCityLocation = iter->second;

    // Calculate the boundaries of the square based on the x and y coordinates
    double minX = givenCityLocation.getCol() - radius;
    double maxX = givenCityLocation.getCol() + radius;
    double minY = givenCityLocation.getRow() - radius;
    double maxY = givenCityLocation.getRow() + radius;

    std::vector<Location> citiesWithinSquare;

    std::transform(cities.begin(), cities.end(), std::back_inserter(citiesWithinSquare), [&](const auto& pair) {
        const Location& cityLocation = pair.second;
        return cityLocation;
        });

    citiesWithinSquare.erase(std::remove_if(citiesWithinSquare.begin(), citiesWithinSquare.end(), [&](const Location& cityLocation) {
        return cityLocation.getCol() < minX || cityLocation.getCol() > maxX ||
            cityLocation.getRow() < minY || cityLocation.getRow() > maxY;
        }), citiesWithinSquare.end());

    citiesWithinSquare.erase(std::remove_if(citiesWithinSquare.begin(), citiesWithinSquare.end(), [&](const Location& cityLocation) {
        return cityLocation.getCol() < minX || cityLocation.getCol() > maxX ||
            cityLocation.getRow() < minY || cityLocation.getRow() > maxY ||
            cityLocation == givenCityLocation;  // Exclude the given city
        }), citiesWithinSquare.end());

    // Create an instance of DistanceCalculation
    DistanceCalculation distanceCalculation;

    // Set the distance function based on the normChoice
    distanceCalculation.setDistanceFunction(normChoice);

    // Sort the cities within the square based on distance from the given city
    std::sort(citiesWithinSquare.begin(), citiesWithinSquare.end(), [&](const Location& loc1, const Location& loc2) {
        return distanceCalculation.calculateDistance(givenCityLocation, loc1) <
            distanceCalculation.calculateDistance(givenCityLocation, loc2);
        });

    // Create a vector to store the cities within the radius
    std::vector<Location> citiesWithinRadius;

    // Copy the cities within the radius to the vector using std::copy_if algorithm
    std::copy_if(citiesWithinSquare.begin(), citiesWithinSquare.end(), std::back_inserter(citiesWithinRadius), [&](const Location& cityLocation) {
        return distanceCalculation.calculateDistance(givenCityLocation, cityLocation) <= radius;
        });

    return citiesWithinRadius;
}


int main()
{
    std::string city;
    double radius;
    int norm;

    readFile("data.txt");

    while (true) {
        std::cout << "Enter city name (press Enter to exit): " << std::endl;
        std::getline(std::cin, city);

        // If the user pressed Enter without entering a city name, exit the program
        if (city.empty())
            break;

        std::cout << "Enter radius: " << std::endl;
        std::cin >> radius;

        std::cout << "Enter norm (0-2: 0 for euclideanDistance, 1 for chebyshevDistance, 2 for manhattanDistance): " << std::endl;
        std::cin >> norm;

        std::cin.ignore(); // Ignore the trailing newline character

        // Find the range of cities with the same name in the multimap
        auto range = cities.equal_range(city);

        // Check if the city exists in the multimap
        if (range.first == cities.end()) {
            std::cout << "City not found." << std::endl;
            continue;
        }

        // Get the coordinates of the given city
        Location givenCityLocation(range.first->second);

        std::vector<Location> citiesWithinRadius = searchCitiesWithinRadius(city, radius, norm);

        // Create an instance of DistanceCalculation
        DistanceCalculation distanceCalculation;
        distanceCalculation.setDistanceFunction(norm);

        // Sort the cities within the radius based on distance from the given city
        std::sort(citiesWithinRadius.begin(), citiesWithinRadius.end(), [&](const Location& loc1, const Location& loc2) {
            return distanceCalculation.calculateDistance(givenCityLocation, loc1) <
                distanceCalculation.calculateDistance(givenCityLocation, loc2);
            });

        // Print the cities within the radius
        std::cout << "Cities within the radius for " << city << ": " << std::endl;
        for (const auto& location : citiesWithinRadius) {
            std::cout << "City: " << city << ", Distance: " << distanceCalculation.calculateDistance(givenCityLocation, location) << ", Location: " << location << "\n";
        }
        std::cout << std::endl;
    }

    return 0;
}





//int main() 
//{
//
//    std::string city;
//    double radius;
//    int norm;
//
//    std::cout << "Enter city name: " << std::endl;
//    std::cin >> city;
//    std::cout << "Enter radius: " << std::endl;
//    std::cin >> radius;
//    std::cout << "Enter norm (0-2: 0 for euclideanDistance, 1 for chebyshevDistance, 2 for manhattanDistance): " << std::endl;
//    std::cin >> norm;
//
//    readFile("data.txt");
//
//    return 0;
//}
