#ifndef CONSOLEDEBUGGER_H
#define CONSOLEDEBUGGER_H

#include "Debugger.h"
#include "ConsoleDebugger.h"

class ConsoleDebugger : public Debugger {
    public:
		  ConsoleDebugger(void);
		  ~ConsoleDebugger();
      void start(void);
      void exec(void);

    private:
      void exportCode(vector<string> commandParts);

};

#endif
