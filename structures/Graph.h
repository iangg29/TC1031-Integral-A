//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 02/12/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_GRAPH_H
#define INTEGRALA_GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <stack>
#include <string>
#include <list>

/**
 * @brief The Graph class
 * 
 */
class Graph {
private:
    int edgesList;
    int nodes;
    std::vector<int> *adjList;

    void dfsHelper(int, int, std::stack<int> &, std::list<int> &, std::vector<std::vector<int>> &, std::stringstream &,
                   std::vector<Circuit>);

public:
    Graph();

    explicit Graph(int);

    void loadGraphList(const std::string &, int);

    void addEdgeList(int, int);

    std::string DFS(int, int, std::vector<Circuit> &);

    static void printPath(std::vector<std::vector<int>> &, int, int, std::stringstream &, std::vector<Circuit> &);

    bool contains(std::list<int>, int);

};

/**
 * @brief Construct a new Graph:: Graph object
 * 
 */
Graph::Graph() {
    edgesList = nodes = 0;
    adjList = {};
}

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param n Number of nodes
 */
Graph::Graph(int n) {
    nodes = n;
    adjList = new std::vector<int>[nodes];
    edgesList = 0;
}

/**
 * @brief Loads a graph from a file
 * 
 * @param file_name Name of the file
 * @param a Number of nodes
 */
void Graph::loadGraphList(const std::string &file_name, int a) {
    nodes = a;
    adjList = new std::vector<int>[nodes];
    std::string line;
    std::ifstream file(file_name);
    int u, v;
    if (file.is_open()) {
        try {
            while (getline(file, line)) {
                std::stringstream s_stream(line);
                while (s_stream.good()) {
                    std::string vs, us;
                    getline(s_stream, us, ',');
                    getline(s_stream, vs, '\n');
                    addEdgeList(std::stoi(us), std::stoi(vs));
                }
            }
        } catch (std::exception &e) {
            std::cout << "[EXCEPTION] " << e.what() << std::endl;
        }
        file.close();
    } else {
        std::cout << "[!] Unable to load graph file." << std::endl;
    }
}

/**
 * @brief Adds an edge to the graph
 * 
 * @param u
 * @param v 
 */
void Graph::addEdgeList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

/**
 * @brief Depth First Search algorithm
 * 
 * @param start Starting node
 * @param goal Goal node
 * @param path Circuits available
 * @return std::string 
 */
std::string Graph::DFS(int start, int goal, std::vector<Circuit> &path) {
    std::stringstream aux;
    std::stack<int> st;
    std::list<int> visited;
    std::vector<std::vector<int>> paths(nodes, std::vector<int>(1, -1));
    st.push(start);
    dfsHelper(start, goal, st, visited, paths, aux, path);
    printPath(paths, start, goal, aux, path);
    return aux.str();
}

/**
 * @brief Helper function for DFS
 * 
 * @param current Current node
 * @param goal Goal node
 * @param st Stack
 * @param visited Node visited
 * @param paths Paths
 * @param aux Node visited in string format
 * @param path Circuits available
 */
void Graph::dfsHelper(int current, int goal, std::stack<int> &st, std::list<int> &visited,
                      std::vector<std::vector<int>> &paths, std::stringstream &aux,
                      std::vector<Circuit> path) {
    if (current == goal) {
        return;
    } else if (st.empty()) {
        std::cout << "[!] Path not found." << std::endl;
        return;
    } else {
        current = st.top();
        st.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); ++i) {
            if (!contains(visited, adjList[current][i])) {
                st.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
            }
        }
        dfsHelper(current, goal, st, visited, paths, aux, std::move(path));
    }
}

/**
 * @brief Prints the path
 * 
 * @param paths Paths
 * @param start Starting node
 * @param goal Goal node
 * @param aux Auxiliar string
 * @param path Circuits available
 */
void Graph::printPath(std::vector<std::vector<int>> &paths, int start, int goal, std::stringstream &aux,
                      std::vector<Circuit> &path) {
    int node = paths[goal][0];
    std::stack<int> reverse;
    reverse.push(goal);
    while (node != start) {
        reverse.push(node);
        node = paths[node][0];
    }

    reverse.push(start);
    while (!reverse.empty()) {
        aux << path[reverse.top()].ref;
        reverse.pop();
        if (!reverse.empty()) {
            aux << " ";
        }
    }
}

/**
 * @brief Checks if a list contains a node
 * 
 * @param lista 
 * @param node 
 * @return true 
 * @return false 
 */
bool Graph::contains(std::list<int> lista, int node) {
    std::list<int>::iterator it;
    it = std::find(lista.begin(), lista.end(), node);
    if (it != lista.end()) {
        return true;
    } else {
        return false;
    }
}


#endif //INTEGRALA_GRAPH_H
