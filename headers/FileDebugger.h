#ifndef FILEDEBUGGER_H
#define FILEDEBUGGER_H

#include "Debugger.h"
#include "FileDebugger.h"

class FileDebugger : public Debugger {
    public:
        FileDebugger(void);
        ~FileDebugger(void);
        void start(void);
        void exec(void);
};

#endif