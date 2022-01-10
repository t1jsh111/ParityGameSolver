#include <iostream>
#include <string>

#include "Parser.h"
#include "ParityGame.h"
#include "Node.h"
#include "ProgressMeasuresAlgo.h"




int main() {
    //std::string filePath = "resources/dining_games/dining_11.plato_infinitely_often_can_eat.gm";
    //std::string filePath = "resources/ccp_games/german_linear_5.invariantly_eventually_fair_shared_access.gm";
    std::string filePath = "resources/manual/Lots_of_single_selfloops.gm";

    ParityGame parityGame = Parser::parseParityGame(filePath);
    auto vec = parityGame.getNodes();
    auto node = parityGame.getNodeById(1);
    node.printSuccessors();
    std::cout << "id: " << node.getId() << " priority: " << node.getPriority() << " owner: " << node.getOwner() << std::endl;

    std::cout << "d value: "  << parityGame.getDValue() << std::endl;

    std::unordered_map<int, ProgressMeasure> rhoMapping;
    for(const auto& node : parityGame.getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(&parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame.getDValue()));
        rhoMapping[node->getId()] = zeroProgressMeasure;
    }


    ProgressMeasuresAlgo::solveParityGame(parityGame, rhoMapping);

    std::cout << "----rho mapping1:----" << std::endl;
    for(const auto& el  : rhoMapping) {
        std::cout << "node " << el.first << " is: ";
        el.second.print();
        std::cout << std::endl;
    }


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

    std::unordered_map<int, ProgressMeasure> rhoMapping4;
    for(const auto& node : parityGame.getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(&parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame.getDValue()));
        rhoMapping4[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameAlternativeWorkList(parityGame, rhoMapping4);

    std::cout << "----rho mapping4:----" << std::endl;
    for(const auto& el  : rhoMapping4) {
        std::cout << "node " << el.first << " is: ";
        el.second.print();
        std::cout << std::endl;
    }

    return 0;
}
