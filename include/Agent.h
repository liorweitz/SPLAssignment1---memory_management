#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Session;

class Agent{
public:
    Agent();
    virtual Agent* clone() const=0;
    virtual void act(Session& session)=0;
    virtual ~Agent();
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual void act(Session& session);
//    ContactTracer(const ContactTracer& other);
    virtual Agent * clone() const;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
//    Virus(const Virus& other);
    virtual Agent* clone() const;
    int getNode() const;
    virtual void act(Session& session);
    static void increaseActiveViruses();
    static bool termination();
protected:
    const int nodeInd;
    static int activeViruses;
};

#endif
