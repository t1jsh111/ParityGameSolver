//
// Created by Tijs Hoeijmakers on 05/01/2022.
//

#ifndef PARITYGAMESOLVER_WORKINGLISTORDERER_H
#define PARITYGAMESOLVER_WORKINGLISTORDERER_H

#include "Node.h"
#include "ProgressMeasure.h"

#include <list>
#include <memory>
#include <unordered_map>

class WorkingListOrderer {
public:
     std::list<std::shared_ptr<Node>> getInitialWorkingList(const std::vector<std::shared_ptr<Node>>& nodes);

     void appendPredecessorsOfNodeToWorkingList(const Node& node, std::list<std::shared_ptr<Node>>& workingList, const std::unordered_map<int, ProgressMeasure>& rhoMapping);



};


#endif //PARITYGAMESOLVER_WORKINGLISTORDERER_H
