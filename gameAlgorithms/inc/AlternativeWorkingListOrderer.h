//
// Created by Tijs Hoeijmakers on 05/01/2022.
//

#ifndef PARITYGAMESOLVER_ALTERNATIVEWORKINGLISTORDERER_H
#define PARITYGAMESOLVER_ALTERNATIVEWORKINGLISTORDERER_H

#include <unordered_map>
#include <memory>
#include <queue>
#include "Node.h"
#include "ProgressMeasure.h"

class AlternativeWorkingListOrderer {
public:
    void addNodeToWorkList(std::shared_ptr<Node> node, std::unordered_map<int, ProgressMeasure>& rhoMapping, bool wasPredecessorOfUpdate = false);

    std::shared_ptr<Node> popFront();

    bool isEmpty() const;
private:
    std::unordered_map<std::shared_ptr<Node>, bool> needsUpdate;



    std::queue<std::shared_ptr<Node>> squareOddWithSelfLoop;
    std::queue<std::shared_ptr<Node>> importantUpdate; // depends on updated node, and is square or depends on update and is diamond with single edge
    std::queue<std::shared_ptr<Node>> squareOddWithoutSelfloop;
    std::queue<std::shared_ptr<Node>> squareEven;
    std::queue<std::shared_ptr<Node>> diamondMultiEdgeUpdate;

    std::queue<std::shared_ptr<Node>> diamondSingleEdge;
    std::queue<std::shared_ptr<Node>> diamondMultiEdgeEven;
    std::queue<std::shared_ptr<Node>> diamondMultiEdgeOdd;

    std::vector<std::queue<std::shared_ptr<Node>>*> queues = {&squareOddWithSelfLoop, &squareOddWithoutSelfloop,
                                                              &importantUpdate, &squareEven, &diamondMultiEdgeUpdate,
                                                              &diamondSingleEdge, &diamondMultiEdgeEven, &diamondMultiEdgeOdd};

    int numberOfUpdateNodes = 0;

};


#endif //PARITYGAMESOLVER_ALTERNATIVEWORKINGLISTORDERER_H
