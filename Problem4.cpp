#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;


// Process structure to store all process info
struct Process {
    int id, at, bt, rem, ct, tat, wt;
    bool inq; // whether process is currently in queue
};

// Round Robin Scheduler class
class RoundRobinScheduler {
    int quantum, current_time, completed, n, running;
    vector<Process> processes;
    queue<int> readyQueue;

    // Print current state of ready queue
    void printQueue() {
        cout << "[ ";
        queue<int> temp = readyQueue;
        bool first = true;

        while (!temp.empty()) {
            int idx = temp.front();
            temp.pop();

            if (!first) cout << ", ";
            first = false;

            cout << "P" << processes[idx].id;
        }

        cout << " ]" << endl;
    }

    // Add processes that have arrived at current time
    void addNewlyArrived() {
        for (int i = 0; i < n; i++) {
            if (processes[i].rem > 0 &&
                processes[i].at <= current_time &&
                !processes[i].inq &&
                processes[i].id != running) {

                readyQueue.push(i);
                processes[i].inq = true;
            }
        }
    }

public:
    // Constructor: initialize processes
    RoundRobinScheduler(int q, const vector<pair<int,int>>& data)
        : quantum(q), current_time(0), completed(0), running(-1) {

        n = data.size();

        for (int i = 0; i < n; i++) {
            Process p;

            p.id = i + 1;
            p.at = data[i].first;
            p.bt = data[i].second;
            p.rem = p.bt;

            p.ct = 0;
            p.tat = 0;
            p.wt = 0;

            p.inq = false;

            processes.push_back(p);
        }
    }

    // Main simulation function
    void simulate() {

        cout << "Queue updates:" << endl;

        while (completed < n) {

            // Add processes that have arrived
            addNewlyArrived();

            // If no process is ready, jump time to next arrival
            if (readyQueue.empty()) {

                int next_arrival = 1e9;

                for (int i = 0; i < n; i++) {
                    if (processes[i].rem > 0) {
                        next_arrival = min(next_arrival, processes[i].at);
                    }
                }

                if (next_arrival > current_time) {
                    if (current_time > 0 || completed > 0)
                        cout << "[ Empty ]" << endl;

                    current_time = next_arrival;
                }

                addNewlyArrived();
                continue;
            }

            // Print current queue state
            printQueue();

            // Get next process from queue
            int idx = readyQueue.front();
            readyQueue.pop();

            processes[idx].inq = false;
            running = processes[idx].id;

            // Execute process for quantum or remaining time
            int exec_time = min(quantum, processes[idx].rem);
            processes[idx].rem -= exec_time;
            current_time += exec_time;

            // Check for new arrivals during execution
            addNewlyArrived();

            // If process finished execution
            if (processes[idx].rem == 0) {

                completed++;

                processes[idx].ct = current_time;
                processes[idx].tat = processes[idx].ct - processes[idx].at;
                processes[idx].wt = processes[idx].tat - processes[idx].bt;

                running = -1;

                if (readyQueue.empty() && completed < n)
                    cout << "[ Empty ]" << endl;
            }

            // If process still not finished, push it back to queue
            else {
                readyQueue.push(idx);
                processes[idx].inq = true;
                running = -1;
            }
        }

        cout << "[ Empty ]" << endl << endl;

        // Print final results table
        cout << "Process\tCompletion\tTurnaround\tWaiting\n";

        float total_waiting = 0;

        for (int i = 0; i < n; i++) {
            cout << "P" << processes[i].id << "\t\t"
                 << processes[i].ct << "\t\t"
                 << processes[i].tat << "\t\t"
                 << processes[i].wt << endl;

            total_waiting += processes[i].wt;
        }

        float avg = total_waiting / n;

        cout << fixed << setprecision(3);
        cout << "Average Waiting Time: " << avg << endl;
    }
};

// Main function: input + run scheduler
int main() {

    int quantum, n;

    cout << "Time Quantum: ";
    cin >> quantum;

    cout << "Number of Processes: ";
    cin >> n;

    vector<pair<int,int>> data;

    for (int i = 0; i < n; i++) {

        int at, bt;

        cout << "Arrival Time, Needed Time P" << i+1 << ": ";
        cin >> at >> bt;

        data.push_back({at, bt});
    }

    RoundRobinScheduler rr(quantum, data);
    rr.simulate();

    return 0;
}
