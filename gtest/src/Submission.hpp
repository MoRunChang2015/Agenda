#ifndef SUBMISSION_HPP_
#define SUBMISSION_HPP_

#include "json.hpp"
#include <string>

/**
 * This Class is a Submission entity
 */

struct Submission {
    /**
     * The submission_id of this submission
     */
    std::string submission_id;

    /**
     * The correspoing problem id of this
     * submission
     */
    std::string submission_problem_id;

    /**
     * The problem_type of this submission.
     * i.e. Programming or Choice or ect.
     */
    std::string submission_problem_type;

    /**
     * A json object parsed from mysql problem config
     * It contians essential imformation about the problem.
     */
    nlohmann::json submission_problem_config;
};

#endif // SUBMISSION_HPP_
