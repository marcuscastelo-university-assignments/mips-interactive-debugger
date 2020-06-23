#ifndef INFO_H
#define INFO_H

#include "DebuggerFunction.h"

class Info : public DebuggerFunction {
    public:
        Info();
        ~Info();
        void exec(void);
};

#endif