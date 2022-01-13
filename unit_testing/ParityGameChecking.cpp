//
// Created by Tijs Hoeijmakers on 03/01/2022.
//

#include "gtest/gtest.h"
#include "Parser.h"
#include "Node.h"
#include "ProgressMeasure.h"

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
class ParityGameTesting : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        parityGame = new ParityGame(Parser::parseParityGame("../resources/manual/slide_example.gm"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete parityGame;
    }
public:
    static ParityGame* parityGame;
};
ParityGame* ParityGameTesting::parityGame = nullptr;


TEST_F(ParityGameTesting, priorityTest) {

    auto vec = parityGame->getNodes();

    auto node = parityGame->getNodeById(0);
    EXPECT_EQ(node.getPriority(), 1);

    node = parityGame->getNodeById(1);
    EXPECT_EQ(node.getPriority(), 1);

    node = parityGame->getNodeById(2);
    EXPECT_EQ(node.getPriority(), 3);

    node = parityGame->getNodeById(3);
    EXPECT_EQ(node.getPriority(), 3);

    node = parityGame->getNodeById(5);
    EXPECT_EQ(node.getPriority(), 2);

    node = parityGame->getNodeById(6);
    EXPECT_EQ(node.getPriority(), 2);
}

TEST_F(ParityGameTesting, ownerTest) {
    auto node = parityGame->getNodeById(0);
    EXPECT_EQ(node.isSquare(), true);
    EXPECT_EQ(node.isDiamond(), false);

    node = parityGame->getNodeById(1);
    EXPECT_EQ(node.isSquare(), false);
    EXPECT_EQ(node.isDiamond(), true);

    node = parityGame->getNodeById(2);
    EXPECT_EQ(node.isSquare(), false);
    EXPECT_EQ(node.isDiamond(), true);

    node = parityGame->getNodeById(3);
    EXPECT_EQ(node.isSquare(), false);
    EXPECT_EQ(node.isDiamond(), true);

    node = parityGame->getNodeById(5);
    EXPECT_EQ(node.isSquare(), true);
    EXPECT_EQ(node.isDiamond(), false);

    node = parityGame->getNodeById(6);
    EXPECT_EQ(node.isSquare(), false);
    EXPECT_EQ(node.isDiamond(), true);
}

TEST_F(ParityGameTesting, dValueTest) {

    int dValue = parityGame->getDValue();
    EXPECT_EQ(dValue, 4);

}

TEST_F(ParityGameTesting, successorTest) {

    auto domainMaximum = parityGame->getProgressMeasureDomainMaximum();
    EXPECT_EQ(domainMaximum.isTop(), false);
    std::vector<int> expectation = {0,2,0,3};
    EXPECT_EQ(domainMaximum.getProgressMeasureVec(), expectation);

}

TEST_F(ParityGameTesting, oddProgressingProgressMeasureDomainMaximum) {

    auto domainMaximum = parityGame->getProgressMeasureDomainMaximum();
    auto oddProg1= domainMaximum.getOddProg(1);
    EXPECT_EQ(oddProg1.isTop(), true);

    auto oddProg3= domainMaximum.getOddProg(3);
    EXPECT_EQ(oddProg3.isTop(), true);


}

TEST_F(ParityGameTesting, evenProgressingProgressMeasureDomainMaximum) {

    auto domainMaximum = parityGame->getProgressMeasureDomainMaximum();
    auto evenProg0 = domainMaximum.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = domainMaximum.getEvenProg(2);
    expectation = {0,2,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);


}

TEST_F(ParityGameTesting, oddProgressingSimpleProgressMeasure) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,0});
    auto oddProg1 =  simpleProgress.getOddProg(1);

    std::vector<int> expectation = {0,2,0,0};
    EXPECT_EQ(oddProg1.getProgressMeasureVec(), expectation);

    auto oddProg3 = simpleProgress.getOddProg(3);
    expectation = {0,1,0,1};
    EXPECT_EQ(oddProg3.getProgressMeasureVec(), expectation);


}

TEST_F(ParityGameTesting, evenProgressingSimpleProgressMeasure) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,0});
    auto evenProg0 =  simpleProgress.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = simpleProgress.getEvenProg(2);
    expectation = {0,1,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);

}



TEST_F(ParityGameTesting, oddProgressingSimpleProgressMeasure2) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,3});
    auto oddProg1 =  simpleProgress.getOddProg(1);

    std::vector<int> expectation = {0,2,0,0};
    EXPECT_EQ(oddProg1.getProgressMeasureVec(), expectation);

    auto oddProg3 = simpleProgress.getOddProg(3);
    expectation = {0,2,0,0};
    EXPECT_EQ(oddProg3.getProgressMeasureVec(), expectation);


}

TEST_F(ParityGameTesting, evenProgressingSimpleProgressMeasure2) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,3});
    auto evenProg0 =  simpleProgress.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = simpleProgress.getEvenProg(2);
    expectation = {0,1,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);

}




TEST_F(ParityGameTesting, oddProgressingSimpleProgressMeasure3) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,2,0,2});
    auto oddProg1 =  simpleProgress.getOddProg(1);

    EXPECT_EQ(oddProg1.isTop(), true);

    auto oddProg3 = simpleProgress.getOddProg(3);
    std::vector<int> expectation = {0,2,0,3};
    EXPECT_EQ(oddProg3.getProgressMeasureVec(), expectation);


}

TEST_F(ParityGameTesting, evenProgressingSimpleProgressMeasure3) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,2,0,2});
    auto evenProg0 =  simpleProgress.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = simpleProgress.getEvenProg(2);
    expectation = {0,2,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);

}


// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
class ParityGameTestingElevator : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        parityGame = new ParityGame(Parser::parseParityGame("../resources/elevator_games/elevator1_2.gm"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete parityGame;
    }
public:
    static ParityGame* parityGame;
};
ParityGame* ParityGameTestingElevator::parityGame = nullptr;

TEST_F(ParityGameTestingElevator, testReadingFile) {

    auto node = parityGame->getNode(100);
    std::cout << "node name" << node->getNodeName();
    EXPECT_EQ(node->getNodeName(), "[X..]  |= 0");


}