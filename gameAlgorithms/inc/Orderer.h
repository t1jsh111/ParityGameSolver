//
// Created by Tijs Hoeijmakers on 10/01/2022.
//

#ifndef PARITYGAMESOLVER_ORDERER_H
#define PARITYGAMESOLVER_ORDERER_H

class Orderer {
public:
    virtual void addNode(std::shared_ptr<Node> node) = 0;

    virtual std::shared_ptr<Node> popFront() = 0;

    virtual bool isEmpty() const = 0;
};

#endif //PARITYGAMESOLVER_ORDERER_H
