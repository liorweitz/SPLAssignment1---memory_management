//
// Created by spl211 on 11/9/20.
//

#include "Tree.h"

using namespace std;

Tree::Tree(int rootLabel):node(rootLabel), children() {}

//need to clone. child we get is an rvalue and will be deleted.
void Tree::addChild(const Tree& child){
    children.push_back(child.clone());
}

void Tree::addChildPointer(Tree* child){
    children.push_back(child);
}

//int Tree::getChildrenSize() const{
//    return children.size();
//}

Tree* Tree::createTree(const Session& session, int rootLabel){
    TreeType treeType=session.getTreeType();
    if (treeType==Root){
        return new RootTree(rootLabel);
    }
    else if(treeType==MaxRank){
        return new MaxRankTree(rootLabel);
    }
    else{
        return new CycleTree(rootLabel, session.getCycle());
    }
}


//destructor
Tree::~Tree() {
    for(unsigned i=0; i<children.size();i++){
         if (children.at(i)){
             delete children.at(i);
             children.at(i)=nullptr;
         }
    }

}

//void Tree::erase(){
//    delete this;
//}

//clear children vector
void Tree::clearChildren(){
    for(unsigned i=0; i<children.size();i++){
        if (children.at(i)){
            children.at(i)=nullptr;
        }
    }
}

//copy constructor
Tree::Tree(const Tree &other): node(other.node),children() {
    for (unsigned i=0;i<other.children.size();i++)
        children.push_back((other.children[i])->clone());
}

//copy assignment operator
const Tree& Tree::operator=(const Tree & other) {
    delete this;
    node=other.node;
    for (unsigned i=0;i<other.children.size();i++) {
        children.push_back((other.children[i])->clone());
    }
    return *this;
}

//move constructor
Tree::Tree(Tree&& other): node(other.node),children(){
    children=other.children;
    other.clearChildren();
}
//move assignment operator
const Tree& Tree::operator=(Tree&& other){
    if (this!=&other){
        node=other.node;
        children=other.children;
        other.clearChildren();
    }
    return *this;
}


CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle) {}

int CycleTree::traceTree() {
    int cycles=currCycle;
    CycleTree* currTree=this;
    while ((cycles!=0) & (currTree->children.size()!=0)){
        currTree= dynamic_cast<CycleTree *>((*currTree).children[0]);
        cycles--;
    }
    return (*currTree).node;
}

CycleTree * CycleTree::clone() const {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    std::queue<MaxRankTree*> treeQ;
    treeQ.push(this);
    int maxRankNode=this->node;
    unsigned maxChildrenSize=this->children.size();
    while (!treeQ.empty()){
        MaxRankTree* currTree=treeQ.front();
        treeQ.pop();
        if ((currTree->children.size())>(maxChildrenSize)){
            maxRankNode=currTree->node;
            maxChildrenSize=currTree->children.size();
        }
        for (unsigned i=0;i<currTree->children.size();i++){
            MaxRankTree* child= dynamic_cast<MaxRankTree *>(currTree->children[i]);
            treeQ.push(child);
        }
    }
    return maxRankNode;
}

MaxRankTree* MaxRankTree::clone() const{
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {
    return node;
}
RootTree* RootTree::clone() const {
    return new RootTree(*this);
}
