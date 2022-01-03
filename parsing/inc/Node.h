//
// Created by tijsh on 1-1-2022.
//

#ifndef PARITYGAMESOLVER_NODE_H
#define PARITYGAMESOLVER_NODE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class Node {
public:
//    typedef std::shared_ptr<std::unordered_map<int, Node>> Mapping;

    Node(int id, int priority, bool owner);

    void setSuccessors(std::vector<std::shared_ptr<Node>> successors);

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
    std::string nodeName;
public:
    const std::string &getNodeName() const;

    void setNodeName(const std::string &nodeName);

private:
    std::vector<std::shared_ptr<Node>> successors;

};


#endif //PARITYGAMESOLVER_NODE_H
