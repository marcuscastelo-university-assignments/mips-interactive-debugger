#ifndef CONSOLEDEBUGGER_H
#define CONSOLEDEBUGGER_H

#include "Debugger.h"
#include "ConsoleDebugger.h"

#include <string>
#include <vector>
using namespace std;

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
