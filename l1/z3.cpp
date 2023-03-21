#include <iostream>
#include <bits/stdc++.h>
#include <list>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct graphEdge{
    int startV, endV;
};

class Graph{
private:
    void SCCUt(int u, int disc[], int low[], stack<int>* stack, bool isOnStack[]){
        static int time = 0;
        disc[u] = low[u] = time++;
        stack->push(u);
        isOnStack[u] = true;
        for(auto i = verticesList[u].begin(); i != verticesList[u].end(); i++){
            int v = *i;
            if(disc[v] == -1){
                SCCUt(v, disc, low, stack, isOnStack);
                low[u] = min(low[u], low[v]);
            }
            else if(isOnStack[v]){
                low[u] = min(low[u], disc[v]);
            }
        }

        int popped;
        int numOfComponents = 0;
        if(low[u] == disc[u]){
            while(stack->top() != u){
                numOfComponents++;
                popped = stack->top();
                if(numOfVertices<=200) cout << popped + 1 << " ";
                isOnStack[popped] = false;
                stack->pop();
            }
            popped = stack->top();
            numOfComponents++;
            if(numOfVertices<=200) cout << popped + 1 << " ";
            isOnStack[popped] = false;
            stack->pop();
            cout << "#" << numOfComponents << endl;
        }

    }

public:
    map<int, list<int>> verticesList;
    int numOfVertices;

    Graph(int V, list<graphEdge> edges) {
        this->numOfVertices = V;
        list<graphEdge>::iterator i;
        for(i = edges.begin(); i!=edges.end();i++){
            graphEdge edge = *i;
            addEgde(edge);
        }
    }

    void addEgde(graphEdge edge){
        verticesList[edge.startV-1].push_back(edge.endV-1);
    }

    void findSCC(){
        int* disc = new int[numOfVertices];
        int* low = new int[numOfVertices];
        bool* isOnStack = new bool[numOfVertices];
        stack<int> stack;
        for(int i = 0; i < numOfVertices; i++){
            disc[i] = -1;
            low[i] = -1;
            isOnStack[i] = false;
        }
        for(int i = 0; i< numOfVertices; i++){
            if(disc[i] == -1){
                SCCUt(i, disc, low, &stack, isOnStack);
            }
        }

    }

};



int main(){
    // Wczytywanie danych z pliku
    clock_t start = clock();
    cout << "Wczytywanie danych...";
    string line;
    string space_delimiter = " ";

    ifstream file("E:/STUDIA/AOD/list1/project1/aod_testy1/3/g3-5.txt");

    int i = 1;
    int V;

    list<graphEdge> edges;

    while(getline(file, line)){
        vector<string> values{};

        if(i==2){
            V = stoi(line);
        }
        else if(i!=1 && i!=3){
            size_t pos;
            while ((pos = line.find(space_delimiter)) != string::npos){
                values.push_back(line.substr(0, pos));
                line.erase(0, pos + space_delimiter.length());
            }
            values.push_back(line);
            graphEdge edge = {stoi(values[0]), stoi(values[1])};
            edges.push_back(edge);
        }
        i++;

    }
    file.close();
    clock_t end = clock();
    cout << (end - start)/(double)CLOCKS_PER_SEC << "s"<< endl;
    // Wczytano dane

    Graph graph(V, edges);
    graph.findSCC();
    return 0;
}
