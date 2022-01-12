//
// Created by tijsh on 2-1-2022.
//

#include "ProgressMeasuresAlgo.h"
#include "Ordering.h"
#include "OtherWorkingListOrderer.h"

#include "Node.h"


#include <limits>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "ImprovedWorkingListOrderer.h"


void ProgressMeasuresAlgo::solveParityGame(ParityGame &parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping) {


    int d = parityGame.getDValue();
    auto workingList = parityGame.getNodes(); // Input order


    order = Ordering::randomOrder(order); // Random order

    bool madeUpdate = true;
    while(madeUpdate) {
        madeUpdate = false;
        for(const auto& node : workingList) {
            bool lifted = lift(*node, rhoMapping, parityGame);
            if(lifted) {
                madeUpdate = true;
            }
        }
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "solveParityGame exec time: " << microseconds << std::endl;
}

void ProgressMeasuresAlgo::solveParityGameWorkList(ParityGame &parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping) {


    int d = parityGame.getDValue();


    //std::cout << "Input order: ";
    //printVectorElements(order);
    OtherWorkingListOrderer orderer;
    auto workingList = orderer.getInitialWorkingList(parityGame.getNodes());


//    order = Ordering::randomOrder(order); // Random order
    auto start = std::chrono::high_resolution_clock::now();
    while(!workingList.empty()) {
        const auto node = workingList.front();
        workingList.pop_front();
        // On top no lifting needs to be done
        if(rhoMapping.at(node->getId()).isTop()) {continue;}

        bool lifted = lift(*node, rhoMapping, parityGame);

        if(lifted) {
                orderer.appendPredecessorsOfNodeToWorkingList(*node, workingList, rhoMapping);
        }
        //continue lifting until stability is reached..
        while(lifted) {
            lifted = lift(*node, rhoMapping, parityGame);
        }

    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "solveParityGame exec time: " << microseconds << std::endl;

}

void ProgressMeasuresAlgo::solveParityGameImprovedWorkList(ParityGame &parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping) {



    ImprovedWorkingListOrderer workingList;
    for(const auto& node : parityGame.getNodes()) {
        workingList.addNode(node);
    }


    auto start = std::chrono::high_resolution_clock::now();
    while(!workingList.isEmpty()) {
        const auto node = workingList.popFront();
        // On top no lifting needs to be done
        if(rhoMapping.at(node->getId()).isTop()) {continue;}

        bool lifted = lift(*node, rhoMapping, parityGame);

        if(lifted) {
            for(const auto& predecessor : node->getPredecessors()) {
                workingList.addNode(predecessor);
            }
        }
        //continue lifting until stability is reached..
        while(lifted) {
            lifted = lift(*node, rhoMapping, parityGame);
        }

    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "solveParityGame exec time: " << microseconds << std::endl;

}


ProgressMeasure
ProgressMeasuresAlgo::Prog(const std::unordered_map<int, ProgressMeasure> &rhoMapping, const Node &v, const Node &w, const ParityGame &parityGame) {

    std::vector<int> leastVector(parityGame.getDValue());

    auto rhoForW = rhoMapping.at(w.getId());

    // Priority of v is even
    if(v.hasEvenPriority()) {
        // only top >= top
        if(rhoForW.isTop()) {
            return rhoForW;
        } else {
            return rhoForW.getEvenProg(v.getPriority());
        }

    } else { // priority of v is odd
        // only top > top
        if(rhoForW.isTop()) {
            return rhoForW;
        } else {
            return rhoForW.getOddProg(v.getPriority());
        }
    }
}

bool ProgressMeasuresAlgo::lift(const Node &v, std::unordered_map<int, ProgressMeasure>& rhoMapping, const ParityGame &parityGame) {

    // Top won't be lifted further so we can immediately return that no update has been done.
    if(rhoMapping.at(v.getId()).isTop()) {return false;}

    auto& successors = v.getSuccessors();

    std::vector<ProgressMeasure> progMeasures;
    progMeasures.reserve(successors.size());
    for (const auto& w : successors) {
        progMeasures.push_back(Prog(rhoMapping, v, *w, parityGame));
    }

    if(v.isDiamond()) {
        ProgressMeasure minElement = *std::min_element(progMeasures.begin(), progMeasures.end());
        auto updatedProgressMeasure = std::max(rhoMapping.at(v.getId()), minElement);
        if(rhoMapping[v.getId()] == updatedProgressMeasure) {
            return false;
        } else {
            rhoMapping[v.getId()] = updatedProgressMeasure;
            return true;
        }


    } else { // v is box
        ProgressMeasure maxElement = *std::max_element(progMeasures.begin(), progMeasures.end());

        auto updatedProgressMeasure = std::max(rhoMapping.at(v.getId()), maxElement);

        if(rhoMapping[v.getId()] == updatedProgressMeasure) {
            return false;
        } else {
            rhoMapping[v.getId()] = updatedProgressMeasure;
            return true;
        }
    }

}

void ProgressMeasuresAlgo::printVectorElements(const std::vector<std::shared_ptr<Node>> nodes) {
    for (auto i = 0; i < nodes.size(); i++) {
        std::cout << nodes.at(i)->getId() << "; ";
    }
    std::cout << std::endl;
}