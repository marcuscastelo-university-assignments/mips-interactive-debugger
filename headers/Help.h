#ifndef HELP_H
#define HELP_H

#include "DebuggerFunction.h"

class Help : public DebuggerFunction {
    public:
        Help();
        ~Help();
        void exec(void);
};

#endif