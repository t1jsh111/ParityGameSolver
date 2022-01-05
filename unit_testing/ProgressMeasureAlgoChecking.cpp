//
// Created by Tijs Hoeijmakers on 03/01/2022.
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
class ProgressMeasureAlgoTesting : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        parityGame = new ParityGame(Parser::parseParityGame("../resources/manual/slide12_example.gm"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete parityGame;
    }
public:
    static ParityGame* parityGame;
};
ParityGame* ProgressMeasureAlgoTesting::parityGame = nullptr;

TEST_F(ProgressMeasureAlgoTesting, test) {
    std::cout << "number of vertices with prior1 " <<parityGame->getNumberOfVerticesWithPriority(2);

}

TEST_F(ProgressMeasureAlgoTesting, progTesting1) {
    Node v(0,0,0);
    Node w(1,0,0);
    std::unordered_map<int, ProgressMeasure> rhoMapping;

    ProgressMeasure measure(parityGame);
    measure.setProgressMeasureVec({0,2,0,0});
    rhoMapping[1] = measure;

    auto result = ProgressMeasuresAlgo::Prog(rhoMapping, v,w, *parityGame);
    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(result.getProgressMeasureVec(),expectation);
    EXPECT_EQ(result.isTop(),false);


}

TEST_F(ProgressMeasureAlgoTesting, progTesting2) {
    Node v(0,1,0);
    Node w(1,0,0);
    std::unordered_map<int, ProgressMeasure> rhoMapping;

    ProgressMeasure measure(parityGame);
    measure.setProgressMeasureVec({0,2,0,0});

    rhoMapping[1] = measure;

    auto result = ProgressMeasuresAlgo::Prog(rhoMapping, v,w, *parityGame);
    EXPECT_EQ(result.isTop(),true);

}

TEST_F(ProgressMeasureAlgoTesting, progTesting3) {
    Node v(0,3,0);
    Node w(1,0,0);
    std::unordered_map<int, ProgressMeasure> rhoMapping;

    ProgressMeasure measure(parityGame);
    measure.setProgressMeasureVec({0,2,0,0});
    rhoMapping[1] = measure;

    auto result = ProgressMeasuresAlgo::Prog(rhoMapping, v,w, *parityGame);
    std::vector<int> expectation = {0,2,0,1};
    EXPECT_EQ(result.getProgressMeasureVec(),expectation);
    EXPECT_EQ(result.isTop(),false);

}

