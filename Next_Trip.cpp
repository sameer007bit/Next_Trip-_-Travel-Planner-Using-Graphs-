#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Transport {
public:
    string name;
    int time;
    int cost;
    int distance;

    Transport(string n, int t, int c, int d) {
        name = n;
        time = t;
        cost = c;
        distance = d;
    }
};

int main() {
    vector<string> cities = {
        "Dhaka", "Chittagong", "Rajshahi", "Sylhet", "Khulna",
        "Barisal", "Rangpur", "Comilla", "Mymensingh", "Faridpur"
    };

    vector<vector<Transport>> transports = {
        { {"Bus", 5, 1300, 250}, {"Train", 4, 750, 250}, {"Plane", 1, 7500, 250} }, // Dhaka
        { {"Bus", 5, 1500, 300}, {"Train", 4, 900, 300}, {"Plane", 1, 8000, 300} }, // Chittagong
        { {"Bus", 6, 1200, 350}, {"Train", 5, 1000, 350}, {"Plane", 1, 9000, 350} }, // Rajshahi
        { {"Bus", 7, 1400, 400}, {"Train", 6, 1100, 400}, {"Plane", 1, 8500, 400} }, // Sylhet
        { {"Bus", 6, 1300, 300}, {"Train", 5, 950, 300}, {"Plane", 1, 7600, 300} }, // Khulna
        { {"Bus", 6, 1400, 320}, {"Train", 5, 1100, 320}, {"Plane", 1, 7200, 320} }, // Barisal
        { {"Bus", 7, 1500, 370}, {"Train", 6, 1200, 370}, {"Plane", 1, 7800, 370} }, // Rangpur
        { {"Bus", 5, 1250, 280}, {"Train", 4, 850, 280}, {"Plane", 1, 7000, 280} }, // Comilla
        { {"Bus", 4, 1000, 200}, {"Train", 3, 600, 200} },  // Mymensingh (No Airport)
        { {"Bus", 4, 1100, 210}, {"Train", 3, 650, 210} }   // Faridpur (No Airport)
    };

    vector<string> noAirportCities = { "Mymensingh", "Faridpur" };

    cout << "Welcome to Next_Trip!\n\n";

    // Select starting city
    cout << "Choose your starting city:\n";
    for (size_t i = 0; i < cities.size(); i++) {
        cout << (i + 1) << ". " << cities[i] << "   ";
    }
    cout << "\nEnter the number of the starting city (1-10): ";
    int startCityIndex;
    cin >> startCityIndex;
    startCityIndex--;

    // Select destination city
    cout << "\nChoose your destination city:\n";
    for (size_t i = 0; i < cities.size(); i++) {
        cout << (i + 1) << ". " << cities[i] << "   ";
    }
    cout << "\nEnter the number of the destination city (1-10): ";
    int destinationCityIndex;
    cin >> destinationCityIndex;
    destinationCityIndex--;

    if (startCityIndex == destinationCityIndex) {
        cout << "\nYou are already in " << cities[startCityIndex] << ". Please choose a different destination.\n";
        return 0;
    }

    // Airport availability check
    if (count(noAirportCities.begin(), noAirportCities.end(), cities[startCityIndex]) > 0) {
        cout << "\n" << cities[startCityIndex] << " has NO airport. You cannot take a plane from here!\n";
    }
    if (count(noAirportCities.begin(), noAirportCities.end(), cities[destinationCityIndex]) > 0) {
        cout << "\n" << cities[destinationCityIndex] << " has NO airport. You cannot fly there!\n";
    }

    // Filter transport options if no airport is available
    vector<Transport> availableTransports = transports[startCityIndex];
    if (count(noAirportCities.begin(), noAirportCities.end(), cities[startCityIndex]) > 0 ||
        count(noAirportCities.begin(), noAirportCities.end(), cities[destinationCityIndex]) > 0) {
        availableTransports.erase(
            remove_if(availableTransports.begin(), availableTransports.end(),
                      [](const Transport& t) { return t.name == "Plane"; }),
            availableTransports.end()
        );
    }

    // Available transport options
    cout << "\nAvailable transport options from " << cities[startCityIndex] << " to " << cities[destinationCityIndex] << ":\n";
    for (size_t i = 0; i < availableTransports.size(); i++) {
        cout << (i + 1) << ". " << availableTransports[i].name
             << " - Time: " << availableTransports[i].time << " hours, "
             << "Cost: " << availableTransports[i].cost << " BDT, "
             << "Distance: " << availableTransports[i].distance << " km\n";
    }

    // Select preference
    cout << "\nChoose your preference for the optimal route:\n";
    cout << "1. Shortest Time\n";
    cout << "2. Least Cost\n";
    cout << "3. Balanced Cost & Time\n";
    cout << "Enter your choice (1-3): ";
    int preference;
    cin >> preference;

    // Finding the optimal transport
    Transport optimalTransport = availableTransports[0];

    if (preference == 1) {  // Shortest time
        for (Transport transport : availableTransports) {
            if (transport.time < optimalTransport.time) {
                optimalTransport = transport;
            }
        }
    } else if (preference == 2) {  // Least cost
        for (Transport transport : availableTransports) {
            if (transport.cost < optimalTransport.cost) {
                optimalTransport = transport;
            }
        }
    } else if (preference == 3) {  // Balanced (Average) Cost & Time
        int avgTime = 0, avgCost = 0;
        for (Transport transport : availableTransports) {
            avgTime += transport.time;
            avgCost += transport.cost;
        }
        avgTime /= availableTransports.size();
        avgCost /= availableTransports.size();

        for (Transport transport : availableTransports) {
            if (abs(transport.time - avgTime) + abs(transport.cost - avgCost) <
                abs(optimalTransport.time - avgTime) + abs(optimalTransport.cost - avgCost)) {
                optimalTransport = transport;
            }
        }
    }

    // Display optimal route
    cout << "\nOptimal Route from " << cities[startCityIndex] << " to " << cities[destinationCityIndex] << "\n";
    cout << "Transport: " << optimalTransport.name << "\n";
    cout << "Distance: " << optimalTransport.distance << " km\n";
    cout << "Time: " << optimalTransport.time << " hours\n";
    cout << "Cost: " << optimalTransport.cost << " BDT\n";

    return 0;
}
