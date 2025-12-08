#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include <string>

#include "result.h"

class CommandProcessor
{
public:
    Result processCommand(std::string command);
};

#endif // COMMAND_PROCESSOR_H
