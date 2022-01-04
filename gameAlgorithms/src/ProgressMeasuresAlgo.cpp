//
// Created by tijsh on 2-1-2022.
//

#include "ProgressMeasuresAlgo.h"
#include "Ordering.h"

#include "Node.h"


#include <limits>
#include <iostream>
#include <algorithm>


void ProgressMeasuresAlgo::solveParityGame(ParityGame &parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping) {


    int d = parityGame.getDValue();
    auto order = parityGame.getNodes(); // Input order

    //std::cout << "Input order: ";
    //printVectorElements(order);

    order = Ordering::randomOrder(order); // Random order

    bool madeUpdate = true;
    while(madeUpdate) {
        madeUpdate = false;
        for(const auto& node : order) {
            bool lifted = lift(*node, rhoMapping, parityGame);
            if(lifted) {
                madeUpdate = true;
            }
        }
    }

}

ProgressMeasure
ProgressMeasuresAlgo::Prog(const std::unordered_map<int, ProgressMeasure> &rhoMapping, const Node &v, const Node &w, const ParityGame &parityGame) {

    std::vector<int> leastVector(parityGame.getDValue());

    auto rhoForW = rhoMapping.at(w.getId());

    // Priority of v is even
    if(v.getPriority() % 2 == 0) {
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
    auto successors = v.getSuccessors();
    std::vector<ProgressMeasure> progMeasures;
    for (auto w : successors) {
        progMeasures.push_back(Prog(rhoMapping, v, *w, parityGame));
    }
    if(v.isEven()) {
        ProgressMeasure minElement = *std::min_element(progMeasures.begin(), progMeasures.end());
        auto updatedProgressMeasure = std::max(rhoMapping.at(v.getId()), minElement);
        if(rhoMapping[v.getId()] == updatedProgressMeasure) {
            return false;
        } else {
            rhoMapping[v.getId()] = updatedProgressMeasure;
            return true;
        }


    } else { // v is odd
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