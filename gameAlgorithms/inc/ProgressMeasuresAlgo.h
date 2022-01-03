//
// Created by tijsh on 2-1-2022.
//

#ifndef PARITYGAMESOLVER_PROGRESSMEASURESALGO_H
#define PARITYGAMESOLVER_PROGRESSMEASURESALGO_H

#include "ParityGame.h"

class ProgressMeasuresAlgo {
public:
    static void solveParityGame(const ParityGame& parityGame );
private:
    static std::vector<int> Prog(const std::unordered_map<int, std::vector<int>>& rhoMapping, const Node& v, const Node& w, const ParityGame &parityGame);
    static void lift(const Node& v, std::unordered_map<int, std::vector<int>>& rhoMapping);
};


#endif //PARITYGAMESOLVER_PROGRESSMEASURESALGO_H
