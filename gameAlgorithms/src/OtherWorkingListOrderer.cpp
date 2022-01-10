//
// Created by Tijs Hoeijmakers on 05/01/2022.
//

#include "OtherWorkingListOrderer.h"

std::list<std::shared_ptr<Node>>
OtherWorkingListOrderer::getInitialWorkingList(const std::vector<std::shared_ptr<Node>> &nodes) {

    std::list<std::shared_ptr<Node>> squareOddSelfloop;
    std::list<std::shared_ptr<Node>> squareOddWithoutSelfloop;
    std::list<std::shared_ptr<Node>> diamondOdd;
    std::list<std::shared_ptr<Node>> squareEven;
    std::list<std::shared_ptr<Node>> diamondEven;

    std::list<std::shared_ptr<Node>> workingList;

    for(const auto& node : nodes) {

        if(node->isSquare()) {
            if(node->hasOddPriority()) {
                if(node->hasSelfLoop()) {
                    squareOddSelfloop.push_back(node);
                } else {
                    squareOddWithoutSelfloop.push_back(node);
                }
            } else { // node has even priority
                squareEven.push_back(node);
            }
        } else { // node is diamond
            if(node->hasOddPriority()) {
                diamondOdd.push_back(node);
            } else { // node has even priority
                diamondEven.push_back(node);
            }
        }


    }

    workingList.insert(workingList.end(), squareOddSelfloop.begin(), squareOddSelfloop.end());
    workingList.insert(workingList.end(), squareOddWithoutSelfloop.begin(), squareOddWithoutSelfloop.end());
    workingList.insert(workingList.end(), diamondOdd.begin(), diamondOdd.end());
    workingList.insert(workingList.end(), squareEven.begin(), squareEven.end());
    workingList.insert(workingList.end(), diamondEven.begin(), diamondEven.end());


    return workingList;
}

void OtherWorkingListOrderer::appendPredecessorsOfNodeToWorkingList(const Node& node, std::list<std::shared_ptr<Node>> &workingList, const std::unordered_map<int, ProgressMeasure>& rhoMapping) {

    std::list<std::shared_ptr<Node>> squareOddSelfloop;
    std::list<std::shared_ptr<Node>> squareOddWithoutSelfloop;
    std::list<std::shared_ptr<Node>> diamondOdd;
    std::list<std::shared_ptr<Node>> squareEven;
    std::list<std::shared_ptr<Node>> diamondEven;

    std::list<std::shared_ptr<Node>> predecessorWorkingList;




    auto predecessors = node.getPredecessors();

    for(const auto& predecessor : predecessors) {

    }


    for(const auto& predecessor : predecessors) {
        // We can ignore predecessors that are  top
        if(rhoMapping.at(predecessor->getId()).isTop() ) {continue;}

        if(predecessor->isSquare()) {
            if(predecessor->hasOddPriority()) {
                if(predecessor->hasSelfLoop()) {
                    squareOddSelfloop.push_back(predecessor);
                } else {
                    squareOddWithoutSelfloop.push_back(predecessor);
                }
            } else { // node has even priority
                squareEven.push_back(predecessor);
            }
        } else { // node is diamond
            if(predecessor->hasOddPriority()) {
                diamondOdd.push_back(predecessor);
            } else { // node has even priority
                diamondEven.push_back(predecessor);
            }
        }
    }




    predecessorWorkingList.insert(predecessorWorkingList.end(), squareOddSelfloop.begin(), squareOddSelfloop.end());
    predecessorWorkingList.insert(predecessorWorkingList.end(), squareOddWithoutSelfloop.begin(), squareOddWithoutSelfloop.end());
    predecessorWorkingList.insert(predecessorWorkingList.end(), diamondOdd.begin(), diamondOdd.end());
    predecessorWorkingList.insert(predecessorWorkingList.end(), squareEven.begin(), squareEven.end());
    predecessorWorkingList.insert(predecessorWorkingList.end(), diamondEven.begin(), diamondEven.end());

    workingList.insert(workingList.begin(),predecessorWorkingList.begin(), predecessorWorkingList.end() );
}
