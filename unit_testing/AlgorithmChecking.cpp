//
// Created by Tijs Hoeijmakers on 06/01/2022.
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
class AlgorithmTesting : public QuickTest {
    // We don't need any more logic than already in the QuickTest fixture.
    // Therefore the body is empty.
protected:
    static void SetUpTestSuite() {
        parityGame = new ParityGame(Parser::parseParityGame("../resources/ccp_games/german_linear_5.invariantly_eventually_fair_shared_access.gm"));
    }

    static void TearDownTestSuite() {
        std::cout << "delete test suite";
        delete parityGame;
    }
public:
    static ParityGame* parityGame;
};
ParityGame* AlgorithmTesting::parityGame = nullptr;


TEST_F(AlgorithmTesting, improvedIsEquivalent) {

    std::unordered_map<int, ProgressMeasure> rhoMapping1;
    std::unordered_map<int, ProgressMeasure> rhoMapping3;
    for(const auto& node : parityGame->getNodes()) {
        auto zeroProgressMeasure = ProgressMeasure(parityGame);
        zeroProgressMeasure.setProgressMeasureVec(std::vector<int>(parityGame->getDValue()));

        rhoMapping1[node->getId()] = zeroProgressMeasure;
        rhoMapping3[node->getId()] = zeroProgressMeasure;
    }

    ProgressMeasuresAlgo::solveParityGame(*parityGame, rhoMapping1);
    ProgressMeasuresAlgo::solveParityGameImprovedWorkList(*parityGame, rhoMapping3);

    for(const auto& node : parityGame->getNodes()) {
        EXPECT_EQ(rhoMapping1[node->getId()], rhoMapping3[node->getId()]);
    }




}