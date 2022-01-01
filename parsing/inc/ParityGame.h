//
// Created by tijsh on 1-1-2022.
//

#ifndef PARITYGAMESOLVER_PARITYGAME_H
#define PARITYGAMESOLVER_PARITYGAME_H

#include <unordered_map>
#include <memory>

class Node;

class ParityGame {
public:
    explicit ParityGame(int highestIdentifier);

    void addNode(std::shared_ptr<Node> node);

    const Node& getNodeById(int id) const;
    std::shared_ptr<Node> getNode(int id) const;

    int getHighestIdentifier() const;

private:
    int highestIdentifier;

    std::unordered_map<int, std::shared_ptr<Node>> nodeMapping;

};


#endif //PARITYGAMESOLVER_PARITYGAME_H
