//
// Created by Tijs Hoeijmakers on 12/01/2022.
//

#ifndef PARITYGAMESOLVER_DATAPRINTER_H
#define PARITYGAMESOLVER_DATAPRINTER_H

#include "ParityGame.h"

class DataPrinter {
public:
    enum AlgorithmType {FixedInputOrder, FixedRandomOrder, Worklist, ImprovedWorklist};


    void printTablesTerminalOutput(std::string folderPath);
    void printTablesTerminalOutputSingleGame(std::string parityGamePath, AlgorithmType algoType);
private:



    std::string getFileName(const std::string& filePath);
    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

    void printLinesTerminalOutput(std::vector<std::vector<std::string>> lines);


    void fillRhoMappingForParityGame(ParityGame* parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping);
    void fillLineForOrder(std::string orderType, std::vector<std::string> line,  ParityGame &parityGameStr);

//    bool compareNat(const std::string& a, const std::string& b);
};


#endif //PARITYGAMESOLVER_DATAPRINTER_H
