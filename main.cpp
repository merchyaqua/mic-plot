#include <bits/stdc++.h>

    #include <cstdio>
    using namespace std;

struct Swap{
    int from;
    int to;
    int scene;
};


void setio() {
    freopen("odyssiad.in", "r", stdin);
    // freopen("odyssiad.out", "w", stdout);
}
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    setio();
    int numScenes, numActors;
    cout << "Number of scenes: ";
    cin >> numScenes;
    cout << "Number of actors: ";
    cin >> numActors;
    bool play[numActors+1][numScenes+1]{}; // for ease of 1-indexing
    map<string,int> actorNums;
    map<int,string> actorNames;
    int actorCount = 1;
    cout << "Scene " << ": ";

    for (int scene = 1; scene < numScenes+1; scene++)
    {
        int numActorsInScene;
        cout << "Scene " << scene << ": ";
        cin >> numActorsInScene;
        for (int i = 0; i < numActorsInScene; i++)
        {
            string name;
            cin >> name;
            if (!actorNums[name]){
                actorNums[name] = actorCount;
                actorNames[actorCount] = name;
                actorCount++;
            }
            play[actorNums[name]][scene] = true;

        }
        cout << '\n';
        
    }
    cout << "Thanks for the input.\n";

    bool hasMic[numActors+1]{};
    vector<Swap> swaps;

    int actorSwaps[numActors+1]{};

    int micsNeeded = 0;
    for (int scene = 1; scene < numScenes+1; scene++)
    {
        for (int actor = 1; actor < numActors+1; actor++)
        {
            if (play[actor][scene] && !hasMic[actor]){
                if (scene == 1){
                    micsNeeded ++;
                    hasMic[actor] = true;
                    cout << actorNames[actor] << "gets mic " << micsNeeded << endl;
                }
                for (int colleague = 1; colleague < numActors+1; colleague++)
                {
                    if (colleague == actor) continue;
                    if (hasMic[colleague] && !play[colleague][scene] && !play[colleague][scene-1]){
                        hasMic[actor] = true;
                        hasMic[colleague] = false;
                        Swap s;
                        s.from = colleague;
                        s.to = actor;
                        s.scene = scene-1; // the swap occurs before scene needed
                        swaps.push_back(s);
                        actorSwaps[colleague]++;
                        actorSwaps[actor] ++;
                        break; // stop asking you already got one
                    }
                }
                if (!hasMic[actor]){ // nothing worked for them
                    micsNeeded ++;
                    hasMic[actor] = true;
                    cout << actorNames[actor] << "gets mic " << micsNeeded << endl;

                }
                
            }
        }
        
    }
    
    cout << "Mics needed: " << micsNeeded << endl;
    cout << "Swaps needed: " << swaps.size() << endl; 
    for (auto swap : swaps)
    {
        cout << "Scene " << swap.scene << ": " << actorNames[swap.from] << " -> " << actorNames[swap.to] << endl;
    }
    
    // sort(actorSwaps, actorSwaps+numActors+1);

    for (int actor = 1; actor < numActors+1; actor++)
    {
        if (actorSwaps[actor] == 0) continue;;
        cout << actorNames[actor] << ": " << actorSwaps[actor] << " swaps \n";

    }
    



}