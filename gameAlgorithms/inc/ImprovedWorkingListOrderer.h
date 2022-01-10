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
    std::queue<std::shared_ptr<Node>> importantUpdate; // depends on updated node, and is square or depends on update and is diamond with single edge
    std::queue<std::shared_ptr<Node>> squareOddWithoutSelfloop;
    std::queue<std::shared_ptr<Node>> squareEven;
    std::queue<std::shared_ptr<Node>> diamondMultiEdgeUpdate;

    std::queue<std::shared_ptr<Node>> remainingDiamondSingleEdge;
    std::queue<std::shared_ptr<Node>> diamondMultiEdgeOdd;
    std::queue<std::shared_ptr<Node>> diamondMultiEdgeEven;

    std::vector<std::queue<std::shared_ptr<Node>>*> queues = {&level1, &squareOddWithoutSelfloop,
                                                              &importantUpdate, &squareEven, &diamondMultiEdgeUpdate,
                                                              &remainingDiamondSingleEdge, &diamondMultiEdgeOdd, &diamondMultiEdgeEven};

    int numberOfUpdateNodes = 0;

};


#endif //PARITYGAMESOLVER_IMPROVEDWORKINGLISTORDERER_H
