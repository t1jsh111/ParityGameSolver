//
// Created by tijsh on 1-1-2022.
//

#ifndef PARITYGAMESOLVER_NODE_H
#define PARITYGAMESOLVER_NODE_H

#include <vector>
#include <memory>
#include <unordered_map>

class Node {
public:
//    typedef std::shared_ptr<std::unordered_map<int, Node>> Mapping;

    Node(int id);

    void setSpecification(int priority, bool owner, std::vector<std::shared_ptr<Node>> successors);

    int getId() const;
    int getPriority() const;

    bool isEven() const;
    bool isOdd() const;
    bool getOwner() const;

    std::vector<std::shared_ptr<Node>> getSuccessors() const;

    void printSuccessors() const;

private:
    int id;
    int priority;
    bool owner;
    std::vector<std::shared_ptr<Node>> successors;

};


#endif //PARITYGAMESOLVER_NODE_H
