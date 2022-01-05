//
// Created by tijsh on 1-1-2022.
//

#include "Parser.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <limits>
#include <sstream>
#include "Node.h"


ParityGame Parser::parseParityGame(const std::string &filePath) {

    std::ifstream autFile(filePath);

    if (!autFile.is_open()) {
        throw std::runtime_error("Could not open the provided file. File path probably invalid...");
    }


    std::string currentWord;
    autFile >> currentWord;
    // The first word of a .aut file should always contain des
    if (currentWord != "parity") {
        throw std::runtime_error("First word is not parity");
    }

    autFile >> currentWord; // currentWord gets assigned the number of highest vertex identifier.
    int highestIdentifier = std::stoi(currentWord);

    ParityGame parityGame(highestIdentifier);

    // create node objects..
    while(autFile >> currentWord) {
        int nodeIdentifier = std::stoi(currentWord);

        autFile >> currentWord;
        int priority = std::stoi(currentWord);

        autFile >> currentWord;
        bool owner = std::stoi(currentWord);

        parityGame.addNode(std::make_shared<Node>(nodeIdentifier, priority, owner));

        // ignore the rest of the line...
        autFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    std::ifstream fileStream(filePath);

    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open the provided file for the 2nd time");
    }

    // ignore first line since header has already been handled...
    fileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(fileStream >> currentWord) {

        int nodeIdentifier = std::stoi(currentWord);
        auto node = parityGame.getNode(nodeIdentifier);

        fileStream >> currentWord;
        int priority = std::stoi(currentWord);

        fileStream >> currentWord;
        bool owner = std::stoi(currentWord);

        // Form vector of successor nodes
        fileStream >> currentWord;
        std::vector<std::shared_ptr<Node>> successorNodes;

        auto successorIdentifiers = commaSeparateString(currentWord);
        for(int successorIdentifier : successorIdentifiers) {
            auto successorNode = parityGame.getNode(successorIdentifier);
            successorNodes.push_back(successorNode);
        }

        // There is a label
        if(currentWord[currentWord.length()-1] != ';') {
            fileStream >> currentWord;
            std::string nodeName = currentWord.substr(1, currentWord.size()-2);
            node->setNodeName(nodeName);
        }
        node->setSuccessors(successorNodes);
//        // Last element is node name
//        if(currentWord[0] == '\"') {
//            std::string nodeName = currentWord.substr(1, currentWord.size()-2);
//        } else { // last element is a successor
//            int successorIdentifier = std::stoi(currentWord.substr(0, currentWord.size()-1));
//            auto successorNode = parityGame.getNode(successorIdentifier);
//            successorNodes.push_back(successorNode);
//        }




    }
    return parityGame;
}


std::vector<int> Parser::commaSeparateString(const std::string& str) {
    std::vector<int> vect;

    std::stringstream ss(str);

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }
    return vect;
}
