//
// Created by s164009 on 3-1-2022.
//

#ifndef PARITYGAMESOLVER_ORDERING_H
#define PARITYGAMESOLVER_ORDERING_H

#include "ParityGame.h"

class Ordering {
public:
    static std::vector<std::shared_ptr<Node>> randomOrder(const std::vector<std::shared_ptr<Node>> nodes);
    static std::vector<std::shared_ptr<Node>> evenOddPriorityOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even);
    static std::vector<std::shared_ptr<Node>> evenOddOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even);
    static std::vector<std::shared_ptr<Node>> highLowPriorityOrder(ParityGame parityGame, const bool highLow);
    static std::vector<std::shared_ptr<Node>> evenOddPrioHighLowPrioOrder(ParityGame parityGame, const bool even, const bool highLow);
    static std::vector<std::shared_ptr<Node>> evenOddHighLowPrioOrder(ParityGame parityGame, const bool even, const bool highLow);
};

#endif //PARITYGAMESOLVER_ORDERING_H
