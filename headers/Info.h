#ifndef INFO_H
#define INFO_H

#include "DebuggerFunction.h"

#include <vector>
#include <string>
using namespace std;


class Info : public DebuggerFunction {
    public:
        Info();
        ~Info();
        void exec(vector<string> command_parts);
};

#endif