// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptBinderTemplate {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTBINDERTEMPLATE
public:
    class ScriptBinderTemplate& operator=(class ScriptBinderTemplate const&) = delete;
    ScriptBinderTemplate(class ScriptBinderTemplate const&) = delete;
#endif

public:
    /*0*/ virtual ~ScriptBinderTemplate();
    /*
    inline  ~ScriptBinderTemplate(){
         (ScriptBinderTemplate::*rv)();
        *((void**)&rv) = dlsym("??1ScriptBinderTemplate@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ScriptBinderTemplate();

protected:

private:

};