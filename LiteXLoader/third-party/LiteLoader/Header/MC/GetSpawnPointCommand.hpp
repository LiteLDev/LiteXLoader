// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class GetSpawnPointCommand {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_GETSPAWNPOINTCOMMAND
public:
    class GetSpawnPointCommand& operator=(class GetSpawnPointCommand const&) = delete;
    GetSpawnPointCommand(class GetSpawnPointCommand const&) = delete;
    GetSpawnPointCommand() = delete;
#endif

public:
    /*0*/ virtual ~GetSpawnPointCommand();
    /*1*/ virtual void execute(class CommandOrigin const&, class CommandOutput&) const;

protected:

private:

};