#include <iostream>
#include <queue>
#include <stack>
#include <map>          // links vehicle id with parking space , easy search and removal
#include <iomanip>      // formatting , ex: leading zeros
#include <limits>       // input validation , ex: clearing cin buffer

using namespace std;

class ParkingLot {
private:
    queue<string> availableSpots;   // queue for new spots (FIFO)
    stack<string> freedSpots;       // stack for freed spots (LIFO)
    map<int, string> parkedCars;    // mapping a vehicle id to a parking spot, BST
    int userIDCounter;

public:
    // constructor to initialize the amount of parking spots (A0 - J9, 100 in total)
    ParkingLot() {
        userIDCounter = 1;
        for (char row = 'A'; row <= 'J'; row++) {
            for (int num = 0; num <= 9; num++) {
                availableSpots.push(string(1, row) + to_string(num));
            }
        }
    }

    // assigns a parking spot to a new vehicle
    void parkVehicle() {
        if (availableSpots.empty() && freedSpots.empty()) {
            cout << "Sorry, no parking spots available.\n";
            return;
        }

        int assignedID = userIDCounter++;
        string assignedSpot;

        if (!freedSpots.empty()) {
            assignedSpot = freedSpots.top();
            freedSpots.pop();
        } else {
            assignedSpot = availableSpots.front();
            availableSpots.pop();
        }

        parkedCars[assignedID] = assignedSpot;

        cout << "Vehicle ID: "
             << setw(3) << setfill('0') << assignedID
             << " parked at " << assignedSpot << endl;
        cout << "Please remember your ID (" << setw(3) << setfill('0') << assignedID
             << ") for removing your car later!\n";
    }

    // removes a vehicle using its ID
    void removeVehicle(int userID) {
        if (parkedCars.find(userID) != parkedCars.end()) {
            string freedSpot = parkedCars[userID];
            parkedCars.erase(userID);
            freedSpots.push(freedSpot);

            cout << "Vehicle with ID " << setw(3) << setfill('0') << userID
                 << " has left the parking lot. Spot " << freedSpot
                 << " is now available.\n";
        } else {
            cout << "Invalid ID! No vehicle found with ID " << setw(3) << setfill('0') << userID << ".\n";
        }
    }

    // shows all currently parked vehicles
    void displayParkedVehicles() {
        cout << "\nCurrent Parked Vehicles:\n";
        if (parkedCars.empty()) {
            cout << "No vehicles are currently parked.\n";
            return;
        }

        for (const auto& entry : parkedCars) {
            cout << "ID: " << setw(3) << setfill('0') << entry.first
                 << ", Parking Spot: " << entry.second << endl;
        }
    }

    // shows the total, used, and available parking spots
    void displayAvailability() {
        int totalAvailable = availableSpots.size() + freedSpots.size();
        int totalUsed = parkedCars.size();
        int totalSpots = totalAvailable + totalUsed;

        cout << "\n--- Parking Lot Status ---\n";
        cout << "Total Spots:   " << totalSpots << endl;
        cout << "Occupied:      " << totalUsed << endl;
        cout << "Available:     " << totalAvailable << endl;
    }
};

int main() {
    ParkingLot lot;
    int choice, userID;


    // interactive menu for users
    do {
        cout << "\n<> Parking Management System <>\n";
        cout << "1. Park a Vehicle\n"
                "2. Remove a Vehicle by ID\n"
                "3. Display Parked Vehicles\n"
                "4. Display Availability\n"
                "5. Exit\n";
        cout << "Enter choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 5: ";
        }

        switch (choice) {
            case 1:
                lot.parkVehicle();
                break;
            case 2:
                cout << "Enter your parking ID: ";
                while (!(cin >> userID)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a valid ID: ";
                }
                lot.removeVehicle(userID);
                break;
            case 3:
                lot.displayParkedVehicles();
                break;
            case 4:
                lot.displayAvailability();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
