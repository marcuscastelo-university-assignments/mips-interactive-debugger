#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Registers.h"

class Debugger {
    private:
        Registers registers;

    public:
        Debugger();
		virtual ~Debugger();
        virtual void start(void);

    protected:
        // Programa programa;
};

#endif
