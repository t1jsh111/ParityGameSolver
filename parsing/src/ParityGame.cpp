//
// Created by tijsh on 1-1-2022.
//

#include "ParityGame.h"

#include "Node.h"
#include <stdexcept>

ParityGame::ParityGame(int highestIdentifier) : highestIdentifier(highestIdentifier) {

}

void ParityGame::addNode(std::shared_ptr<Node> node) {
    nodes.push_back(node);

    if(priorityToNodesMap.find(node->getPriority()) == priorityToNodesMap.end()) {
        priorityToNodesMap[node->getPriority()] = std::vector<std::shared_ptr<Node>>();
    }
    priorityToNodesMap[node->getPriority()].push_back(node);

    idToNodeMap[node->getId()] = node;

    highestPriority = std::max(highestPriority, node->getPriority());
}

const Node &ParityGame::getNodeById(int id) const{
    if(idToNodeMap.find(id) == idToNodeMap.end()) {
        throw std::runtime_error("Node for this id does not exist...");
    }

    return *idToNodeMap.at(id);
}

std::shared_ptr<Node> ParityGame::getNode(int id) const {
    if(idToNodeMap.find(id) == idToNodeMap.end()) {
        throw std::runtime_error("Node for this id does not exist...");
    }

    return idToNodeMap.at(id);
}

int ParityGame::getHighestIdentifier() const {
    return highestIdentifier;
}

int ParityGame::getDValue() const {
//    if(nodes.empty()) {
//        throw std::runtime_error("Tries to get d value of empty parity game");
//    }
//    int dValue = nodes[0]->getPriority();
//
//    for(const auto& node : nodes) {
//        dValue = std::max(dValue, node->getPriority());
//    }

    return highestPriority+1;
}

int ParityGame::getNumberOfVerticesWithPriority(int priority) const {
    if(priorityToNodesMap.find(priority) != priorityToNodesMap.end()) {
        return priorityToNodesMap.at(priority).size();
    } else {
        return 0;
    }
}

const std::vector<std::shared_ptr<Node>> &ParityGame::getNodes() const {
    return nodes;
}
