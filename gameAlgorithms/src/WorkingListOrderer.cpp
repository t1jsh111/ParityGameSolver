//
// Created by Tijs Hoeijmakers on 10/01/2022.
//

#include "WorkingListOrderer.h"

void WorkingListOrderer::addNode(std::shared_ptr<Node> node) {
    workingList.push(node);
}

std::shared_ptr<Node> WorkingListOrderer::popFront() {
    auto front = workingList.front();
    workingList.pop();
    return front;
}

bool WorkingListOrderer::isEmpty() const {
    return workingList.empty();
}
