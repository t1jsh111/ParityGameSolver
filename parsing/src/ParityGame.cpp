//
// Created by tijsh on 1-1-2022.
//

#include "ParityGame.h"

#include "Node.h"
#include <stdexcept>

ParityGame::ParityGame(int highestIdentifier) : highestIdentifier(highestIdentifier) {

}

void ParityGame::addNode(std::shared_ptr<Node> node) {
    nodeMapping[node->getId()] = std::move(node);
}

const Node &ParityGame::getNodeById(int id) const{
    if(nodeMapping.find(id) == nodeMapping.end()) {
        throw std::runtime_error("Node for this id does not exist...");
    }

    return *nodeMapping.at(id);
}

std::shared_ptr<Node> ParityGame::getNode(int id) const {
    if(nodeMapping.find(id) == nodeMapping.end()) {
        throw std::runtime_error("Node for this id does not exist...");
    }

    return nodeMapping.at(id);
}

int ParityGame::getHighestIdentifier() const {
    return highestIdentifier;
}
