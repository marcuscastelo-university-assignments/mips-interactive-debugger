#ifndef __CONSOLEDEBUGGER__H__
#define __CONSOLEDEBUGGER__H__

#include "Debugger.h"

class ConsoleDebugger : public Debugger {
    public:
		  ConsoleDebugger(void);
		  ~ConsoleDebugger();
      void start(void);

    private:
      void exportCode(std::vector<std::string> commandParts);
      void printModifiedRegisters(const Registers& oldRegisters, const Registers& newRegisters);
};

#endif
