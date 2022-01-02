//
// Created by tijsh on 1-1-2022.
//

#ifndef PARITYGAMESOLVER_PARSER_H
#define PARITYGAMESOLVER_PARSER_H

#include "ParityGame.h"
#include <string>
#include <vector>

class Parser {
public:
    static ParityGame parseParityGame(const std::string& filePath);

private:
    static std::vector<int> commaSeparateString(const std::string& str);

};


#endif //PARITYGAMESOLVER_PARSER_H
