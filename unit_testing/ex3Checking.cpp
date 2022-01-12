//
// Created by Tijs Hoeijmakers on 10/01/2022.
//


#include "gtest/gtest.h"
#include "Parser.h"
#include "Node.h"
#include "ProgressMeasure.h"
#include "ProgressMeasuresAlgo.h"

#include <unordered_set>

class QuickTest : public testing::Test {
protected:

    void SetUp() override {
    }

    // TearDown() is invoked immediately after a test finishes.  Here we
    // check if the test was too slow.
    void TearDown() override {
    }

};

// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
class Ex3Testing : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {

    }

    static void setParityGame(std::string path) {
        parityGame = new ParityGame(Parser::parseParityGame(path));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete parityGame;
    }
public:
    static ParityGame* parityGame;
};
ParityGame* Ex3Testing::parityGame = nullptr;


TEST_F(Ex3Testing, printingFig1) {
    setParityGame("../resources/ex3/fig1.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGame(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }




}

TEST_F(Ex3Testing, printingFig2) {

    setParityGame("../resources/ex3/fig2.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGame(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}

TEST_F(Ex3Testing, printingFig3) {

    setParityGame("../resources/ex3/fig3.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGame(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}

TEST_F(Ex3Testing, printingFig4) {

    setParityGame("../resources/ex3/fig4.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGame(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}


TEST_F(Ex3Testing, SlideTest) {

    setParityGame("../resources/manual/slide_example.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameImprovedWorkList(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}