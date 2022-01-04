#include <iostream>
#include <string>

#include "Parser.h"
#include "ParityGame.h"
#include "Node.h"
#include "ProgressMeasuresAlgo.h"




int main() {
    //std::string filePath = "resources/ccp_games/german_linear_2.infinite_run_no_access.gm";
    std::string filePath = "resources/manual/slide12_example.gm";

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

    for(const auto& el  : rhoMapping) {
        std::cout << "node " << el.first << " is: ";
        el.second.print();
        std::cout << std::endl;
    }

    return 0;
}
