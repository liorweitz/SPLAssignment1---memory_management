//
// Created by spl211 on 11/7/20.
//
#include "Graph.h"
#include "Tree.h"


//vertice {healthy-0; carrier-1, infected-2}
Graph::Graph(std::vector <std::vector<int>> matrix): edges(std::move(matrix)), verticesStatus(){}

Graph::Graph(const Graph & other):edges(other.edges), verticesStatus(other.verticesStatus){}

const Graph& Graph::operator=(const Graph& other){
    edges=other.edges;
    verticesStatus=other.verticesStatus;
    return *this;
}

void Graph::makeCarrier(int nodeInd){
    verticesStatus[nodeInd]=1;
}

bool Graph::isCarrier(int nodeInd){
    return verticesStatus[nodeInd]==1;
}

void Graph::infectNode(int nodeInd) {
    verticesStatus[nodeInd]=2;
}

bool Graph::isInfected(int nodeInd) {
    if(verticesStatus[nodeInd]==2){
        return true;
    }
    return false;
}

void Graph::removeEdges(int nodeInd){
    for (unsigned i=0;i<edges.size();i++){
        edges[i][nodeInd]=0;
        edges[nodeInd][i]=0;
    }
}

void Graph::setVerticesStatus(int status) {
    for (unsigned i=0;i<edges[0].size();i++){
        verticesStatus.push_back(status);
    }
}

Tree* Graph::BFSScan(int nodeInd, const Session& session){
    std::vector<int> visitedVertices=std::vector<int>(edges.size(),0); //visited vertices
    std::queue<int> verticesQ; //queue of vertices to go on.
    std::vector<Tree*> treeVector=std::vector<Tree*>(edges.size());
    visitedVertices[nodeInd]=1;
    verticesQ.push(nodeInd);
    Tree* root=Tree::createTree(session, nodeInd);
    treeVector[nodeInd]=root;
    int currVer=nodeInd;
    while (!verticesQ.empty()){
       currVer=verticesQ.front();
       verticesQ.pop();
       std::queue<int> neighbors=getNeighbors(currVer); //neighbors vertices queue
       while (!neighbors.empty()){
           int neigh=neighbors.front();
           neighbors.pop();
           if (visitedVertices[neigh]==0){
               visitedVertices[neigh]=1;
               treeVector[neigh]=Tree::createTree(session, neigh);
               treeVector[currVer]->addChildPointer(treeVector[neigh]);
               verticesQ.push(neigh);

           }
       }
    }
    return treeVector[nodeInd];
}

std::queue<int> Graph::getNeighbors(int curr){
    std::queue<int> neighbors;
    for (unsigned i=0;i<edges.size();i++){
        if (edges[curr][i]==1){
            neighbors.push(i);
        }
    }
    return neighbors;
}

void Graph::setVerticeStatus(int nodeInd, int status) {
    verticesStatus[nodeInd]=status;
}

int Graph::getVerticeStatus(int nodeInd){
    return verticesStatus[nodeInd];
}

std::vector<std::vector<int>> Graph::getEdges(){
    return edges;
}

