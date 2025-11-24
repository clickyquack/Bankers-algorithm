#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

// Function to read data from input file
// And store it in the relevant data structures
void readInput(vector<int>& available, vector<vector<int>>& allocation, 
               vector<vector<int>>& max) {
    ifstream file("input.txt");
    
    // Read Available table
    available.resize(NUM_RESOURCES);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        file >> available[i];
    }
    
    // Skip blank line
    string line;
    getline(file, line); getline(file, line);
    
    // Read Allocation table
    allocation.resize(NUM_PROCESSES, vector<int>(NUM_RESOURCES));
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            file >> allocation[i][j];
        }
    }
    
    // Skip blank line
    getline(file, line); getline(file, line);
    
    // Read Max table
    max.resize(NUM_PROCESSES, vector<int>(NUM_RESOURCES));
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            file >> max[i][j];
        }
    }
}

// Apply banker's algorithm on given data
// If system in safe state, return true and store safe sequence
// Otherwise, return false
bool bankersAlgorithm(const vector<int>& available,
                      const vector<vector<int>>& allocation,
                      const vector<vector<int>>& need,
                      vector<int>& safeSequence) {
    vector<int> work = available;
    vector<bool> finish(NUM_PROCESSES, false);
    safeSequence.clear();
    
    bool found;
    int finished = 0;
    
    // Try to find a safe sequence
    while (finished < NUM_PROCESSES) {
        found = false;
        
        for (int i = 0; i < NUM_PROCESSES; i++) {
            // The process can be satisfied,
            // unless it needs more instances of a resource
            // than what is available
            bool canSatisfy = true;
            for (int j = 0; j < NUM_RESOURCES; j++) {
                if (need[i][j] > work[j]) {
                    canSatisfy = false;
                }
            }

            // If process i not finished and can be satisfied
            if (!finish[i] && canSatisfy) {
                // "Finish" process i
                // Its resources are added to Work
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
                // Place process i in the safe sequence
                safeSequence.push_back(i);
                found = true;
                finished++;
                break;
            }
        }
        
        // If no process can be satisfied, system is in unsafe state
        if (!found) {
            return false;
        }
    }
    
    return true;
}

int main() {
    vector<int> available;
    vector<vector<int>> allocation;
    vector<vector<int>> max;
    vector<vector<int>> need;
    vector<int> safeSequence;
    
    // Read input from file
    readInput(available, allocation, max);
    
    // Calculate Need matrix
    need.resize(NUM_PROCESSES, vector<int>(NUM_RESOURCES));
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    // Run Banker's Algorithm
    bool isSafe = bankersAlgorithm(available, allocation, need, safeSequence);
    
    // Output results
    if (isSafe) {
        cout << "The system is in a safe state." << endl;
        cout << "Safe sequence: ";
        for (size_t i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i];
            if (i < safeSequence.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "The system is not in a safe state." << endl;
    }
}