#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;


struct Process {
    int id, at, bt, rem, ct, tat, wt;
    bool inq;
};

class RoundRobinScheduler {
    int quantum, current_time, completed, n, running;
    vector<Process> processes;
    queue<int> readyQueue;

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

    void simulate() {
        cout << "Queue updates:" << endl;

        while (completed < n) {
            addNewlyArrived();

            if (readyQueue.empty()) {
                int next_arrival = 1e9;
                for (int i = 0; i < n; i++) {
                    if (processes[i].rem > 0) {
                        next_arrival = min(next_arrival, processes[i].at);
                    }
                }
                if (next_arrival > current_time) {
                    if (current_time > 0 || completed > 0) {
                        cout << "[ Empty ]" << endl;
                    }
                    current_time = next_arrival;
                }
                addNewlyArrived();
                continue;
            }

            printQueue();

            int idx = readyQueue.front();
            readyQueue.pop();
            processes[idx].inq = false;
            running = processes[idx].id;

            int exec_time = min(quantum, processes[idx].rem);
            processes[idx].rem -= exec_time;
            current_time += exec_time;

            addNewlyArrived();

            if (processes[idx].rem == 0) {
                completed++;
                processes[idx].ct = current_time;
                processes[idx].tat = processes[idx].ct - processes[idx].at;
                processes[idx].wt = processes[idx].tat - processes[idx].bt;
                running = -1;
                if (readyQueue.empty() && completed < n) {
                    cout << "[ Empty ]" << endl;
                }
            } else {
                readyQueue.push(idx);
                processes[idx].inq = true;
                running = -1;
            }
        }

        cout << "[ Empty ]" << endl;
        cout << endl;

        cout << "Process   Completion   Time Turnaround   Time Waiting Time" << endl;
        float total_waiting = 0;
        for (int i = 0; i < n; i++) {
            cout << "P" << processes[i].id << "\t\t"
                 << processes[i].ct << "\t\t"
                 << processes[i].tat << "\t\t"
                 << processes[i].wt << endl;
            total_waiting += processes[i].wt;
        }

        float avg = total_waiting / n;
        if (avg == static_cast<int>(avg))
            cout << fixed << setprecision(1);
        else
            cout << fixed << setprecision(3);
        cout << "Average Waiting Time: " << avg << endl;
    }
};

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