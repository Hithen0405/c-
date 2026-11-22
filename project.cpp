
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

const float MAX_GRID_LOAD = 80.0;

// ================= VEHICLE CLASS =================

class Vehicle
{
public:
    int id, priority;
    string name;
    float batteryCapacity, batteryLevel, requiredEnergy;

    Vehicle(int i, string n, float capacity,
            float level, int p)
    {

        id = i;
        name = n;
        batteryCapacity = capacity;
        batteryLevel = level;
        priority = p;

        requiredEnergy = capacity * (100 - level) / 100;
    }

    void display() const
    {
        cout << left << setw(10) << id
             << setw(18) << name
             << setw(12) << batteryLevel
             << setw(12) << requiredEnergy
             << priority << endl;
    }
};

// ================= CHARGING STATION CLASS =================

class ChargingStation
{
public:
    int id;
    float power;
    int vehicleID;
    bool available;

    ChargingStation(int i, float p)
    {
        id = i;
        power = p;
        vehicleID = -1;
        available = true;
    }
};

// ================= EV SCHEDULER CLASS =================

class EVScheduler
{
private:
    vector<Vehicle> vehicles;
    queue<Vehicle> waitingQueue;
    map<int, ChargingStation> stations;

public:
    // Initialize charging stations
    EVScheduler()
    {
        stations.emplace(1, ChargingStation(1, 22));
        stations.emplace(2, ChargingStation(2, 30));
        stations.emplace(3, ChargingStation(3, 50));
    }

    // Register vehicle
    void addVehicle()
    {
        int id, priority;
        float capacity, level;
        string name;

        cout << "\nEnter Vehicle ID: ";
        if (!(cin >> id))
        {
            cout << "Invalid ID!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        for (const auto &v : vehicles)
        {
            if (v.id == id)
            {
                cout << "Vehicle already registered!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Vehicle Name: ";
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty!\n";
            return;
        }

        cout << "Enter Battery Capacity (kWh): ";
        if (!(cin >> capacity))
        {
            cout << "Invalid capacity!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter Current Battery Level (%): ";
        if (!(cin >> level))
        {
            cout << "Invalid battery level!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cout << "Enter Priority (1-5): ";
        if (!(cin >> priority))
        {
            cout << "Invalid priority!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        if (capacity <= 0 || level < 0 || level >= 100 ||
            priority < 1 || priority > 5)
        {
            cout << "Invalid vehicle details!\n";
            return;
        }

        Vehicle v(id, name, capacity, level, priority);

        vehicles.push_back(v);
        waitingQueue.push(v);

        cout << "\nVehicle registered successfully!\n";
        cout << "Energy required: "
             << fixed << setprecision(2)
             << v.requiredEnergy << " kWh\n";
    }

    // Display waiting vehicles
    void displayQueue()
    {
        if (waitingQueue.empty())
        {
            cout << "\nNo vehicles waiting!\n";
            return;
        }

        queue<Vehicle> temp = waitingQueue;

        cout << "\nID        Name              Battery     Energy      Priority\n";

        while (!temp.empty())
        {
            temp.front().display();
            temp.pop();
        }
    }

    // Priority-based queue optimization
    void optimizeQueue()
    {
        vector<Vehicle> temp;

        while (!waitingQueue.empty())
        {
            temp.push_back(waitingQueue.front());
            waitingQueue.pop();
        }

        stable_sort(temp.begin(), temp.end(),
                    [](const Vehicle &a, const Vehicle &b)
                    {
                        if (a.priority != b.priority)
                            return a.priority > b.priority;

                        return a.batteryLevel < b.batteryLevel;
                    });

        for (const auto &v : temp)
            waitingQueue.push(v);

        cout << "\nQueue optimized successfully!\n";
    }

    // Calculate current electricity load
    float getCurrentLoad()
    {
        float load = 0;

        for (const auto &s : stations)
        {
            if (!s.second.available)
                load += s.second.power;
        }

        return load;
    }

    // Smart station allocation
    void scheduleVehicle()
    {
        if (waitingQueue.empty())
        {
            cout << "\nNo vehicles waiting!\n";
            return;
        }

        float currentLoad = getCurrentLoad();

        auto bestStation = stations.end();

        // Select the highest-power available charger
        // that does not exceed the grid limit.

        for (auto it = stations.begin();
             it != stations.end(); ++it)
        {

            if (it->second.available &&
                currentLoad + it->second.power <= MAX_GRID_LOAD)
            {

                if (bestStation == stations.end() ||
                    it->second.power > bestStation->second.power)
                {
                    bestStation = it;
                }
            }
        }

        if (bestStation == stations.end())
        {
            cout << "\nNo suitable charging station available!\n";
            cout << "Current grid load: "
                 << currentLoad << " kW\n";
            return;
        }

        Vehicle v = waitingQueue.front();
        waitingQueue.pop();

        bestStation->second.available = false;
        bestStation->second.vehicleID = v.id;

        float chargingTime =
            (v.requiredEnergy / bestStation->second.power) * 60;

        cout << "\n===== SMART CHARGING ALLOCATION =====\n";

        cout << "Vehicle: " << v.name << endl;
        cout << "Vehicle ID: " << v.id << endl;
        cout << "Station: " << bestStation->first << endl;
        cout << "Charger Power: "
             << bestStation->second.power << " kW\n";

        cout << "Energy Required: "
             << v.requiredEnergy << " kWh\n";

        cout << fixed << setprecision(2);
        cout << "Estimated Charging Time: "
             << chargingTime << " minutes\n";

        cout << "Total Grid Load: "
             << currentLoad + bestStation->second.power
             << " / " << MAX_GRID_LOAD << " kW\n";

        cout << "Status: Charging Started\n";
    }

    // Complete charging session
    void completeCharging()
    {
        int id;

        cout << "\nEnter Station ID: ";

        if (!(cin >> id))
        {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        auto it = stations.find(id);

        if (it == stations.end())
        {
            cout << "Invalid station ID!\n";
            return;
        }

        if (it->second.available)
        {
            cout << "Station is already available!\n";
            return;
        }

        int vehicleID = it->second.vehicleID;

        ofstream file("charging_history.txt", ios::app);

        if (!file)
        {
            cout << "Unable to save history!\n";
            return;
        }

        file << "Vehicle ID: " << vehicleID
             << " | Station ID: " << id
             << " | Energy session completed\n";

        file.close();

        it->second.available = true;
        it->second.vehicleID = -1;

        cout << "\nCharging completed successfully!\n";
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Station " << id << " is now available.\n";
        cout << "Updated Grid Load: "
             << getCurrentLoad() << " kW\n";
    }

    // Display station information
    void displayStations()
    {
        cout << "\n===== CHARGING STATIONS =====\n";

        for (const auto &s : stations)
        {
            cout << "Station " << s.first
                 << " | Power: " << s.second.power << " kW"
                 << " | Status: ";

            if (s.second.available)
                cout << "Available\n";
            else
                cout << "Occupied by Vehicle "
                     << s.second.vehicleID << endl;
        }

        cout << "\nCurrent Grid Load: "
             << getCurrentLoad() << " kW";

        cout << "\nMaximum Grid Load: "
             << MAX_GRID_LOAD << " kW\n";
    }

    // View charging history
    void displayHistory()
    {
        ifstream file("charging_history.txt");
        string line;

        cout << "\n===== CHARGING HISTORY =====\n";

        if (!file)
        {
            cout << "No history available.\n";
            return;
        }

        while (getline(file, line))
            cout << line << endl;

        file.close();
    }

    // Main menu
    void menu()
    {
        int choice;

        do
        {
            cout << "\n====================================\n";
            cout << " SMART EV CHARGING MANAGEMENT SYSTEM\n";
            cout << "====================================\n";

            cout << "1. Register Vehicle\n";
            cout << "2. Display Waiting Queue\n";
            cout << "3. Optimize Queue\n";
            cout << "4. Smart Charging Allocation\n";
            cout << "5. Complete Charging\n";
            cout << "6. Display Station and Load Status\n";
            cout << "7. View Charging History\n";
            cout << "8. Exit\n";

            cout << "------------------------------------\n";
            cout << "Enter Choice: ";

            if (!(cin >> choice))
            {
                cout << "Invalid input! Enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (choice)
            {
            case 1:
                addVehicle();
                break;

            case 2:
                displayQueue();
                break;

            case 3:
                optimizeQueue();
                break;

            case 4:
                scheduleVehicle();
                break;

            case 5:
                completeCharging();
                break;

            case 6:
                displayStations();
                break;

            case 7:
                displayHistory();
                break;

            case 8:
                cout << "\nThank you for using Smart EV System!\n";
                break;

            default:
                cout << "Invalid choice!\n";
            }

        } while (choice != 8);
    }
};

// ================= MAIN FUNCTION =================

int main()
{
    EVScheduler ev;
    ev.menu();

    return 0;
}
