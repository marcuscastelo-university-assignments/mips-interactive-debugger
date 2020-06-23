#ifndef DEBUGGERFUNCTION_H 
#define DEBUGGERFUNCTION_H

class DebuggerFunction {
    public:
        DebuggerFunction(void);
        virtual ~DebuggerFunction();
        virtual void exec(void);
};

#endif