/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// #include "huhi/vendor/bat-native-usermodel/src/DataPoint.h"
#include "huhi/vendor/bat-native-usermodel/src/classifier.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"
#include <cmath>

namespace usermodel {

class Classifier_Test : public ::testing::Test {
 protected:
  Classifier_Test() {}
  ~Classifier_Test() override {}
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(Classifier_Test, Three_classes_test) {
  std::map<std::string,DataPoint> weights = {
    {"class_1", std::vector<float>{1.0, 0.0, 0.0}},
    {"class_2", std::vector<float>{0.0, 1.0, 0.0}},
    {"class_3", std::vector<float>{0.0, 0.0, 1.0}}
  };
  std::map<std::string,float> biases = {
    {"class_1",0.0},
    {"class_2", 0.0},
    {"class_3",0.0}
  };
  Linear_classifier linear_classifier(weights,biases);
  
  auto class1 = DataPoint(std::vector<float>{1.0, 0.0, 0.0});
  auto rez1 = linear_classifier.Predict(class1);
  EXPECT_TRUE(rez1["class_1"] > rez1["class_2"]);
  EXPECT_TRUE(rez1["class_1"] > rez1["class_3"]);

  auto class2 = DataPoint(std::vector<float>{0.0, 1.0, 0.0});
  auto rez2 = linear_classifier.Predict(class2);
  EXPECT_TRUE(rez2["class_2"] > rez2["class_1"]);
  EXPECT_TRUE(rez2["class_2"] > rez2["class_3"]);

  auto class3 = DataPoint(std::vector<float>{0.0, 1.0, 2.0});
  auto rez3 = linear_classifier.Predict(class3);
  EXPECT_TRUE(rez3["class_3"] > rez3["class_1"]);
  EXPECT_TRUE(rez3["class_3"] > rez3["class_2"]);
}

TEST_F(Classifier_Test, Biases_test) {
  std::map<std::string,DataPoint> weights = {
    {"class_1", std::vector<float>{1.0, 0.0, 0.0}},
    {"class_2", std::vector<float>{0.0, 1.0, 0.0}},
    {"class_3", std::vector<float>{0.0, 0.0, 1.0}}
  };
  std::map<std::string,float> biases = {
    {"class_1",0.0},
    {"class_2", 0.0},
    {"class_3",1.0}
  };
  Linear_classifier biased_classifier(weights,biases);
  
  auto avg_point = DataPoint(std::vector<float>{1.0, 1.0, 1.0});
  auto rez = biased_classifier.Predict(avg_point);
  EXPECT_TRUE(rez["class_3"] > rez["class_1"]);
  EXPECT_TRUE(rez["class_3"] > rez["class_2"]);
}

TEST_F(Classifier_Test, Softmax_test) {
  std::map<std::string,float> group_1 = {{"c1", -1.0}, {"c2",2.0}, {"c3", 3.0} };
  auto sm = usermodel::Softmax(group_1);
  
  EXPECT_TRUE(sm["c3"]>sm["c1"]);
  EXPECT_TRUE(sm["c3"]>sm["c2"]);
  EXPECT_TRUE(sm["c2"]>sm["c1"]);
  EXPECT_TRUE(sm["c1"]>0.0);
  EXPECT_TRUE(sm["c3"]<1.0);
  float sum = 0.0;
  for (auto const& x : sm){
    sum += x.second;
  }
  EXPECT_TRUE((sum-1.0) < 0.00000001);

}

TEST_F(Classifier_Test, Extended_Softmax_test) {
  //from scipy.special import softmax  
  // softmax([0,1,2]) == softmax([3,4,5]) == [true, true,true]
  //In [2]: softmax([0,1,2])                                                                                                                                                            
  //Out[2]: array([0.09003057, 0.24472847, 0.66524096])

  
  std::map<std::string,float> group_1 = {{"c1", 0.0}, {"c2",1.0}, {"c3", 2.0} };
  std::map<std::string,float> group_2 = {{"c1", 3.0}, {"c2",4.0}, {"c3", 5.0} };
  auto sm_1 = usermodel::Softmax(group_1);
  auto sm_2 = usermodel::Softmax(group_2);
  EXPECT_TRUE( abs(  sm_1["c1"]-sm_2["c1"] ) <0.00000001);
  EXPECT_TRUE( abs( sm_1["c2"]-sm_2["c2"] ) < 0.00000001 );
  EXPECT_TRUE( abs(sm_1["c3"]-sm_2["c3"] ) <0.00000001 );
  EXPECT_TRUE( abs(sm_1["c1"] - 0.09003057) <0.00000001 );
  EXPECT_TRUE( abs(sm_1["c2"] - 0.24472847) < 0.00000001);
  EXPECT_TRUE( abs(sm_1["c3"] - 0.66524095) < 0.00000001);  
  
  
}

}  // namespace usermodel
