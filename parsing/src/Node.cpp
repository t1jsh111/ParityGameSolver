//
// Created by tijsh on 1-1-2022.
//

#include "Node.h"

#include <utility>
#include <iostream>

Node::Node(int id) :
id(id)
{

}

std::vector<std::shared_ptr<Node>> Node::getSuccessors() const {
    return successors;
}

void Node::setSpecification(int priority, bool owner, std::vector<std::shared_ptr<Node>> successors) {
    this->priority = priority;
    this->owner = owner;
    this->successors = std::move(successors);
}


int Node::getId() const {
    return id;
}

int Node::getPriority() const {
    return priority;
}

bool Node::isEven() const {
    if(owner == 0) {
        return true;
    } else {
        return false;
    }
}

bool Node::isOdd() const {
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
