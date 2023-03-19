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
    void DFS(bool visited[], int startVertex, bool print, list<int> *stack){
        visited[startVertex] = true;
        if(print) cout << startVertex + 1 << ", ";
        list<int> adj = verticesList[startVertex];
        list<int>::iterator i;
        for(i = adj.begin(); i!=adj.end(); i++){
            if(!visited[*i]) DFS(visited, *i, print, stack);
        }
        if(!print) stack->push_front(startVertex);
    }

    Graph getTranspose(){
        Graph transpose(this->numOfVertices);
        for(int v = 0; v<numOfVertices; v++){
            list<int>::iterator i;
            for(i = verticesList[v].begin(); i!=verticesList[v].end(); i++){
                graphEdge edge = {*i+1, v+1};
                transpose.addEgde(edge);
            }
        }
        return transpose;
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

    explicit Graph(int V){
        this->numOfVertices = V;
    }

    void addEgde(graphEdge edge){
        verticesList[edge.startV-1].push_back(edge.endV-1);
    }

    void findSSC(){
        cout << "SSC:" <<endl;
        list<int> stack;
        bool* visited = new bool[numOfVertices];
        for(int i = 0; i< numOfVertices; i++) visited[i] = false;

        // step 1: fill order
        for(int i = 0; i< numOfVertices; i++){
            if(!visited[i]) DFS(visited, i, false, &stack);
        }

        // step 2: get transpose graph
        Graph tr = getTranspose();
        for(int i = 0; i< numOfVertices; i++) visited[i] = false;

        // step 3: process vertices on stack
        while(!stack.empty()){
            int v = stack.front();
            stack.pop_front();
            // print ssc
            if(!visited[v]){
                tr.DFS(visited, v, true, &stack);
                cout << "/"<< endl;
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

    ifstream file("E:/STUDIA/AOD/list1/project1/aod_testy1/3/g3-2.txt");

    int i = 1;
    bool directed;
    int V, E;

    list<graphEdge> edges;

    while(getline(file, line)){
        vector<string> values{};

        if(i==1){
            char* dir = new char[1];
            strcpy(dir, line.c_str());
            if(dir[0] == 'D') directed = true;
            else directed = false;
        } else if(i==2){
            V = stoi(line);
        }
        else if(i==3){
            E = stoi(line);
        }
        else{
            size_t pos = 0;
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
    graph.findSSC();

}