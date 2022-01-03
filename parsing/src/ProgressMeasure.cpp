//
// Created by Tijs Hoeijmakers on 03/01/2022.
//

#include "ProgressMeasure.h"

ProgressMeasure::ProgressMeasure(const ParityGame& correspondingParityGame, bool top) :
progressMeasureVec(correspondingParityGame.getDValue(), 0), correspondingParityGame(correspondingParityGame), top(top) {

}

ProgressMeasure ProgressMeasure::getEvenProg(int priority) const {
    if(priority % 2 != 0) {
        throw std::runtime_error("priority provided is not even");
    }

    if(isTop()) {
        return *this;
    } else {
        int d = correspondingParityGame.getDValue();
        ProgressMeasure progress(correspondingParityGame);
        std::vector<int> m(d);
        for(int i = 0; i <= priority; i++) {
            m[i] = progressMeasureVec[i];
        }
        progress.setProgressMeasureVec(m);
        return progress;
    }
}

ProgressMeasure ProgressMeasure::getOddProg(int priority) const {
    if(priority % 2 != 1) {
        throw std::runtime_error("priority provided is not odd");
    }

    if(isTop()) {
        return *this;
    } else {
        int d = correspondingParityGame.getDValue();
        ProgressMeasure mProgressMeasure(correspondingParityGame);
        std::vector<int> m(d);

//        // in case d is not odd, we need to start one element lower
//        if(d % 2 != 1) {d--;}

        for(int i = priority; i >= 0; i -= 2) {
            if(progressMeasureVec[i]+1 <= correspondingParityGame.getNumberOfVerticesWithPriority(i)) {
                // We can increase
                m[i] = progressMeasureVec[i]+1;
                // copy the rest of the vector
                for(int j = i-2; j >= 0; j -= 2) {
                    m[j] = progressMeasureVec[j];
                }
                break;


            } else { // we could not increase index i

                // We were not able to increase
                if(i == 1) {
                    ProgressMeasure top(correspondingParityGame, true);
                    return top;
                }

                m[i] = 0;
            }
        }

        mProgressMeasure.setProgressMeasureVec(m);
        return mProgressMeasure;

    }
}


void ProgressMeasure::setProgressMeasureVec(const std::vector<int> &progressMeasureVec) {
    ProgressMeasure::progressMeasureVec = progressMeasureVec;
}



bool ProgressMeasure::isTop() const {
    return top;
}

const std::vector<int> &ProgressMeasure::getProgressMeasureVec() const {
    return progressMeasureVec;
}

