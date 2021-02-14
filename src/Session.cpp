//
// Created by spl211 on 11/7/20.
//

#include "Session.h"

using namespace std;
using json = nlohmann::json;

int Session::cycle=0;
Session::Session(const std::string& path): g(vector<vector<int>>(0,vector<int>(0,0))), treeType(), agents(),infectedQ(){

    json j;
    std::ifstream ifs(path);
    ifs >> j;

    g=Graph(j["graph"]);
    string type=j["tree"];
    if (type=="R"){
        treeType=Root;
    }
    else if (type=="M"){
        treeType=MaxRank;
    }
    else {
        treeType=Cycle;
    }
    json jAgents=j["agents"];
    for (unsigned i=0; i<jAgents.size();i++){
        if (jAgents[i][0]=="C"){
            ContactTracer *tracer=new ContactTracer(); //heap
            addAgent(*tracer);
            delete tracer;
        }
        else if (jAgents[i][0]=="V"){
//            Virus::increaseActiveViruses();
            Virus *vir=new Virus(jAgents[i][1]);
            addAgent(*vir);
            delete vir;
        }
    }
}

void Session::simulate() {
    g.setVerticesStatus(0);
    for (unsigned i=0; i<agents.size();i++){
        if (auto virus=dynamic_cast<const Virus*>(agents[i])){
            setVerticeStatus(virus->getNode(),1);
        }
    }
//    for (int i=0; i<g.getEdges().size();i++){
//        lonelyInfectedNodes.push_back(0);
//    }
     while (!Virus::termination()){
        int currAgentsSize=agents.size();
        for (int i=0; i<currAgentsSize;i++){
            Agent* currAgent=(agents[i])->clone();
            currAgent->act(*this);
            delete currAgent;
        }
         cycle++;
    }
     std::vector<int> infectedList;
     for (unsigned i=0;i<g.getEdges().size();i++){
         if (getVerticeStatus(i)!=0){
            infectedList.push_back(i);
        }
    }
    json jOutput;
    jOutput["graph"]=g.getEdges();
    jOutput["infected"]=infectedList;
    std::ofstream file("output.json");
    file<<jOutput;
    clearAgents();
}

void Session::addAgent(const Agent &agent) {
    Agent* clone=agent.clone();
    agents.vector::push_back(clone);
}

void Session::setGraph(const Graph &graph) {
    g=graph;
}

void Session::enqueueInfected(int nodeInt) {
    g.infectNode(nodeInt);
    infectedQ.push(nodeInt);
}

int Session::dequeueInfected() {
    if (!infectedQ.empty()) {
        int infectedNode=infectedQ.front();
        infectedQ.pop();
        return infectedNode;
    }
    return -2;
}

bool Session::isInfectedQEmpty(){
    return infectedQ.empty();
}

TreeType Session::getTreeType() const {
    return treeType;
}

//void Session::setLonely(int nodeInd){
//    lonelyInfectedNodes[nodeInd]=1;
//}

//bool Session::isLonely(int nodeInd) {
//    return lonelyInfectedNodes[nodeInd]==1;
//}
//access to Graph methods
void Session::makeCarrier(int nodeInd){
    g.makeCarrier(nodeInd);
}

bool Session::isCarrier(int nodeInd){
    return g.isCarrier(nodeInd);
}

bool Session::isInfected(int nodeInd) {
    return g.isInfected(nodeInd);
}

void Session::setVerticeStatus(int nodeInd, int status){
    g.setVerticeStatus(nodeInd, status);
}

int Session::getVerticeStatus(int nodeInd){
    return g.getVerticeStatus(nodeInd);
}

std::queue<int> Session::getNeighbors(int nodeInd){
    return g.getNeighbors(nodeInd);
}

Tree* Session::BFSScan(int nodeInd){
    return g.BFSScan(nodeInd, *this);
}

void Session::removeEdges(int nodeInd){
    g.removeEdges(nodeInd);
}

//destructor
Session::~Session(){
    clearAgents();
}
void Session::clearAgents(){
    for (const Agent* elem:agents){
        if (elem) delete elem;
    }
    agents.clear();
}
void Session::clearQueue() {
    while(!infectedQ.empty()){
        infectedQ.pop();
    }
}

//copy constructor
Session::Session(const Session & other):  g(other.g),treeType(other.treeType),agents(other.agents.size()), infectedQ(other.infectedQ) {
    clearAgents();
    for(auto agent:other.agents){
        addAgent(*(*agent).clone());
    }
}

//copy assignment operator
const Session & Session::operator=(const Session& other){
    if (this!=&other) {
        g = other.g;
        treeType = other.treeType;
        clearQueue();
        infectedQ = other.infectedQ;
//        lonelyInfectedNodes=other.lonelyInfectedNodes;
        clearAgents();
        for (auto agent:other.agents) {
            addAgent(*(*agent).clone());
        }
    }
    return *this;
}

//move constructor
Session::Session(Session&& other):g(vector<vector<int>>()),treeType(other.treeType),agents(),infectedQ(other.infectedQ){
    if (this!=&other){
        g=other.g;
//      infectedQ=other.infectedQ;
        agents=std::move(other.agents);
//        lonelyInfectedNodes=other.lonelyInfectedNodes;
    }
}

//move assignment operator
const Session& Session::operator=(Session&& other){
    clearAgents();
    agents=other.agents;
    g=other.g;
    infectedQ=other.infectedQ;
//    lonelyInfectedNodes=other.lonelyInfectedNodes;
    treeType=other.treeType;
    return *this;
}

const int Session::getCycle() const{
    return Session::cycle;
}

//Graph& Session::getGraph(){
//    return g;
//}





