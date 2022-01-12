//
// Created by Tijs Hoeijmakers on 05/01/2022.
//

#include "ImprovedWorkingListOrderer.h"

#include <stdexcept>

bool ImprovedWorkingListOrderer::isEmpty() const {
    return numberOfUpdateNodes == 0;
}

void ImprovedWorkingListOrderer::addNodeToWorkList(std::shared_ptr<Node> node, bool wasPredecessorOfUpdate) {



    if(needsUpdate.find(node) == needsUpdate.end() || !needsUpdate.at(node)) {
        numberOfUpdateNodes++;
    }
    needsUpdate[node] = true;


//    std::queue<std::shared_ptr<Node>> squareOddWithSelfLoop;
//    std::queue<std::shared_ptr<Node>> importantUpdate; // depends on updated node, and is square or depends on update and is diamond with single edge
//    std::queue<std::shared_ptr<Node>> squareOddWithoutSelfloop;
//    std::queue<std::shared_ptr<Node>> squareEven;
//    std::queue<std::shared_ptr<Node>> diamondMultiEdgeUpdate;
//
//    std::queue<std::shared_ptr<Node>> diamondSingleEdge;
//    std::queue<std::shared_ptr<Node>> diamondMultiEdgeEven;
//    std::queue<std::shared_ptr<Node>> diamondMultiEdgeOdd;

    if(wasPredecessorOfUpdate) {
        if(node->isSquare() || (node->isDiamond() && node->hasOnlySingleSuccessor())) {
            importantUpdate.push(node);
        } else { // node is diamond with multiple successors
            diamondMultiEdgeUpdate.push(node);
        }
    } else {
        if(node->isSquare()) {
            if(node->hasOddPriority()) {
                if(node->hasSelfLoop()) {
                    squareOddWithSelfLoop.push(node);
                } else {
                    squareOddWithoutSelfloop.push(node);
                }
            } else {
                squareEven.push(node);
            }
        } else { // node is diamond
            if(node->hasOnlySingleSuccessor()) {
                diamondSingleEdge.push(node);
            } else {
                if(node->hasEvenPriority()) {
                    diamondMultiEdgeEven.push(node);
                } else {
                    diamondMultiEdgeOdd.push(node);
                }
            }


        }
    }

}

std::shared_ptr<Node> ImprovedWorkingListOrderer::popFront() {
    if(numberOfUpdateNodes <= 0) {
        throw std::runtime_error(" The worklist is empty");
    }

    numberOfUpdateNodes--;


    for(const auto& queue : queues) {
        while(queue->size() != 0) {
            auto front = queue->front();
            if(needsUpdate[front]) {
                // it will now be handled;
                needsUpdate[front] = false;
                queue->pop();
                return front;
            } else {
                queue->pop();
            }

        }
    }

    throw std::runtime_error("Should not be reachable");

}
