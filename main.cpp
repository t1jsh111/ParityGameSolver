#include <iostream>
#include <string>

#include "Parser.h"
#include "ParityGame.h"
#include "Node.h"




int main() {
    std::string filePath = "resources/ccp_games/german_linear_2.infinite_run_no_access.gm";

    ParityGame parityGame = Parser::parseParityGame(filePath);
    std::cout << parityGame.getHighestIdentifier();
    auto node = parityGame.getNodeById(4);
    node.printSuccessors();

    return 0;
}
