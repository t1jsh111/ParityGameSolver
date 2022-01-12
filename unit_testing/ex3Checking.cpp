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
    std::unordered_map<int, ProgressMeasure> expectedMapping;

    ProgressMeasure prog0Expec(parityGame, false);
    prog0Expec.setProgressMeasureVec({0,0,0,0,0});
    expectedMapping[0] = prog0Expec;

    ProgressMeasure prog1Expec(parityGame, false);
    prog1Expec.setProgressMeasureVec({0,0,0,0,0});
    expectedMapping[1] = prog0Expec;

    ProgressMeasure prog2Expec(parityGame, true);
    expectedMapping[2] = prog2Expec;

    ProgressMeasure prog3Expec(parityGame, true);
    expectedMapping[3] = prog3Expec;



    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

//    for(const auto& node : parityGame->getNodes()) {
//        std::cout << "node: " << node->getId() << " evals to ";
//        rhoMapping1[node->getId()].print();
//        std::cout << std::endl;
//    }

    for(const auto& node : parityGame->getNodes()) {
        EXPECT_EQ(rhoMapping1[node->getId()], expectedMapping[node->getId()]);
    }



}

TEST_F(Ex3Testing, printingFig2) {

    setParityGame("../resources/ex3/fig2.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    std::unordered_map<int, ProgressMeasure> expectedMapping;

    ProgressMeasure prog0Expec(parityGame, true);
    expectedMapping[0] = prog0Expec;

    ProgressMeasure prog1Expec(parityGame, true);
    expectedMapping[1] = prog0Expec;

    ProgressMeasure prog2Expec(parityGame, true);
    expectedMapping[2] = prog2Expec;

    ProgressMeasure prog3Expec(parityGame, true);
    expectedMapping[3] = prog3Expec;

    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

//    for(const auto& node : parityGame->getNodes()) {
//        std::cout << "node: " << node->getId() << " evals to ";
//        rhoMapping1[node->getId()].print();
//        std::cout << std::endl;
//    }

    for(const auto& node : parityGame->getNodes()) {
        EXPECT_EQ(rhoMapping1[node->getId()], expectedMapping[node->getId()]);
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

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

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

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}

TEST_F(Ex3Testing, printingFig5) {

    setParityGame("../resources/ex3/fig5.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}

TEST_F(Ex3Testing, printingFig6) {

    setParityGame("../resources/ex3/fig6.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}

TEST_F(Ex3Testing, printingFig7) {

    setParityGame("../resources/ex3/fig7.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

    for(const auto& node : parityGame->getNodes()) {
        std::cout << "node: " << node->getId() << " evals to ";
        rhoMapping1[node->getId()].print();
        std::cout << std::endl;
    }


}

TEST_F(Ex3Testing, printingFig8) {

    setParityGame("../resources/ex3/fig8.gm");

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGameInputOrder(*parityGame, rhoMapping1);

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