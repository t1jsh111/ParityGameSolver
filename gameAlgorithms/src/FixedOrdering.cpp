//
// Created by s164009 on 3-1-2022.
//

#include "FixedOrdering.h"
#include "Node.h"

#include <random>
#include <algorithm>
#include <iostream>

std::vector<std::shared_ptr<Node>> FixedOrdering::inputOrder(const std::vector<std::shared_ptr<Node>> nodes) {
    return nodes;
}

std::vector<std::shared_ptr<Node>> FixedOrdering::randomOrder(const std::vector<std::shared_ptr<Node>> nodes) {
    std::vector<std::shared_ptr<Node>> order = nodes;
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(order.begin(), order.end(), rng);
    return order;
}

std::vector<std::shared_ptr<Node>> FixedOrdering::evenOddOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even) {
    std::vector<std::shared_ptr<Node>> e;
    std::vector<std::shared_ptr<Node>> o;
    for (const auto& n : nodes) {
        if (n->getPriority() % 2 == 0) {
            e.push_back(n);
        } else {
            o.push_back(n);
        }
    }
    std::vector<std::shared_ptr<Node>> order;
    if (even) { // Even first
        order.insert(order.begin(), e.begin(), e.end());
        order.insert(order.end(), o.begin(), o.end());
    } else { // Odd first
        order.insert(order.begin(), o.begin(), o.end());
        order.insert(order.end(), e.begin(), e.end());
    }
    return order;
}

std::vector<std::shared_ptr<Node>> FixedOrdering::ownerOrder(const std::vector<std::shared_ptr<Node>> nodes, const bool even) {
    std::vector<std::shared_ptr<Node>> e;
    std::vector<std::shared_ptr<Node>> o;
    for (const auto& n : nodes) {
        if (n->isDiamond()) {
            e.push_back(n);
        } else {
            o.push_back(n);
        }
    }
    std::vector<std::shared_ptr<Node>> order;
    if (even) { // Even first
        order.insert(order.begin(), e.begin(), e.end());
        order.insert(order.end(), o.begin(), o.end());
    } else { // Odd first
        order.insert(order.begin(), o.begin(), o.end());
        order.insert(order.end(), e.begin(), e.end());
    }
    return order;
}

std::vector<std::shared_ptr<Node>> FixedOrdering::priorityOrder(ParityGame parityGame,
                                                                const bool highLow) {
    std::vector<std::shared_ptr<Node>> order;
    if (highLow) {
        for (int i = parityGame.getDValue() - 1; i > 0; i--) {
            for (auto n : parityGame.getNodesWithPriority(i)) {
                order.push_back(n);
            }
        }
    } else {
        for (int i = 1; i < parityGame.getDValue(); i++) {
            for (auto n: parityGame.getNodesWithPriority(i)) {
                order.push_back(n);
            }
        }
    }
    return order;
}

std::vector<std::shared_ptr<Node>>
FixedOrdering::evenOddPriorityOrder(ParityGame parityGame, const bool even, const bool highLow) {
    std::vector<std::shared_ptr<Node>> e;
    std::vector<std::shared_ptr<Node>> o;
    if (highLow) {
        for (int i = parityGame.getDValue() - 1; i > 0; i--) {
            for (auto n : parityGame.getNodesWithPriority(i)) {
                if (n->getPriority() % 2 == 0) {
                    e.push_back(n);
                } else {
                    o.push_back(n);
                }
            }
        }
    } else {
        for (int i = 1; i < parityGame.getDValue(); i++) {
            for (auto n: parityGame.getNodesWithPriority(i)) {
                if (n->getPriority() % 2 == 0) {
                    e.push_back(n);
                } else {
                    o.push_back(n);
                }
            }
        }
    }
    std::vector<std::shared_ptr<Node>> order;
    if (even) { // Even first
        order.insert(order.begin(), e.begin(), e.end());
        order.insert(order.end(), o.begin(), o.end());
    } else { // Odd first
        order.insert(order.begin(), o.begin(), o.end());
        order.insert(order.end(), e.begin(), e.end());
    }
    return order;
}

std::vector<std::shared_ptr<Node>>
FixedOrdering::ownerPriorityOrder(ParityGame parityGame, const bool even, const bool highLow) {
    std::vector<std::shared_ptr<Node>> e;
    std::vector<std::shared_ptr<Node>> o;
    if (highLow) {
        for (int i = parityGame.getDValue() - 1; i > 0; i--) {
            for (auto n : parityGame.getNodesWithPriority(i)) {
                if (n->isDiamond()) {
                    e.push_back(n);
                } else {
                    o.push_back(n);
                }
            }
        }
    } else {
        for (int i = 1; i < parityGame.getDValue(); i++) {
            for (auto n: parityGame.getNodesWithPriority(i)) {
                if (n->isDiamond()) {
                    e.push_back(n);
                } else {
                    o.push_back(n);
                }
            }
        }
    }
    std::vector<std::shared_ptr<Node>> order;
    if (even) { // Even first
        order.insert(order.begin(), e.begin(), e.end());
        order.insert(order.end(), o.begin(), o.end());
    } else { // Odd first
        order.insert(order.begin(), o.begin(), o.end());
        order.insert(order.end(), e.begin(), e.end());
    }
    return order;
}



