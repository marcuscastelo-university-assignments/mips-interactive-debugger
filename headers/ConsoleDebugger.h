#ifndef CONSOLEDEBUGGER_H
#define CONSOLEDEBUGGER_H

#include "Debugger.h"
#include "ConsoleDebugger.h"

class ConsoleDebugger : public Debugger {
    public:
		ConsoleDebugger(void);
		~ConsoleDebugger(void);
        void start(void);
};

#endif
