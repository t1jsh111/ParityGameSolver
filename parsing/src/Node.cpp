//
// Created by tijsh on 1-1-2022.
//

#include "Node.h"

#include <utility>
#include <iostream>

Node::Node(int id, int priority, bool owner) :
id(id), priority(priority), owner(owner), selfLoop(false)
{

}



void Node::setSuccessors(std::unordered_set<std::shared_ptr<Node>> successors) {
    this->successors = std::move(successors);
}


int Node::getId() const {
    return id;
}

int Node::getPriority() const {
    return priority;
}

bool Node::isDiamond() const {
    if(owner == 0) {
        return true;
    } else {
        return false;
    }
}

bool Node::isSquare() const {
    if(owner == 1) {
        return true;
    } else {
        return false;
    }
}

bool Node::getOwner() const {
    return owner;
}

void Node::printSuccessors() const{
    std::cout << "Successors: ";

    for(auto successor : successors) {
        std::cout << successor->getId();
        std::cout << ", ";
    }
    std::cout << std::endl;
}

const std::string &Node::getNodeName() const {
    return nodeName;
}

void Node::setNodeName(const std::string &nodeName) {
    Node::nodeName = nodeName;
}

bool Node::hasEvenPriority() const{
    return (priority % 2 == 0);
}

bool Node::hasOddPriority() const {
    return !(hasEvenPriority());
}

void Node::addPredecessor(std::shared_ptr<Node> predecessor) {
    predecessors.insert(std::move(predecessor));
}

bool Node::hasSelfLoop() const {
    return selfLoop;
}

void Node::setSelfLoop(bool selfLoop) {
    Node::selfLoop = selfLoop;
}

const std::unordered_set<std::shared_ptr<Node>> & Node::getSuccessors() const {
    return successors;
}

const std::unordered_set<std::shared_ptr<Node>> &Node::getPredecessors() const {
    return predecessors;
}

bool Node::hasOnlySingleSuccessor() const {
    return successors.size() == 1;
}
