#ifndef PATH_HPP
#define PATH_HPP

class Path {
public:
    static const char *userPath;
    static const char *meetingPath;
};

const char *Path::meetingPath = "tmp/data/meetings.csv";
const char *Path::userPath = "tmp/data/users.csv";

#endif
