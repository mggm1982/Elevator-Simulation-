#include <iostream>
#include <set>
using namespace std;

class Elevator {
private:
    int currentFloor;
    int totalFloors;
    set<int> upRequests;   // all requested floors above current floor
    set<int, greater<int>> downRequests; // all requested floors below current floor

public:
    Elevator(int floors) {
        currentFloor = 0;    // start at ground floor
        totalFloors = floors;
    }

    void requestFloor(int floor) {
        if (floor < 0 || floor >= totalFloors) {
            cout << "Invalid floor request!\n";
            return;
        }

        if (floor > currentFloor) {
            upRequests.insert(floor);
            cout << "Request accepted for floor " << floor << " (UP)\n";
        } else if (floor < currentFloor) {
            downRequests.insert(floor);
            cout << "Request accepted for floor " << floor << " (DOWN)\n";
        } else {
            cout << "Elevator already at floor " << floor << endl;
        }
    }

    void move() {
        // First serve all upward requests
        while (!upRequests.empty()) {
            int target = *upRequests.begin(); // smallest higher floor
            upRequests.erase(upRequests.begin());

            cout << "\nElevator moving UP from " << currentFloor << " to " << target << endl;
            while (currentFloor < target) {
                currentFloor++;
                cout << "  At Floor " << currentFloor << endl;
            }
            cout << " Reached Floor " << currentFloor << endl;
        }

        // Then serve all downward requests
        while (!downRequests.empty()) {
            int target = *downRequests.begin(); // largest lower floor
            downRequests.erase(downRequests.begin());

            cout << "\nElevator moving DOWN from " << currentFloor << " to " << target << endl;
            while (currentFloor > target) {
                currentFloor--;
                cout << "  At Floor " << currentFloor << endl;
            }
            cout << " Reached Floor " << currentFloor << endl;
        }
    }
};

int main() {
    int totalFloors = 10; // building has 10 floors (0–9)
    Elevator lift(totalFloors);

    int requests;
    cout << "Enter number of requests: ";
    cin >> requests;

    cout << "Enter requested floors: ";
    for (int i = 0; i < requests; i++) {
        int f;
        cin >> f;
        lift.requestFloor(f);
    }

    lift.move();
    return 0;
}