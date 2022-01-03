//
// Created by tijsh on 1-1-2022.
//

#ifndef PARITYGAMESOLVER_PARITYGAME_H
#define PARITYGAMESOLVER_PARITYGAME_H

#include <unordered_map>
#include <memory>
#include <vector>

class Node;

class ParityGame {
public:
    explicit ParityGame(int highestIdentifier);

    void addNode(std::shared_ptr<Node> node);



    int getNumberOfVerticesWithPriority(int priority) const;

    const std::vector<std::shared_ptr<Node>>& getNodes() const;

    const Node& getNodeById(int id) const;
    std::shared_ptr<Node> getNode(int id) const;

    int getHighestIdentifier() const;

    int getDValue() const;

private:
    int highestIdentifier;

    std::unordered_map<int, std::shared_ptr<Node>> idToNodeMap;
    std::unordered_map<int, std::vector<std::shared_ptr<Node>>> priorityToNodesMap;
    std::vector<std::shared_ptr<Node>> nodes;

    int highestPriority;

};


#endif //PARITYGAMESOLVER_PARITYGAME_H
