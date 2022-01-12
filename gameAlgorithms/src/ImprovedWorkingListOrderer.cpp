//
// Created by Tijs Hoeijmakers on 05/01/2022.
//

#include "ImprovedWorkingListOrderer.h"

#include <stdexcept>

bool ImprovedWorkingListOrderer::isEmpty() const {
    return numberOfUpdateNodes == 0;
}

void ImprovedWorkingListOrderer::addNode(std::shared_ptr<Node> node) {
    addNode(node, false);
}


void ImprovedWorkingListOrderer::addNode(std::shared_ptr<Node> node, bool wasPredecessorOfUpdate) {


    if(needsUpdate.find(node) == needsUpdate.end() || !needsUpdate.at(node)) {
        numberOfUpdateNodes++;
    }
    needsUpdate[node] = true;


//    std::queue<std::shared_ptr<Node>> level1;
//    std::queue<std::shared_ptr<Node>> diamondEvenSingleEdgeSelfLoop;
//    std::queue<std::shared_ptr<Node>> level2; // depends on updated node, and is square or depends on update and is diamond with single edge
//    std::queue<std::shared_ptr<Node>> level3;
//    std::queue<std::shared_ptr<Node>> level4;
//    std::queue<std::shared_ptr<Node>> level5;
//
//    std::queue<std::shared_ptr<Node>> diamondSingleEdge;
//    std::queue<std::shared_ptr<Node>> level8;
//    std::queue<std::shared_ptr<Node>> level7;

    if(wasPredecessorOfUpdate) {
        if(node->isSquare() || (node->isDiamond() && node->hasOnlySingleSuccessor())) {
            level2.push(node);
        } else { // node is diamond with multiple successors
            level5.push(node);
        }
    } else {
        if(node->isSquare()) {
            if(node->hasOddPriority()) {
                if(node->hasSelfLoop()) {
                    level1.push(node);
                } else {
                    level3.push(node);
                }
            } else {
                level4.push(node);
            }
        } else { // node is diamond
            if(node->hasOnlySingleSuccessor()) {
                if(node->hasOddPriority()) {
                    if(node->hasSelfLoop()) {
                        level1.push(node);
                    } else {
                        level3.push(node);
                    }
                } else {
                    level6.push(node);
                }

//                if(node->hasSelfLoop() && node->hasOddPriority()) {
//                    level1.push(node);
//                } else {
//                    level6.push(node);
//                }

            } else {
                if(node->hasEvenPriority()) {
                    level8.push(node);
                } else {
                    level7.push(node);
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

