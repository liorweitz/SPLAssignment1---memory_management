//
// Created by spl211 on 11/7/20.
//
#include "Agent.h"

int Virus::activeViruses=0;
Agent::Agent()=default;

ContactTracer::ContactTracer(){}



Agent::~Agent(){}

//ContactTracer::ContactTracer(const ContactTracer &other) {}

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session){
    if (!session.isInfectedQEmpty()) {
        int infectedNode = session.dequeueInfected();
//        Graph g = session.getGraph();
        Tree *tree = session.BFSScan(infectedNode);
        int tracedNode = tree->traceTree();
        session.removeEdges(tracedNode);
        delete tree;
    }
}


Virus::Virus(int nodeInd) : nodeInd(nodeInd){
    activeViruses++;

}

//Virus::Virus(const Virus &other):nodeInd(other.nodeInd) {}

Agent * Virus::clone() const {
    return new Virus(*this);
}

int Virus::getNode() const{
    return nodeInd;
}

void Virus::act(Session &session){
//    Graph g=session.getGraph();
    if ((!session.isInfected(nodeInd)) & (session.getVerticeStatus(nodeInd)!=-1)){
        session.enqueueInfected(nodeInd);
    }
    std::queue<int> neighbors=session.getNeighbors(nodeInd);

    while(!neighbors.empty()){
        int currNode=neighbors.front();
        neighbors.pop();
        if (session.getVerticeStatus(currNode)==0){
            Agent* agent=new Virus(currNode);
            session.addAgent(*agent);
            session.setVerticeStatus(currNode, 1);
            delete agent;
            break;
        }

    }
    if ((neighbors.empty()) & (session.getVerticeStatus(nodeInd)!=-1)){
        activeViruses--;
        session.setVerticeStatus(nodeInd, -1);
    }

}

void Virus::increaseActiveViruses() {
    activeViruses++;
}

bool Virus::termination(){
    return activeViruses==0;
}