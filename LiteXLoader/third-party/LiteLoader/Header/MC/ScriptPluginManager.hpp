// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Scripting.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptPluginManager {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTPLUGINMANAGER
public:
    class ScriptPluginManager& operator=(class ScriptPluginManager const&) = delete;
    ScriptPluginManager(class ScriptPluginManager const&) = delete;
    ScriptPluginManager() = delete;
#endif

public:
    MCAPI ScriptPluginManager(class Scripting::ScriptEngine&, class Scripting::IPrinter*);
    MCAPI void addNativeModuleFactory(std::unique_ptr<class Scripting::IModuleBindingFactory>);
    MCAPI class ScriptPluginResult discoverPlugins(struct PluginDefStack const&);
    MCAPI void releasePlugins();
    MCAPI class ScriptPluginResult runAll();
    MCAPI ~ScriptPluginManager();

protected:

private:
    MCAPI void _reportContextResults(std::string const&, struct Scripting::ScriptContextResult const&, class ScriptPluginResult&);

};