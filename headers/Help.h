#ifndef HELP_H
#define HELP_H

#include "DebuggerFunction.h"

#include <vector>
#include <string>
using namespace std;


class Help : public DebuggerFunction {
    public:
        Help();
        ~Help();
        void exec(vector<string> command_parts);
};

#endif