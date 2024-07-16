#include <bits/stdc++.h>
using namespace std;

struct Event {
    int time;
    int actor;
    bool entering; // true if actor is entering the stage, false if leaving
    bool operator<(const Event &other) const {
        return time > other.time; // for priority queue, earliest event first
    }
};

struct Swap {
    int from;
    int to;
    int scene;
};

void setio() {
    freopen("odyssiad.in", "r", stdin);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setio();

    int numScenes, numActors;
    int micsAvail = 30;
    cin >> numScenes >> numActors;

    bool play[numActors + 1][numScenes + 1]{};
    map<string, int> actorNums;
    map<int, string> actorNames;
    int actorCount = 1;

    vector<Event> events;

    for (int scene = 1; scene <= numScenes; scene++) {
        int numActorsInScene;
        cin >> numActorsInScene;
        for (int i = 0; i < numActorsInScene; i++) {
            string name;
            cin >> name;
            if (!actorNums[name]) {
                actorNums[name] = actorCount;
                actorNames[actorCount] = name;
                actorCount++;
            }
            int actor = actorNums[name];
            play[actor][scene] = true;
            events.push_back({scene, actor, true});
        }
    }

    for (int actor = 1; actor <= numActors; actor++) {
        for (int scene = 1; scene <= numScenes; scene++) {
            if (play[actor][scene] && (scene == numScenes || !play[actor][scene + 1])) {
                events.push_back({scene, actor, false});
            }
        }
    }

    sort(events.begin(), events.end(), [](const Event &a, const Event &b) {
        return a.time < b.time || (a.time == b.time && a.entering < b.entering);
    });

    int hasMic[numActors + 1]{};
    vector<Swap> swaps;
    int actorSwaps[numActors + 1]{};
    int micsNeeded = 0;
    priority_queue<int, vector<int>, greater<int>> freeMics;
    unordered_set<int> busyActors;

    for (int i = 1; i <= micsAvail; ++i) {
        freeMics.push(i);
    }

    for (const Event &event : events) {
        int actor = event.actor;
        if (event.entering) {
            if (!freeMics.empty()) {
                int mic = freeMics.top();
                freeMics.pop();
                hasMic[actor] = mic;
                busyActors.insert(actor);
                cout << actorNames[actor] << " gets mic " << mic << " at scene " << event.time << endl;
            } else {
                for (int colleague : busyActors) {
                    if (!play[colleague][event.time] && !play[colleague][event.time - 1]) {
                        int mic = hasMic[colleague];
                        hasMic[actor] = mic;
                        hasMic[colleague] = 0;
                        Swap s = {colleague, actor, event.time - 1};
                        swaps.push_back(s);
                        actorSwaps[colleague]++;
                        actorSwaps[actor]++;
                        busyActors.erase(colleague);
                        busyActors.insert(actor);
                        cout << "Swap during scene " << event.time - 1 << ": " << actorNames[colleague] << " " << mic << " -> " << actorNames[actor] << endl;
                        break;
                    }
                }
            }
        } else {
            int mic = hasMic[actor];
            if (mic != 0) {
                freeMics.push(mic);
                busyActors.erase(actor);
                hasMic[actor] = 0;
            }
        }
    }

    cout << "Mics needed: " << min(micsAvail, int(freeMics.size())) << endl;
    cout << "Swaps needed: " << swaps.size() << endl;

    for (int actor = 1; actor <= numActors; actor++) {
        if (actorSwaps[actor] == 0) continue;
        cout << actorNames[actor] << ": " << actorSwaps[actor] << " swaps \n";
    }
}
