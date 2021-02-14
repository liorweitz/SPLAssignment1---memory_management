#ifndef TREE_H_
#define TREE_H_

#include "Session.h"
#include "Graph.h"
#include <vector>
#include <string>
#include <iostream>


class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    void addChildPointer(Tree* child);
//    int getChildrenSize() const;

    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

//    std::vector<Tree *> copyTree(const Tree &other);

//destructor
    virtual ~Tree();
//erase
//    void erase();
//clear children vector
    void clearChildren();
//copy constructor
    Tree(const Tree & other);
//copy assignment operator
    const Tree& operator=(const Tree & other);
//clone
    virtual Tree* clone() const=0;
//move constructor
    Tree(Tree&& other);
//move assignment operator
    const Tree& operator=(Tree&& other);

protected:
    int node;
    std::vector<Tree*> children;
};

//CycleTree
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual CycleTree* clone() const;
private:
    int currCycle;
};

//MaxRankTree
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual MaxRankTree* clone() const;
};
//RootTree
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual RootTree* clone() const;
};



#endif
