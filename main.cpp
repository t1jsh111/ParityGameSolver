#include <iostream>
#include <string>

#include "Parser.h"
#include "ParityGame.h"
#include "Node.h"
#include "DataPrinter.h"
#include "ProgressMeasuresAlgo.h"


std::string getInput(std::unordered_set<std::string> recognizedCommands) {
    std::string inputWord;
    while(std::cin >> inputWord) {
        bool inputRecognized = recognizedCommands.find(inputWord) != recognizedCommands.end();

        if(inputRecognized) {
            return inputWord;
        } else {
            std::cout << "input " << inputWord << " is not valid input please try again " << std::endl;
        }

    }
    return inputWord;
}

void printMenu() {
    std::cout << "Welcome to the ParityGameSolver!" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Press 1 to compute all information of a folder containing paritygames and print in Console format" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Press 3 to compute for a specific parity game using a specific algorithm" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Press 3 to compute for a specific parity game using a specific algorithm" << std::endl;
    std::cout << "-----" << std::endl;
}


int main() {
    std::cout << "__________              .__  __           \n"
                 "\\______   \\_____ _______|__|/  |_ ___.__. \n"
                 " |     ___/\\__  \\\\_  __ \\  \\   __<   |  | \n"
                 " |    |     / __ \\|  | \\/  ||  |  \\___  | \n"
                 " |____|    (____  /__|  |__||__|  / ____| \n"
                 "                \\/                \\/      \n"
                 "  ________                                \n"
                 " /  _____/_____    _____   ____           \n"
                 "/   \\  ___\\__  \\  /     \\_/ __ \\          \n"
                 "\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/          \n"
                 " \\______  (____  /__|_|  /\\___  >         \n"
                 "        \\/     \\/      \\/     \\/          \n"
                 "  _________      .__                      \n"
                 " /   _____/ ____ |  |___  __ ___________  \n"
                 " \\_____  \\ /  _ \\|  |\\  \\/ // __ \\_  __ \\ \n"
                 " /        (  <_> )  |_\\   /\\  ___/|  | \\/ \n"
                 "/_______  /\\____/|____/\\_/  \\___  >__|    \n"
                 "        \\/                      \\/        " << std::endl;
    std::cout << "By Tijs H. and Milan H." << std::endl;
    DataPrinter dataPrinter;

    while(true) {
        printMenu();


        std::string inputWord = getInput({"1", "2", "3"});

        if (inputWord == "1") {
            std::cout << "drag and drop folder to console / provide folder path and press enter" << std::endl;
            std::cin >> inputWord;
            try {
                dataPrinter.printTablesTerminalOutput(inputWord);
            } catch (const std::exception &e) {
                std::cout << "it looks like the folder contains invalid paritygame" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }

        } else if (inputWord == "2") {
            std::cout << "drag and drop file to console / provide file path and press enter" << std::endl;
            std::cin >> inputWord;
            try {
                dataPrinter.printTablesTerminalOutputSingleGame(inputWord, DataPrinter::FixedInputOrder);
            } catch (const std::exception &e) {
                std::cout << "it looks like the folder contains invalid paritygame" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }
        } else if (inputWord == "3") {
            std::cout << "drag and drop parity game system to console / provide file path and press enter" << std::endl;
            std::cin >> inputWord;
            try {
//                ParityGame parityGame = Parser::parseParityGame(inputWord);
//
//                enterFormula:
//
//                std::cout << "drag and drop the formula to console / provide file path and press enter" << std::endl;
//                std::cin >> inputWord;
//                try {
//                    std::cout << "press i for executing the algorithm using fixed input order: " << std::endl;
//                    std::cout << "press r for executing the algorithm using fixed random input order: " << std::endl;
//                    std::cout << "press w for executing the algorithm using worklist: " << std::endl;
//                    std::cout << "press iw for executing the algorithm using improved worklist: " << std::endl;
//                    inputWord = getInput({"i", "r", "w", "iw"});
//                    if (inputWord == "i") {
//                        dataPrinter.printInformationSingleFormulaAndLts(*form, lts, DataPrinter::Naive);
//                    } else if (inputWord == "r") {
//                        dataPrinter.printInformationSingleFormulaAndLts(*form, lts, DataPrinter::Emerson);
//                    } else if(inputWord == "w") {
//
//                    } else if(inputWord == "iw") {
//
//                    }
//                    else {
//                        throw std::runtime_error("This should not be reachable. Bug in code!!");
//                    }
//
//
//                } catch (const std::exception &e) {
//                    std::cout << "it looks like the formula is not properly formatted" << std::endl;
//                    std::cout << e.what() << std::endl;
//                    std::cout << "Please try again";
//
//                    // This is really bad practice, but okay for a functional interface for now...
//                    goto enterFormula;
//                }

            } catch (const std::exception &e) {
                std::cout << "it looks like the lts is not properly formatted" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }

        } else {
            throw std::runtime_error("This should not be reachable. Bug in code!!");
        }
    }


    return 0;




//    //std::string filePath = "resources/dining_games/dining_11.plato_infinitely_often_can_eat.gm";
//    //std::string filePath = "resources/ccp_games/german_linear_5.invariantly_eventually_fair_shared_access.gm";
//    std::string filePath = "resources/manual/slide_example.gm";
//
//    ParityGame parityGame = Parser::parseParityGame(filePath);
//    auto vec = parityGame.getNodes();
//    auto node = parityGame.getNodeById(1);
//    node.printSuccessors();
//    std::cout << "id: " << node.getId() << " priority: " << node.getPriority() << " owner: " << node.getOwner() << std::endl;
//
//    std::cout << "d value: "  << parityGame.getDValue() << std::endl;
//
//    std::unordered_map<int, ProgressMeasure> rhoMapping;
//    for(const auto& node : parityGame.getNodes()) {
//        auto zeroProgressMeasure = ProgressMeasure(&parityGame);
//        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame.getDValue()));
//        rhoMapping[node->getId()] = zeroProgressMeasure;
//    }
//
//
//    ProgressMeasuresAlgo::solveParityGameInputOrder(parityGame, rhoMapping);
//
//    std::cout << "----rho mapping1:----" << std::endl;
//    for(const auto& el  : rhoMapping) {
//        std::cout << "node " << el.first << " is: ";
//        el.second.print();
//        std::cout << std::endl;
//    }
//
//
//    std::unordered_map<int, ProgressMeasure> rhoMapping2;
//    for(const auto& node : parityGame.getNodes()) {
//        auto zeroProgressMeasure = ProgressMeasure(&parityGame);
//        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame.getDValue()));
//        rhoMapping2[node->getId()] = zeroProgressMeasure;
//    }
//
//
//
//    ProgressMeasuresAlgo::solveParityGameWorkList(parityGame, rhoMapping2);
//
//    std::cout << "----rho mapping2:----" << std::endl;
//    for(const auto& el  : rhoMapping2) {
//        std::cout << "node " << el.first << " is: ";
//        el.second.print();
//        std::cout << std::endl;
//    }
//
//    std::unordered_map<int, ProgressMeasure> rhoMapping3;
//    for(const auto& node : parityGame.getNodes()) {
//        auto zeroProgressMeasure = ProgressMeasure(&parityGame);
//        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame.getDValue()));
//        rhoMapping3[node->getId()] = zeroProgressMeasure;
//    }
//
//    ProgressMeasuresAlgo::solveParityGameImprovedWorkList(parityGame, rhoMapping3);
//
//    std::cout << "----rho mapping3:----" << std::endl;
//    for(const auto& el  : rhoMapping3) {
//        std::cout << "node " << el.first << " is: ";
//        el.second.print();
//        std::cout << std::endl;
//    }
//
//    return 0;
}
