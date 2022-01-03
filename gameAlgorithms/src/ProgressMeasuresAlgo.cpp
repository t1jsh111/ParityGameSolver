//
// Created by tijsh on 2-1-2022.
//

#include "ProgressMeasuresAlgo.h"

#include "Node.h"

void ProgressMeasuresAlgo::solveParityGame(const ParityGame &parityGame) {

    std::unordered_map<int, std::vector<int>> rhoMapping;
    int d = parityGame.getDValue();

    for(auto& node  : parityGame.getNodes()) {
        rhoMapping[node->getPriority()] = std::vector<int>(d);
    }


}

std::vector<int>
ProgressMeasuresAlgo::Prog(const std::unordered_map<int, std::vector<int>> &rhoMapping, const Node &v, const Node &w, const ParityGame &parityGame) {

    std::vector<int> leastVector(parityGame.getDValue());

    auto rhoForW = rhoMapping.at(w.getId());

    bool isTop = true;
    for(int i : rhoForW) {
        if(i != std::numeric_limits<int>::max()) {
            isTop = false;
            break;
        }
    }


    // Priority of v is even
    if(v.getPriority() % 2 == 0) {
        // only top >= top
        if(isTop) {
            return rhoForW;
        } else {
            for(int i = 0; i <= v.getPriority(); i++) {
                leastVector[i] = rhoForW[i];
            }
        }

    } else { // priority of v is odd
        // only top > top
        if(isTop) {
            return rhoForW;
        } else {
            for(int i = 0; i <= v.getPriority(); i++) {
                if(rhoForW[i] + 1 <= parityGame.getNumberOfVerticesWithPriority(i)) {
                    leastVector[i] = rhoForW[i] + 1;
                } else {
                    std::vector<int> top(parityGame.getDValue());
                    for(int i = 0; i < parityGame.getDValue(); i++) {top[i] = std::numeric_limits<int>::max()}
                    return top;
                }
            }
        }
    }
}

void ProgressMeasuresAlgo::lift(const Node &v, std::unordered_map<int, std::vector<int>> &rhoMapping) {
    if(v.isEven()) {
        rhoMapping[v.getId()] = std::max(rhoMapping[v])
    } else { // v is odd

    }
}
