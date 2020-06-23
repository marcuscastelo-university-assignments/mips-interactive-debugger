#ifndef DEBUGGERFUNCTION_H 
#define DEBUGGERFUNCTION_H

#include <vector>
#include <string>
using namespace std;

class DebuggerFunction {
    public:
        DebuggerFunction(void);
        virtual ~DebuggerFunction();
        virtual void exec(vector<string> command_parts);
};

#endif