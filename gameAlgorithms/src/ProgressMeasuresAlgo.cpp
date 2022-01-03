//
// Created by tijsh on 2-1-2022.
//

#include "ProgressMeasuresAlgo.h"

#include "Node.h"

#include <limits>

#include <bits/stdc++.h>

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
                    for(int i = 0; i < parityGame.getDValue(); i++) {top[i] = std::numeric_limits<int>::max();}
                    return top;
                }
            }
        }
    }
}

void ProgressMeasuresAlgo::lift(const Node &v, std::unordered_map<int, std::vector<int>> &rhoMapping, const ParityGame &parityGame) {
    auto successors = v.getSuccessors();
    std::vector<std::vector<int>> progVectors;
    for (auto w : successors) {
        progVectors.push_back(Prog(rhoMapping, v, *w, parityGame));
    }
    bool updated = false;

    if(v.isEven()) { // v is even
        for (int i = 0; i < parityGame.getDValue(); i++) { // Loop over vectors from highest to lowest significance
            // Temporarily store int values of same significance in single vector compare
            std::vector<int> compare;
            for (std::vector<int> j : progVectors) {
                compare.push_back(j.at(i));
            }

            // Get minimum value
            auto min = std::min_element(compare.begin(), compare.end());

            // Eliminate candidate vectors with value higher than minimum
            std::vector<std::vector<int>> temp;
            for (std::vector<int> j : progVectors) {
                if (j.at(i) == *min.base()) { // NOTE: not certain yet that min.base gives the minimum value.
                    temp.push_back(j);
                }
            }
            progVectors = temp;

            // Prematurely break when only one candidate remains
            if (progVectors.size() == 1) {
                rhoMapping[v.getId()] = progVectors.at(0);
                updated = true;
                break;
            }
        }
    } else { // v is odd
        bool top = false;

        // Check if there is a top in progVectors
        /*for (std::vector<int> i : progVectors) {
            if (there is a top) {
                rhoMapping[v.getId()] = i;
                updated = true;
                top = true;
                break;
            }
        }*/

        for (int i = 0; i < parityGame.getDValue() && !top; i++) { // Loop over vectors from highest to lowest significance
            // Temporarily store int values of same significance in single vector compare
            std::vector<int> compare;
            for (std::vector<int> j : progVectors) {
                compare.push_back(j.at(i));
            }

            // Get maximum value
            auto max = std::max_element(compare.begin(), compare.end());

            // Eliminate candidate vectors with value lower than maximum
            std::vector<std::vector<int>> temp;
            for (std::vector<int> j : progVectors) {
                if (j.at(i) == *max.base()) { // NOTE: not certain yet that max.base gives the maximum value.
                    temp.push_back(j);
                }
            }
            progVectors = temp;

            // Prematurely break when only one candidate remains
            if (progVectors.size() == 1) {
                rhoMapping[v.getId()] = progVectors.at(0);
                updated = true;
                break;
            }
        }
    }

    if (!updated) {
        rhoMapping[v.getId()] = progVectors.at(0);
    }
}
