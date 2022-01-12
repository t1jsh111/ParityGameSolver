//
// Created by Tijs Hoeijmakers on 03/01/2022.
//

#ifndef PARITYGAMESOLVER_PROGRESSMEASURE_H
#define PARITYGAMESOLVER_PROGRESSMEASURE_H

#include <vector>
#include "ParityGame.h"

class ProgressMeasure {
public:
    ProgressMeasure();
    ProgressMeasure(ParityGame* correspondingParityGame, bool top = false);


    ProgressMeasure getEvenProg(int priority) const;
    ProgressMeasure getOddProg(int priority) const;
    bool isTop() const;
    void setProgressMeasureVec(const std::vector<int> &progressMeasureVec);

    void print() const;

    const std::vector<int> &getProgressMeasureVec() const;

    bool operator<(const ProgressMeasure& rhs) const;
    bool operator==(const ProgressMeasure& rhs) const;

private:
    std::vector<int> progressMeasureVec;

    bool top;
    ParityGame* correspondingParityGame;
};


#endif //PARITYGAMESOLVER_PROGRESSMEASURE_H
