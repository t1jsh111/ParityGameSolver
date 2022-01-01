//
// Created by tijsh on 1-1-2022.
//

#include "Parser.h"

#include <iostream>
#include <fstream>
#include <limits>
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
    while(!autFile.eof()) {
        int identifier;

        autFile >> currentWord;
        identifier = std::stoi(currentWord);
        parityGame.addNode(std::make_shared<Node>(identifier));

        // ignore the rest of the line...
        autFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    std::ifstream fileStream(filePath);

    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open the provided file for the 2nd time");
    }

    // ignore first line since header has already been handled...
    fileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(!fileStream.eof()) {
        fileStream >> currentWord;
        int nodeIdentifier = std::stoi(currentWord);
        auto node = parityGame.getNode(nodeIdentifier);

        fileStream >> currentWord;
        int priority = std::stoi(currentWord);

        fileStream >> currentWord;
        bool owner = std::stoi(currentWord);

        // Form vector of successor nodes
        fileStream >> currentWord;
        std::vector<std::shared_ptr<Node>> successorNodes;
        while(currentWord[currentWord.length()-1] != ';') {
            int successorIdentifier = std::stoi(currentWord);
            auto successorNode = parityGame.getNode(successorIdentifier);
            successorNodes.push_back(successorNode);

            fileStream >> currentWord;
        }
        // Last element is node name
        if(currentWord[0] == '\"') {
            std::string nodeName = currentWord.substr(1, currentWord.size()-2);
        } else { // last element is a successor
            int successorIdentifier = std::stoi(currentWord.substr(0, currentWord.size()-1));
            auto successorNode = parityGame.getNode(successorIdentifier);
            successorNodes.push_back(successorNode);
        }

        node->setSpecification(priority, owner, successorNodes);

    }
    return parityGame;
}

