#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <string>

#include "result.h"

class CommandProcessor
{
public:
    const bool debug;

    CommandProcessor() : debug(true) {};
    CommandProcessor(bool debugMode) : debug(debugMode) {};

    Result processCommand(std::string command);
};

#endif // COMMAND_PROCESSOR_H
