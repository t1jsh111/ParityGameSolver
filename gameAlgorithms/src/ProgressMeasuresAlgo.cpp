//
// Created by tijsh on 2-1-2022.
//

#include "ProgressMeasuresAlgo.h"

#include "Node.h"


#include <limits>
#include <iostream>
#include <random>
#include <algorithm>


void ProgressMeasuresAlgo::solveParityGame(const ParityGame &parityGame) {

    std::unordered_map<int, std::vector<int>> rhoMapping;
    int d = parityGame.getDValue();
    auto order = parityGame.getNodes(); // Input order

    std::cout << "Input order: ";
    for (auto i = 0; i < order.size(); i++) {
        std::cout << order.at(i)->getId() << "; ";
    }
    std::cout << std::endl;

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(order.begin(), order.end(), rng); // Random order

    std::cout << "Random order: ";
    for (auto i = 0; i < order.size(); i++) {
        std::cout << order.at(i)->getId() << "; ";
    }
    std::cout << std::endl;

    /*for(auto& node  : order) {
        rhoMapping[node->getPriority()] = std::vector<int>(d);
    }*/
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

void ProgressMeasuresAlgo::lift(const Node &v, std::unordered_map<int, ProgressMeasure>& rhoMapping, const ParityGame &parityGame) {
    auto successors = v.getSuccessors();
    std::vector<ProgressMeasure> progMeasures;
    for (auto w : successors) {
        progMeasures.push_back(Prog(rhoMapping, v, *w, parityGame));
    }
    if(v.isEven()) {
        ProgressMeasure minElement = *std::min_element(progMeasures.begin(), progMeasures.end());
        auto updatedProgressMeasure = std::max(rhoMapping.at(v.getId()), minElement);
        rhoMapping[v.getId()] = updatedProgressMeasure;

    } else { // v is odd
        ProgressMeasure maxElement = *std::max_element(progMeasures.begin(), progMeasures.end());

        auto updatedProgressMeasure = std::max(rhoMapping.at(v.getId()), maxElement);
        rhoMapping[v.getId()] = updatedProgressMeasure;
    }

}
