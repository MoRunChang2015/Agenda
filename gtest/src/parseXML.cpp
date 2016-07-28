#include <iostream>
#include "json.hpp"
#include "tinyxml2.h"
#include "Submission.hpp"
#include "Result.hpp"

using nlohmann::json;

namespace {
  using nlohmann::json;
  void collectMessage(tinyxml2::XMLElement *failure, json &message) {
    do {
      message += failure->Attribute("message");
      failure = failure->NextSiblingElement();
    } while (failure);
  }

  void traverseTree(tinyxml2::XMLElement *root, json &config, Result &result) {
    if (root == nullptr) {
      return;
    }
    if (strcmp(root->Name(), "testcase") == 0) {
      if (!(root->NoChildren())) {
        int deduction = config[root->Attribute("name")];
        result.grade -= deduction;
        json test;
        test[root->Attribute("name")] = deduction;
        //  Do not collect error info
        //  Just record the failed tests

        // json message;
        // collectMessage(root->FirstChildElement(), message);
        // test["message"] = message;
        result.report += test;
      }
      traverseTree(root->NextSiblingElement(), config, result);
      return;
    }
    traverseTree(root->FirstChildElement(), config, result);
    traverseTree(root->NextSiblingElement(), config, result);
  }

}

nlohmann::json parseXML(const std::string &filePath,
                        const json &config) {
  Result result;
  //  Load xml file
  tinyxml2::XMLDocument doc;
  doc.LoadFile(filePath.c_str());
  auto AllTests = doc.RootElement();
  //  Load configure json
  result.grade = config["grading"]["google tests"];
  auto tests = config["grading"]["google tests detail"];
  //  Traverse the DOM tree
  traverseTree(AllTests->FirstChildElement(), tests, result);
  json resultJs;
  resultJs["grade"] = result.grade;
  resultJs["failure"] = result.report;
  resultJs["info"] = config["google tests info"];
  return resultJs;
}
