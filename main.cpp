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
    std::cout << "Press 2 to compute for a specific parity game using a specific algorithm" << std::endl;
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


        std::string inputWord = getInput({"1", "2"});

        if (inputWord == "1") {
            std::cout << "drag and drop folder to console / provide folder path and press enter" << std::endl;
            std::cin >> inputWord;
            std::string filePath;
            filePath = inputWord;
            try {
                std::cout << "Do you want to print the final rho mappings y/n?" << std::endl;
                inputWord = getInput({"y", "n"});
                bool wantRhoMappings = inputWord == "y";
                dataPrinter.printTablesTerminalOutput(filePath, wantRhoMappings);

            } catch (const std::exception &e) {
                std::cout << "it looks like the folder contains invalid paritygame" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }

        } else if (inputWord == "2") {
            std::cout << "drag and drop file to console / provide file path and press enter" << std::endl;
            std::cin >> inputWord;
            std::string filePath;
            filePath = inputWord;
            try {
                    std::cout << "press 1 for executing the algorithm using fixed input order: " << std::endl;
                    std::cout << "press 2 for executing the algorithm using fixed random input order: " << std::endl;
                    std::cout << "press 3 for executing the algorithm using worklist: " << std::endl;
                    std::cout << "press 4 for executing the algorithm using improved worklist: " << std::endl;
                    std::string algoType = getInput({"1", "2", "3", "4"});

                    std::cout << "Do you want to print the final rho mappings y/n?" << std::endl;
                    inputWord = getInput({"y", "n"});
                    bool wantRhoMappings = inputWord == "y";


                    if (algoType == "1") {
                        dataPrinter.printTablesTerminalOutputSingleGame(filePath, DataPrinter::FixedInputOrder, wantRhoMappings);
                    } else if (algoType == "2") {
                        dataPrinter.printTablesTerminalOutputSingleGame(filePath, DataPrinter::FixedRandomOrder, wantRhoMappings);
                    } else if(algoType == "3") {
                        dataPrinter.printTablesTerminalOutputSingleGame(filePath, DataPrinter::Worklist, wantRhoMappings);
                    } else {
                        dataPrinter.printTablesTerminalOutputSingleGame(filePath, DataPrinter::ImprovedWorklist, wantRhoMappings);
                    }
            } catch (const std::exception &e) {
                std::cout << "it looks like the folder contains invalid paritygame" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }
        } else {
            throw std::runtime_error("This should not be reachable. Bug in code!!");
        }
    }


}
