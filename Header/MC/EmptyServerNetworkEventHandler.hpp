// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class EmptyServerNetworkEventHandler {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_EMPTYSERVERNETWORKEVENTHANDLER
public:
    class EmptyServerNetworkEventHandler& operator=(class EmptyServerNetworkEventHandler const&) = delete;
    EmptyServerNetworkEventHandler(class EmptyServerNetworkEventHandler const&) = delete;
    EmptyServerNetworkEventHandler() = delete;
#endif

public:
    /*0*/ virtual ~EmptyServerNetworkEventHandler();
    /*1*/ virtual struct GameplayHandlerResult<enum CoordinatorResult> handleChat(struct ChatEvent&);

protected:

private:

};