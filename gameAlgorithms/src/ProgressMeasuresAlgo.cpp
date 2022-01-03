//
// Created by tijsh on 2-1-2022.
//

#include "ProgressMeasuresAlgo.h"

#include "Node.h"


#include <limits>

void ProgressMeasuresAlgo::solveParityGame(const ParityGame &parityGame) {

    std::unordered_map<int, std::vector<int>> rhoMapping;
    int d = parityGame.getDValue();

    for(auto& node  : parityGame.getNodes()) {
        rhoMapping[node->getPriority()] = std::vector<int>(d);
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

void ProgressMeasuresAlgo::lift(const Node &v, std::unordered_map<int, ProgressMeasure> &rhoMapping) {
    if(v.isEven()) {
        //rhoMapping[v.getId()] = std::max(rhoMapping[v])
    } else { // v is odd

    }
}
