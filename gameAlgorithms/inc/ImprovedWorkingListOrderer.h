//
// Created by Tijs Hoeijmakers on 05/01/2022.
//

#ifndef PARITYGAMESOLVER_IMPROVEDWORKINGLISTORDERER_H
#define PARITYGAMESOLVER_IMPROVEDWORKINGLISTORDERER_H

#include <unordered_map>
#include <memory>
#include <queue>
#include "Node.h"
#include "Orderer.h"

class ImprovedWorkingListOrderer : public Orderer{
public:
    void addNode(std::shared_ptr<Node> node) override;
    void addNode(std::shared_ptr<Node> node, bool wasPredecessorOfUpdate);

    std::shared_ptr<Node> popFront() override;

    bool isEmpty() const;
private:
    std::unordered_map<std::shared_ptr<Node>, bool> needsUpdate;

    std::queue<std::shared_ptr<Node>> level1;
    std::queue<std::shared_ptr<Node>> level2; // depends on updated node, and is square or depends on update and is diamond with single edge
    std::queue<std::shared_ptr<Node>> level3;
    std::queue<std::shared_ptr<Node>> level5;
    std::queue<std::shared_ptr<Node>> level4;
    std::queue<std::shared_ptr<Node>> level6;
    std::queue<std::shared_ptr<Node>> level7;

    std::vector<std::queue<std::shared_ptr<Node>>*> queues = {&level1, &level2,
                                                              &level3, &level4, &level5,
                                                              &level6, &level7};

    int numberOfUpdateNodes = 0;

};


#endif //PARITYGAMESOLVER_IMPROVEDWORKINGLISTORDERER_H
