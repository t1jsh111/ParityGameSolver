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
class ProgressMeasureTesting : public QuickTest {
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
ParityGame* ProgressMeasureTesting::parityGame = nullptr;




TEST_F(ProgressMeasureTesting, oddProgressingProgressMeasureDomainMaximum) {

    auto domainMaximum = parityGame->getProgressMeasureDomainMaximum();
    auto oddProg1= domainMaximum.getOddProg(1);
    EXPECT_EQ(oddProg1.isTop(), true);

    auto oddProg3= domainMaximum.getOddProg(3);
    EXPECT_EQ(oddProg3.isTop(), true);


}

TEST_F(ProgressMeasureTesting, evenProgressingProgressMeasureDomainMaximum) {

    auto domainMaximum = parityGame->getProgressMeasureDomainMaximum();
    auto evenProg0 = domainMaximum.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = domainMaximum.getEvenProg(2);
    expectation = {0,2,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);


}

TEST_F(ProgressMeasureTesting, oddProgressingSimpleProgressMeasure) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,0});
    auto oddProg1 =  simpleProgress.getOddProg(1);

    std::vector<int> expectation = {0,2,0,0};
    EXPECT_EQ(oddProg1.getProgressMeasureVec(), expectation);

    auto oddProg3 = simpleProgress.getOddProg(3);
    expectation = {0,1,0,1};
    EXPECT_EQ(oddProg3.getProgressMeasureVec(), expectation);


}

TEST_F(ProgressMeasureTesting, evenProgressingSimpleProgressMeasure) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,0});
    auto evenProg0 =  simpleProgress.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = simpleProgress.getEvenProg(2);
    expectation = {0,1,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);

}



TEST_F(ProgressMeasureTesting, oddProgressingSimpleProgressMeasure2) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,3});
    auto oddProg1 =  simpleProgress.getOddProg(1);

    std::vector<int> expectation = {0,2,0,0};
    EXPECT_EQ(oddProg1.getProgressMeasureVec(), expectation);

    auto oddProg3 = simpleProgress.getOddProg(3);
    expectation = {0,2,0,0};
    EXPECT_EQ(oddProg3.getProgressMeasureVec(), expectation);


}

TEST_F(ProgressMeasureTesting, evenProgressingSimpleProgressMeasure2) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,1,0,3});
    auto evenProg0 =  simpleProgress.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = simpleProgress.getEvenProg(2);
    expectation = {0,1,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);

}




TEST_F(ProgressMeasureTesting, oddProgressingSimpleProgressMeasure3) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,2,0,2});
    auto oddProg1 =  simpleProgress.getOddProg(1);

    EXPECT_EQ(oddProg1.isTop(), true);

    auto oddProg3 = simpleProgress.getOddProg(3);
    std::vector<int> expectation = {0,2,0,3};
    EXPECT_EQ(oddProg3.getProgressMeasureVec(), expectation);


}

TEST_F(ProgressMeasureTesting, evenProgressingSimpleProgressMeasure3) {

    ProgressMeasure simpleProgress(parityGame);
    simpleProgress.setProgressMeasureVec({0,2,0,2});
    auto evenProg0 =  simpleProgress.getEvenProg(0);

    std::vector<int> expectation = {0,0,0,0};
    EXPECT_EQ(evenProg0.getProgressMeasureVec(), expectation);

    auto evenProg2 = simpleProgress.getEvenProg(2);
    expectation = {0,2,0,0};
    EXPECT_EQ(evenProg2.getProgressMeasureVec(), expectation);

}


TEST_F(ProgressMeasureTesting, progressMeasureComparison) {

    ProgressMeasure progressM1(parityGame);
    ProgressMeasure progressM2(parityGame);
    progressM1.setProgressMeasureVec({0,1,0,2});
    progressM2.setProgressMeasureVec({0,2,0,2});

    EXPECT_EQ(progressM1 < progressM2, true);
    EXPECT_EQ(progressM2 < progressM1, false);
    EXPECT_EQ(progressM2 == progressM1, false);

    EXPECT_EQ(std::max(progressM1, progressM2) == progressM1, false);
    EXPECT_EQ(std::max(progressM1, progressM2) == progressM2, true);

    progressM1.setProgressMeasureVec({0,1,0,2});
    progressM2.setProgressMeasureVec({0,2,0,1});
    EXPECT_EQ(progressM1 < progressM2, true);
    EXPECT_EQ(progressM2 < progressM1, false);
    EXPECT_EQ(progressM2 == progressM1, false);

    EXPECT_EQ(std::max(progressM1, progressM2) == progressM1, false);
    EXPECT_EQ(std::max(progressM1, progressM2) == progressM2, true);

    progressM1.setProgressMeasureVec({0,2,0,2});
    progressM2.setProgressMeasureVec({0,2,0,2});
    EXPECT_EQ(progressM1 < progressM2, false);
    EXPECT_EQ(progressM2 < progressM1, false);
    EXPECT_EQ(progressM2 == progressM1, true);

    EXPECT_EQ(std::max(progressM1, progressM2) == progressM1, true);
    EXPECT_EQ(std::max(progressM1, progressM2) == progressM2, true);

    ProgressMeasure progressM3(parityGame, true);
    std::vector<ProgressMeasure> measures = {progressM1, progressM2, progressM3};
    EXPECT_EQ(std::max_element(measures.begin(), measures.end())->isTop(), true);

}