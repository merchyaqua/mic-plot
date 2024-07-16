#include <bits/stdc++.h>

#include <cstdio>
using namespace std;

struct State{
    vector<vector<int>> micPlot;
    int scene;
    int unassignedMics;
};

struct Swap{
    int from;
    int to;
    int scene;
};

vector<Swap> swaps;

int numScenes, numActors;
int micsAvail = 30;

vector<vector<int>> play; // will now be [scene][actor], 0 indexed
map<string,int> actorNums;
map<int,string> actorNames;
stack<State> frontier;

void setio() {
    freopen("odyssiad.in", "r", stdin);
    freopen("odyssiad.out", "w", stdout);
}

void dfs(){

    State current = frontier.top();
    frontier.pop();

        for (int actor = 0; actor < numActors; actor++) {
            if (current.micPlot[current.scene][actor] == 0){
                if (current.micPlot[current.scene][actor] == -1 && current.unassignedMics >0){
                    // micsNeeded ++; 
                    current.unassignedMics--;
                    current.micPlot[current.scene][actor] = micsAvail-current.unassignedMics;
                    cout << actorNames[actor] << " gets mic " << micsAvail-current.unassignedMics << endl;
                    continue;

                }
                // cout << "Scene " << scene << actorNames[actor] << " needs mic"<< endl;
                for (int colleague = 0; colleague < numActors; colleague++)
                {
                    if (colleague == actor) continue;
                    if (hasMic[colleague] && !play[colleague][scene] && !play[colleague][scene-1]){
                        // cout << "Swap during scene " << scene-1 << ": " 
                        // << actorNames[colleague] << hasMic[colleague] << " -> "
                        //  << actorNames[actor] << hasMic[actor] << endl;
                        
                        hasMic[actor] = hasMic[colleague];
                        hasMic[colleague] = 0;
                        Swap s;
                        s.from = colleague;
                        s.to = actor;
                        s.scene = current.scene-1; // the swap occurs before scene needed
                        swaps.push_back(s);

                        // actorSwaps[colleague]++;
                        // actorSwaps[actor] ++;
                        break; // stop asking you already got one
                    }
                }
                // if (!hasMic[actor]){ // nothing worked for them so let's assign new
                //     micsNeeded ++;
                //     hasMic[actor] = micsNeeded;
                //     cout << actorNames[actor] << " gets mic " << micsNeeded << endl;
                // }
            }
        }

}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setio();
    // cout << "Number of scenes: ";
    cin >> numScenes;
    // cout << "Number of actors: ";
    cin >> numActors;
    int actorCount = 0;
    // cout << "Scene " << ": ";

    play.resize(numScenes);

    // reading in who's in what scene
    for (int scene = 0; scene < numScenes; scene++)
    {
        int numActorsInScene;
        // cout << "Scene " << scene << ": ";
        cin >> numActorsInScene;
        for (int i = 0; i < numActors; i++)
        {
            play[scene].push_back(-1);
        }
        
        for (int i = 0; i < numActorsInScene; i++)
        {
            string name;
            cin >> name;
            if (!actorNums[name]){
                actorNums[name] = actorCount;
                actorNames[actorCount] = name;
                actorCount++;
            }
            play[scene][actorNums[name]] = 0;

        }
        cout << '\n';
        
    }
    // cout << "Thanks for the input.\n";

// all has mic 0 i.e. no mic
    // int actorSwaps[numActors+1]{};

    dfs();
    
    
    // cout << "Mics needed: " << 'p' << endl;
    cout << "Swaps needed: " << swaps.size() << endl; 
    // for (auto swap : swaps)
    // {
    //     cout << "Scene " << swap.scene << ": " << actorNames[swap.from] << " -> " << actorNames[swap.to] << endl;
    // }
    
    // sort(actorSwaps, actorSwaps+numActors+1);

    for (int actor = 1; actor < numActors+1; actor++){
        if (actorSwaps[actor] == 0) continue;;
        cout << actorNames[actor] << ": " << actorSwaps[actor] << " swaps \n";
    }
    



}