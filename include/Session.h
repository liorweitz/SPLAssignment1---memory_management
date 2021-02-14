#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "Agent.h"
#include <fstream>
#include "json.hpp"
#include <memory>
#include <queue>
#include "Tree.h"
#include <fstream>

//forward declaration to calm the compiler and tell
//him that i can use references to this class.
class Agent;
class Graph;

//its like a map. TreeType variable is actually like:
//TreeType{Cycle=0, MaxRank=1, Root=2};
enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    void enqueueInfected(int);
    int dequeueInfected();
    bool isInfectedQEmpty();
    TreeType getTreeType() const;
//    void setLonely(int nodeInd);
//    bool isLonely(int nodeInd);

    //session here is just the middle man between other classes
    //and Graph
    void makeCarrier(int nodeInd);
    bool isCarrier(int nodeInd);
    bool isInfected(int nodeInd);
    void setVerticeStatus(int nodeInd, int status);
    int getVerticeStatus(int nodeInd);
    std::queue<int> getNeighbors(int nodeInd);
    Tree* BFSScan(int nodeInd);
    void removeEdges(int nodeInd);

    //destructor
    virtual ~Session();
    //copy constructor
    Session(const Session & other);
    //copy assignment operator
    const Session &operator=(const Session& other);
    //move constructor
    Session(Session&& other);
    //move assignment operator
    const Session& operator=(Session&& other);

    const int getCycle() const;
//    Graph& getGraph();

private:
    Graph g;
    TreeType treeType;
    std::vector<const Agent*> agents;
    std::queue<int> infectedQ;
//    std::vector<int> lonelyInfectedNodes;
    static int cycle;

    void clearAgents();
    void clearQueue();

};

#endif
