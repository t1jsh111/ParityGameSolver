#include <iostream>
#include <string>

#include "Parser.h"
#include "ParityGame.h"
#include "Node.h"
#include "ProgressMeasuresAlgo.h"




int main() {
    std::string filePath = "resources/ccp_games/german_linear_2.infinite_run_no_access.gm";

    ParityGame parityGame = Parser::parseParityGame(filePath);
    auto node = parityGame.getNodeById(501);
    node.printSuccessors();
    std::cout << "id: " << node.getId() << " priority: " << node.getPriority() << " owner: " << node.getOwner() << std::endl;

    std::cout << "d value: "  << parityGame.getDValue() << std::endl;

    ProgressMeasuresAlgo::solveParityGame(parityGame);

    return 0;
}
