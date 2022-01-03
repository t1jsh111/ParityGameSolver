//
// Created by tijsh on 2-1-2022.
//

#ifndef PARITYGAMESOLVER_PROGRESSMEASURESALGO_H
#define PARITYGAMESOLVER_PROGRESSMEASURESALGO_H

#include "ParityGame.h"
#include "ProgressMeasure.h"


class ProgressMeasuresAlgo {
public:
    static void solveParityGame(const ParityGame& parityGame );

    static ProgressMeasure Prog(const std::unordered_map<int, ProgressMeasure>& rhoMapping, const Node& v, const Node& w, const ParityGame &parityGame);
    static void lift(const Node& v, std::unordered_map<int, ProgressMeasure>& rhoMapping, const ParityGame &parityGame);
    static void printVectorElements(const std::vector<std::shared_ptr<Node>> nodes);
    static std::vector<std::shared_ptr<Node>> evenOddPriorityOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even);
    static std::vector<std::shared_ptr<Node>> evenOddOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even);
};


#endif //PARITYGAMESOLVER_PROGRESSMEASURESALGO_H
