//
// Created by Tijs Hoeijmakers on 12/01/2022.
//

#ifndef PARITYGAMESOLVER_DATAPRINTER_H
#define PARITYGAMESOLVER_DATAPRINTER_H

#include "ParityGame.h"
#include "TextTable.h"

class DataPrinter {
public:
    enum AlgorithmType {FixedInputOrder, FixedRandomOrder, Worklist, ImprovedWorklist, FixedEvenOddOrder,
            FixedDiamondSquareOrder, FixedPriorityOrder, FixedEvenOddPriorityOrder, FixedDiamondSquarePriorityOrder};

    void printTablesTerminalOutput(std::string folderPath, bool printRhoMapping, int iterations);
    void printTablesFileOutput(std::string folderPath);
    void printTablesTerminalOutputSingleGame(std::string parityGamePath, AlgorithmType algoType,bool printRhoMapping, bool even, bool diamond, bool high);
    void printTablesTerminalOutputOnlyWorklist(std::string folderPath, bool printRhoMapping);
private:



    std::string getFileName(const std::string& filePath);
    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

    void printLinesTerminalOutput(std::vector<std::vector<std::string>> lines);
    TextTable printLinesFileOutput(std::vector<std::vector<std::string>> lines);


    void fillRhoMappingForParityGame(ParityGame* parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping);
    void fillLineForOrder(std::string orderType, std::vector<std::string> line,  ParityGame &parityGameStr);

//    bool compareNat(const std::string& a, const std::string& b);
};


#endif //PARITYGAMESOLVER_DATAPRINTER_H
