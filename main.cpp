#include <iostream>
#include <string>

#include "Parser.h"
#include "ParityGame.h"
#include "Node.h"

#include "ProgressMeasuresAlgo.h"





int main() {

    std::string filePath = "resources/manual/slide_example.gm";

    ParityGame parityGame = Parser::parseParityGame(filePath);


    std::unordered_map<int, ProgressMeasure> rhoMapping2;
    for(const auto& node : parityGame.getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(&parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame.getDValue()));
        rhoMapping2[node->getId()] = zeroProgressMeasure;
    }


    ProgressMeasuresAlgo::solveParityGameWorkList(parityGame, rhoMapping2);

    std::cout << "----rho mapping2:----" << std::endl;
    for(const auto& el  : rhoMapping2) {
        std::cout << "node " << el.first << " is: ";
        el.second.print();
        std::cout << std::endl;
    }

    std::unordered_map<int, ProgressMeasure> rhoMapping3;
    for(const auto& node : parityGame.getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(&parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame.getDValue()));
        rhoMapping3[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameImprovedWorkList(parityGame, rhoMapping3);

    std::cout << "----rho mapping3:----" << std::endl;
    for(const auto& el  : rhoMapping3) {
        std::cout << "node " << el.first << " is: ";
        el.second.print();
        std::cout << std::endl;
    }

    return 0;

}
