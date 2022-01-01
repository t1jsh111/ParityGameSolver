//
// Created by tijsh on 1-1-2022.
//

#ifndef PARITYGAMESOLVER_PARSER_H
#define PARITYGAMESOLVER_PARSER_H

#include "ParityGame.h"
#include <string>

class Parser {
public:
    static ParityGame parseParityGame(const std::string& filePath);

private:

};


#endif //PARITYGAMESOLVER_PARSER_H
