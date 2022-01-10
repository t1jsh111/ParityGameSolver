//
// Created by Tijs Hoeijmakers on 10/01/2022.
//

#ifndef PARITYGAMESOLVER_WORKINGLISTORDERER_H
#define PARITYGAMESOLVER_WORKINGLISTORDERER_H
#include <unordered_map>
#include <memory>
#include <queue>
#include "Node.h"
#include "Orderer.h"

class WorkingListOrderer : public Orderer {
public:
    void addNode(std::shared_ptr<Node> node) override;

    std::shared_ptr<Node> popFront() override;

    bool isEmpty() const override;

private:
    std::queue<std::shared_ptr<Node>> workingList;
};


#endif //PARITYGAMESOLVER_WORKINGLISTORDERER_H
