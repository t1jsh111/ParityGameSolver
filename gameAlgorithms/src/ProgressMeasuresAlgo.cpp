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
    printVectorElements(order);

    /*std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(order.begin(), order.end(), rng); // Random order

    std::cout << "Random order: ";
    printVectorElements(order);*/

    /*order = evenOddPriorityOrder(order, false); // Odd first order

    std::cout << "Odd first order: ";
    printVectorElements(order);*/

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

//    bool updated = false;
//
//    if(v.isEven()) { // v is even
//        for (int i = 0; i < parityGame.getDValue(); i++) { // Loop over vectors from highest to lowest significance
//            // Temporarily store int values of same significance in single vector compare
//            std::vector<int> compare;
//            for (ProgressMeasure j : progMeasures) {
//                compare.push_back(j.getProgressMeasureVec().at(i));
//            }
//
//            // Get minimum value
//            auto min = std::min_element(compare.begin(), compare.end());
//
//            // Eliminate candidate vectors with value higher than minimum
//            std::vector<ProgressMeasure> temp;
//            for (ProgressMeasure j : progMeasures) {
//                if (j.getProgressMeasureVec().at(i) == *min.base()) { // NOTE: not certain yet that min.base gives the minimum value.
//                    temp.push_back(j);
//                }
//            }
//            progVectors = temp;
//
//            // Prematurely break when only one candidate remains
//            if (progVectors.size() == 1) {
//                rhoMapping[v.getId()] = progVectors.at(0);
//                updated = true;
//                break;
//            }
//        }
//    } else { // v is odd
//        bool top = false;
//
//        // Check if there is a top in progVectors
//        /*for (std::vector<int> i : progVectors) {
//            if (there is a top) {
//                rhoMapping[v.getId()] = i;
//                updated = true;
//                top = true;
//                break;
//            }
//        }*/
//
//        for (int i = 0; i < parityGame.getDValue() && !top; i++) { // Loop over vectors from highest to lowest significance
//            // Temporarily store int values of same significance in single vector compare
//            std::vector<int> compare;
//            for (std::vector<int> j : progVectors) {
//                compare.push_back(j.at(i));
//            }
//
//            // Get maximum value
//            auto max = std::max_element(compare.begin(), compare.end());
//
//            // Eliminate candidate vectors with value lower than maximum
//            std::vector<std::vector<int>> temp;
//            for (std::vector<int> j : progVectors) {
//                if (j.at(i) == *max.base()) { // NOTE: not certain yet that max.base gives the maximum value.
//                    temp.push_back(j);
//                }
//            }
//            progVectors = temp;
//
//            // Prematurely break when only one candidate remains
//            if (progVectors.size() == 1) {
//                rhoMapping[v.getId()] = progVectors.at(0);
//                updated = true;
//                break;
//            }
//        }
//    }
//
//    if (!updated) {
//        rhoMapping[v.getId()] = progVectors.at(0);
//    }
}

void ProgressMeasuresAlgo::printVectorElements(const std::vector<std::shared_ptr<Node>> nodes) {
    for (auto i = 0; i < nodes.size(); i++) {
        std::cout << nodes.at(i)->getId() << "; ";
    }
    std::cout << std::endl;
}

std::vector<std::shared_ptr<Node>> ProgressMeasuresAlgo::evenOddPriorityOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even) {
    std::vector<std::shared_ptr<Node>> e;
    std::vector<std::shared_ptr<Node>> o;
    for (auto n : nodes) {
        if (n->getPriority() % 2 == 0) {
            e.push_back(n);
        } else {
            o.push_back(n);
        }
    }
    std::vector<std::shared_ptr<Node>> order;
    if (even) { // Even first
        order.insert(order.begin(), e.begin(), e.end());
        order.insert(order.end(), o.begin(), o.end());
    } else { // Odd first
        order.insert(order.begin(), o.begin(), o.end());
        order.insert(order.end(), e.begin(), e.end());
    }
    return order;
}

std::vector<std::shared_ptr<Node>> ProgressMeasuresAlgo::evenOddOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even) {
    std::vector<std::shared_ptr<Node>> e;
    std::vector<std::shared_ptr<Node>> o;
    for (auto n : nodes) {
        if (n->isEven()) {
            e.push_back(n);
        } else {
            o.push_back(n);
        }
    }
    std::vector<std::shared_ptr<Node>> order;
    if (even) { // Even first
        order.insert(order.begin(), e.begin(), e.end());
        order.insert(order.end(), o.begin(), o.end());
    } else { // Odd first
        order.insert(order.begin(), o.begin(), o.end());
        order.insert(order.end(), e.begin(), e.end());
    }
    return order;
}