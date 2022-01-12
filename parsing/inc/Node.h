//
// Created by tijsh on 1-1-2022.
//

#ifndef PARITYGAMESOLVER_NODE_H
#define PARITYGAMESOLVER_NODE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <unordered_set>

class Node {
public:
//    typedef std::shared_ptr<std::unordered_map<int, Node>> Mapping;

    Node(int id, int priority, bool owner);

    void setSuccessors(std::unordered_set<std::shared_ptr<Node>> successors);
    void addPredecessor(std::shared_ptr<Node> predecessor);

    int getId() const;
    int getPriority() const;

    bool isDiamond() const;
    bool isSquare() const;
    bool getOwner() const;

    bool hasEvenPriority() const;
    bool hasOddPriority() const;

    bool hasSelfLoop() const;
    void setSelfLoop(bool selfLoop);

    bool hasOnlySingleSuccessor() const;




    const std::unordered_set<std::shared_ptr<Node>> & getSuccessors() const;
    const std::unordered_set<std::shared_ptr<Node>> & getPredecessors() const;

    void printSuccessors() const;

private:
    int id;
    int priority;
    bool owner;
    std::string nodeName;
    bool selfLoop;


public:
    const std::string &getNodeName() const;

    void setNodeName(const std::string &nodeName);

private:
    std::unordered_set<std::shared_ptr<Node>> successors;
    std::unordered_set<std::shared_ptr<Node>> predecessors;

};


#endif //PARITYGAMESOLVER_NODE_H
