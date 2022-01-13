//
// Created by Tijs Hoeijmakers on 12/01/2022.
//

#include "DataPrinter.h"
#include "ProgressMeasuresAlgo.h"
#include "NaturalSort.h"
#include "Parser.h"
#include "Node.h"
#include "TextTable.h"
#include <iostream>
#include <filesystem>



std::string DataPrinter::getFileName(const std::string &filePath) {
    int lastSlashLocation = 0;
    int nameLength = 0;

    for (size_t i = filePath.size() - 1; i >= 0; i--) {
        if (filePath[i] == '/') {
            lastSlashLocation = i;
            nameLength = filePath.size() - 1 - lastSlashLocation;
            break;
        }
    }

    return filePath.substr(lastSlashLocation + 1, nameLength);
}

std::string DataPrinter::ReplaceAll(std::string str, const std::string &from, const std::string &to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}




void DataPrinter::printTablesTerminalOutput(std::string folderPath) {

    std::vector<std::string> parityGames;

    for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(folderPath)) {
        std::string fileLocation = dirEntry.path().generic_string();

        if (fileLocation.substr(fileLocation.size() - 3, 3) == ".gm") {
            parityGames.push_back(fileLocation);
        }
    }

    std::sort(parityGames.begin(), parityGames.end(), SI::natural::compare<std::string>);


    std::cout << std::endl;
    std::cout << "%=====" << "====" << std::endl;


    std::vector<std::string> timingLine1;
    timingLine1.push_back(" ");
    std::vector<std::string> timingLine2;
    timingLine2.push_back("Input Order");

    std::vector<std::string> timingLine3;
    timingLine3.push_back("Random Order");

    std::vector<std::string> timingLine4;
    timingLine4.push_back("Worklist Order");

    std::vector<std::string> timingLine5;
    timingLine5.push_back("Improved Worklist Order");


    for (const auto &parityGameStr : parityGames) {
        std::string fileName = getFileName(parityGameStr);
        fileName = ReplaceAll(fileName, "_", "\\_");
        fileName = ReplaceAll(fileName, ".gm", "");

        timingLine1.push_back(fileName);

        ParityGame parityGame = Parser::parseParityGame(parityGameStr);

        //-------BEGIN: Input order------
        std::unordered_map<int, ProgressMeasure> rhoMappingFixedInputOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingFixedInputOrder);

        auto start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameInputOrder(parityGame, rhoMappingFixedInputOrder);
        auto end = std::chrono::high_resolution_clock::now();


        auto durationInputOrder = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double dur = (double) durationInputOrder.count() / 1000;
        std::string durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
        timingLine2.push_back(durStr);
        //-------END: Input order------


        //-------BEGIN: Random order------
        std::unordered_map<int, ProgressMeasure> rhoMappingFixedRandomOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingFixedRandomOrder);

         start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameInputOrder(parityGame, rhoMappingFixedRandomOrder);
         end = std::chrono::high_resolution_clock::now();


        auto durationRandomOrder = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        dur = (double) durationRandomOrder.count() / 1000;
        durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
        timingLine3.push_back(durStr);

        //-------END: Random order------

        //-------BEGIN: Worklist order------
        std::unordered_map<int, ProgressMeasure> rhoMappingWorkListOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingWorkListOrder);

        start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameWorkList(parityGame, rhoMappingWorkListOrder);
        end = std::chrono::high_resolution_clock::now();

        auto durationWorklist = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        dur = (double) durationWorklist.count() / 1000;
        durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
        timingLine4.push_back(durStr);

        //-------END: Worklist order------


        //-------BEGIN: Improved Worklist order------
        std::unordered_map<int, ProgressMeasure> rhoMappingImprovedWorkListOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingImprovedWorkListOrder);

        start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameImprovedWorkList(parityGame, rhoMappingImprovedWorkListOrder);
        end = std::chrono::high_resolution_clock::now();

        auto durationImprovedWorkList = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        dur = (double) durationImprovedWorkList.count() / 1000;
        durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
        timingLine5.push_back(durStr);
        //-------END: Improved Worklist order------

        std::cout << "Parity game: " << fileName  << std::endl;
        std::vector<std::vector<std::string>> lines;
        lines.push_back({" ","Input order", "Random Order", "Worklist Order", "Improved Worklist Order"});
        for(const auto& node : parityGame.getNodes()) {
            std::vector<std::string> line;
            line.push_back("Node: " + std::to_string(node->getId()) );
            line.push_back(rhoMappingFixedInputOrder[node->getId()].getStringRepresentation());
            line.push_back(rhoMappingFixedRandomOrder[node->getId()].getStringRepresentation());
            line.push_back(rhoMappingWorkListOrder[node->getId()].getStringRepresentation());
            line.push_back(rhoMappingImprovedWorkListOrder[node->getId()].getStringRepresentation());
            lines.push_back(line);
        }
        printLinesTerminalOutput(lines);


    }


    std::cout << "Performance in time"
              << "Checking the performance in time gives the following results in \\emph{milliseconds}:\\\\"
              << std::endl;
    printLinesTerminalOutput({timingLine1, timingLine2, timingLine3, timingLine4, timingLine5});




}

void
DataPrinter::printLinesTerminalOutput( std::vector<std::vector<std::string>> lines) {
    TextTable t( '-', '|', '+' );
    for(const auto& line : lines) {
        for(const auto& word : line) {
            t.add(word);
        }
        t.endOfRow();
    }
//    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    std::cout << t;

}

void
DataPrinter::fillRhoMappingForParityGame(ParityGame *parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping) {
    for (const auto &node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));
        rhoMapping[node->getId()] = zeroProgressMeasure;
    }
}

void DataPrinter::printTablesTerminalOutputSingleGame(std::string parityGamePath, DataPrinter::AlgorithmType algoType) {
    std::cout << std::endl;
    std::cout << "%=====" << "====" << std::endl;

    std::unordered_map<int, ProgressMeasure> rhoMapping;
    ParityGame parityGame = Parser::parseParityGame(parityGamePath);
    std::string fileName = getFileName(parityGamePath);

    fillRhoMappingForParityGame(&parityGame, rhoMapping);

    std::string algorithmType = "";

    if(algoType == FixedInputOrder) {
        algorithmType = "FixedInputOrder";
        std::unordered_map<int, ProgressMeasure> rhoMappingFixedInputOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingFixedInputOrder);

        auto start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameInputOrder(parityGame, rhoMappingFixedInputOrder);
        auto end = std::chrono::high_resolution_clock::now();


        auto durationInputOrder = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double dur = (double) durationInputOrder.count() / 1000;
        std::string durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
    } else if(algoType == FixedRandomOrder) {
        algorithmType = "FixedRandomOrder";
        std::unordered_map<int, ProgressMeasure> rhoMappingFixedRandomOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingFixedRandomOrder);

        auto start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameInputOrder(parityGame, rhoMappingFixedRandomOrder);
        auto end = std::chrono::high_resolution_clock::now();


        auto durationRandomOrder = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double dur = (double) durationRandomOrder.count() / 1000;
        std::string durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
    } else if(algoType == Worklist) {
        algorithmType = "Worklist";
        std::unordered_map<int, ProgressMeasure> rhoMappingWorkListOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingWorkListOrder);

        auto start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameWorkList(parityGame, rhoMappingWorkListOrder);
        auto end = std::chrono::high_resolution_clock::now();

        auto durationWorklist = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double dur = (double) durationWorklist.count() / 1000;
        std::string durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);

    } else {
        algorithmType = "ImprovedWorkList";
        std::unordered_map<int, ProgressMeasure> rhoMappingImprovedWorkListOrder;
        fillRhoMappingForParityGame(&parityGame, rhoMappingImprovedWorkListOrder);

        auto start = std::chrono::high_resolution_clock::now();
        ProgressMeasuresAlgo::solveParityGameImprovedWorkList(parityGame, rhoMappingImprovedWorkListOrder);
        auto end = std::chrono::high_resolution_clock::now();

        auto durationImprovedWorkList = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        double dur = (double) durationImprovedWorkList.count() / 1000;
        std::string durStr = std::to_string(dur);
        durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
    }

    std::cout << "Parity game: " << fileName  << std::endl;
    std::vector<std::vector<std::string>> lines;
    lines.push_back({" ",algorithmType});
    for(const auto& node : parityGame.getNodes()) {
        std::vector<std::string> line;
        line.push_back("Node: " + std::to_string(node->getId()) );
        line.push_back(rhoMapping[node->getId()].getStringRepresentation());
        lines.push_back(line);
    }
    printLinesTerminalOutput(lines);

}

//void DataPrinter::printTablesTerminalOutputSingleGame(std::string parityGamePath) {
//
//    std::cout << std::endl;
//    std::cout << "%=====" << "====" << std::endl;
//
//
//    std::vector<std::string> timingLine1;
//    timingLine1.push_back(" ");
//    std::vector<std::string> timingLine2;
//    timingLine2.push_back("Input Order");
//
//    std::vector<std::string> timingLine3;
//    timingLine3.push_back("Random Order");
//
//    std::vector<std::string> timingLine4;
//    timingLine4.push_back("Worklist Order");
//
//    std::vector<std::string> timingLine5;
//    timingLine5.push_back("Improved Worklist Order");
//
//
//    std::string fileName = getFileName(parityGamePath);
//    fileName = ReplaceAll(fileName, "_", "\\_");
//    fileName = ReplaceAll(fileName, ".gm", "");
//
//    timingLine1.push_back(fileName);
//
//    ParityGame parityGame = Parser::parseParityGame(parityGamePath);
//
//    //-------BEGIN: Input order------
//    std::unordered_map<int, ProgressMeasure> rhoMappingFixedInputOrder;
//    fillRhoMappingForParityGame(&parityGame, rhoMappingFixedInputOrder);
//
//    auto start = std::chrono::high_resolution_clock::now();
//    ProgressMeasuresAlgo::solveParityGameInputOrder(parityGame, rhoMappingFixedInputOrder);
//    auto end = std::chrono::high_resolution_clock::now();
//
//
//    auto durationInputOrder = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    double dur = (double) durationInputOrder.count() / 1000;
//    std::string durStr = std::to_string(dur);
//    durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
//    timingLine2.push_back(durStr);
//    //-------END: Input order------
//
//
//    //-------BEGIN: Random order------
//    std::unordered_map<int, ProgressMeasure> rhoMappingFixedRandomOrder;
//    fillRhoMappingForParityGame(&parityGame, rhoMappingFixedRandomOrder);
//
//    start = std::chrono::high_resolution_clock::now();
//    ProgressMeasuresAlgo::solveParityGameInputOrder(parityGame, rhoMappingFixedRandomOrder);
//    end = std::chrono::high_resolution_clock::now();
//
//
//    auto durationRandomOrder = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    dur = (double) durationRandomOrder.count() / 1000;
//    durStr = std::to_string(dur);
//    durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
//    timingLine3.push_back(durStr);
//
//    //-------END: Random order------
//
//    //-------BEGIN: Worklist order------
//    std::unordered_map<int, ProgressMeasure> rhoMappingWorkListOrder;
//    fillRhoMappingForParityGame(&parityGame, rhoMappingWorkListOrder);
//
//    start = std::chrono::high_resolution_clock::now();
//    ProgressMeasuresAlgo::solveParityGameWorkList(parityGame, rhoMappingWorkListOrder);
//    end = std::chrono::high_resolution_clock::now();
//
//    auto durationWorklist = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    dur = (double) durationWorklist.count() / 1000;
//    durStr = std::to_string(dur);
//    durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
//    timingLine4.push_back(durStr);
//
//    //-------END: Worklist order------
//
//
//    //-------BEGIN: Improved Worklist order------
//    std::unordered_map<int, ProgressMeasure> rhoMappingImprovedWorkListOrder;
//    fillRhoMappingForParityGame(&parityGame, rhoMappingImprovedWorkListOrder);
//
//    start = std::chrono::high_resolution_clock::now();
//    ProgressMeasuresAlgo::solveParityGameImprovedWorkList(parityGame, rhoMappingImprovedWorkListOrder);
//    end = std::chrono::high_resolution_clock::now();
//
//    auto durationImprovedWorkList = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    dur = (double) durationImprovedWorkList.count() / 1000;
//    durStr = std::to_string(dur);
//    durStr.erase(durStr.find_last_not_of('0') + 1, std::string::npos);
//    timingLine5.push_back(durStr);
//    //-------END: Improved Worklist order------
//
//    std::cout << "Parity game: " << fileName  << std::endl;
//    std::vector<std::vector<std::string>> lines;
//    lines.push_back({" ","Input order", "Random Order", "Worklist Order", "Improved Worklist Order"});
//    for(const auto& node : parityGame.getNodes()) {
//        std::vector<std::string> line;
//        line.push_back("Node: " + std::to_string(node->getId()) );
//        line.push_back(rhoMappingFixedInputOrder[node->getId()].getStringRepresentation());
//        line.push_back(rhoMappingFixedRandomOrder[node->getId()].getStringRepresentation());
//        line.push_back(rhoMappingWorkListOrder[node->getId()].getStringRepresentation());
//        line.push_back(rhoMappingImprovedWorkListOrder[node->getId()].getStringRepresentation());
//        lines.push_back(line);
//    }
//    printLinesTerminalOutput(lines);
//
//    std::cout << "Performance in time"
//              << "Checking the performance in time gives the following results in \\emph{milliseconds}:\\\\"
//              << std::endl;
//    printLinesTerminalOutput({timingLine1, timingLine2, timingLine3, timingLine4, timingLine5});
//
//}
