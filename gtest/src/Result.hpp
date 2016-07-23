#ifndef RESULT_HPP_
#define RESULT_HPP_

#include "json.hpp"

/**
 * This is a Result class for the judge result.
 */

struct Result {
    /**
     * the grade
     */
    int grade;
    /**
     * The report which is in json format.
     * The key indicates the check entry.
     * The value inidicates the what the checker
     * says. It some information about the result
     * or some hint for the student to see.
     */
    nlohmann::json report;
};

#endif // RESULT_HPP_
