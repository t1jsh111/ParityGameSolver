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

void ProgressMeasuresAlgo::lift(const Node &v, std::unordered_map<int, ProgressMeasure>& rhoMapping, const ParityGame &parityGame) {
    auto successors = v.getSuccessors();
    std::vector<ProgressMeasure> progMeasures;
    for (auto w : successors) {
        progMeasures.push_back(Prog(rhoMapping, v, *w, parityGame));
    }
    bool updated = false;

    if(v.isEven()) { // v is even
        for (int i = 0; i < parityGame.getDValue(); i++) { // Loop over vectors from highest to lowest significance
            // Temporarily store int values of same significance in single vector compare
            std::vector<int> compare;
            for (ProgressMeasure j : progMeasures) {
                compare.push_back(j.getProgressMeasureVec().at(i));
            }

            // Get minimum value
            auto min = std::min_element(compare.begin(), compare.end());

            // Eliminate candidate vectors with value higher than minimum
            std::vector<ProgressMeasure> temp;
            for (ProgressMeasure j : progMeasures) {
                if (j.getProgressMeasureVec().at(i) == *min.base()) { // NOTE: not certain yet that min.base gives the minimum value.
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
