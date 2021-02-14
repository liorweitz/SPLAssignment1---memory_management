#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <utility>
#include <memory>



class Tree;
class Session;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph(const Graph & other);
    const Graph& operator=(const Graph& other);

    void makeCarrier(int nodeInd);
    bool isCarrier(int nodeInd);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void removeEdges(int nodeInd);
    void setVerticesStatus(int status);
    Tree* BFSScan(int nodeInt, const Session& session);
    std::queue<int> getNeighbors(int curr);
    void setVerticeStatus(int nodeInd,int status);
    int getVerticeStatus(int nodeInd);
    std::vector<std::vector<int>> getEdges();


private:
    std::vector<std::vector<int>> edges;
    std::vector<int> verticesStatus;


};

#endif
