#include <fstream>
#include <iostream>
#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include "json.hpp"
#include "tinyxml2.h"
#include "Submission.hpp"
#include "Result.hpp"

using std::fstream;
using nlohmann::json;

void collectMessage(tinyxml2::XMLElement *failure, json &message);
void traverseTree(tinyxml2::XMLElement *root, json &config, Result &result);

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
        std::cout << root->Attribute("name") << std::endl;
        if (!(root->NoChildren())) {
            int deduction = config[root->Attribute("name")];
            result.grade -= deduction;
            json test;
            test[root->Attribute("name")] = deduction;
            json message;
            collectMessage(root->FirstChildElement(), message);
            test["message"] = message;
            result.report += test;
        }
        traverseTree(root->NextSiblingElement(), config, result);
        return;
    }
    traverseTree(root->FirstChildElement(), config, result);
    traverseTree(root->NextSiblingElement(), config, result);
}

Result parseXML(const std::string &filePath,
                const Submission &t_submission) {
    const char server[] = "eden.sysu.edu.cn";
    const char db[] = "MatrixDev";
    const char user[] = "matrixdev";
    const char password[] = "123456";
    std::string queryString = "select config from problem where id = "
        + t_submission.submission_problem_id;
    Result result;
    //  Connect to the database server
    mysqlpp::Connection conn(true);
    try {
        conn.connect(db, server, user, password);
    } catch(...) {
        std::cout << "Cannot connect to the server.\n";
        result.grade = -1;
        result.report["error"] = "Cannot connect to the server";
        return result;
    }
    //  Load xml file
    tinyxml2::XMLDocument doc;
    doc.LoadFile(filePath.c_str());
    auto AllTests = doc.RootElement();
    try {
        //  Load configure json
        auto res = conn.query(queryString).store();
        auto config = json::parse(res[0][0].c_str());
        result.grade = config["grading"]["google tests"]["total"];
        auto tests = config["grading"]["google tests"]["detail"];
        //  Traverse the DOM tree
        traverseTree(AllTests->FirstChildElement(), tests, result);
    } catch(mysqlpp::BadQuery e) {
        std::cout << "Query failed\n";
        std::cout << e.what();
    }
    return result;
}
