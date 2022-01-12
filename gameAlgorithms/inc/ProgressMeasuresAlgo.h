//
// Created by tijsh on 2-1-2022.
//

#ifndef PARITYGAMESOLVER_PROGRESSMEASURESALGO_H
#define PARITYGAMESOLVER_PROGRESSMEASURESALGO_H

#include "ParityGame.h"
#include "Orderer.h"
#include "ProgressMeasure.h"


class ProgressMeasuresAlgo {
public:
    static void solveParityGameInputOrder(ParityGame& parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping);


    static void solveParityGameWorkList(ParityGame& parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping);
    static void solveParityGameImprovedWorkList(ParityGame& parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping);

    static ProgressMeasure Prog(const std::unordered_map<int, ProgressMeasure>& rhoMapping, const Node& v, const Node& w, const ParityGame &parityGame);
    static bool lift(const Node& v, std::unordered_map<int, ProgressMeasure>& rhoMapping, const ParityGame &parityGame);
    static bool improvedLift(const Node& v, std::unordered_map<int, ProgressMeasure>& rhoMapping, const ParityGame &parityGame);
    static void printVectorElements(const std::vector<std::shared_ptr<Node>> nodes);


private:
    static void solveParityGameUsingWorkList(ParityGame& parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping, Orderer& workList);
    static void solveParityGameForOrder(ParityGame& parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping,  std::vector<std::shared_ptr<Node>> order);
};


#endif //PARITYGAMESOLVER_PROGRESSMEASURESALGO_H
