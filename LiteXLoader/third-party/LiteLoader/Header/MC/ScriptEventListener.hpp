// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptEventListener {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTEVENTLISTENER
public:
    class ScriptEventListener& operator=(class ScriptEventListener const&) = delete;
    ScriptEventListener(class ScriptEventListener const&) = delete;
    ScriptEventListener() = delete;
#endif

public:
    /*0*/ virtual ~ScriptEventListener();
    /*
    inline enum EventResult onScriptError(std::string const& a0, std::string const& a1){
        enum EventResult (ScriptEventListener::*rv)(std::string const&, std::string const&);
        *((void**)&rv) = dlsym("?onScriptError@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
        return (this->*rv)(std::forward<std::string const&>(a0), std::forward<std::string const&>(a1));
    }
    inline enum EventResult onScriptListenForEvent(std::string const& a0){
        enum EventResult (ScriptEventListener::*rv)(std::string const&);
        *((void**)&rv) = dlsym("?onScriptListenForEvent@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
        return (this->*rv)(std::forward<std::string const&>(a0));
    }
    inline enum EventResult onScriptBroadcastEvent(std::string const& a0, enum RegistrationType a1, bool a2){
        enum EventResult (ScriptEventListener::*rv)(std::string const&, enum RegistrationType, bool);
        *((void**)&rv) = dlsym("?onScriptBroadcastEvent@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4RegistrationType@@_N@Z");
        return (this->*rv)(std::forward<std::string const&>(a0), std::forward<enum RegistrationType>(a1), std::forward<bool>(a2));
    }
    inline enum EventResult onScriptInternalError(std::string const& a0){
        enum EventResult (ScriptEventListener::*rv)(std::string const&);
        *((void**)&rv) = dlsym("?onScriptInternalError@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
        return (this->*rv)(std::forward<std::string const&>(a0));
    }
    inline enum EventResult onScriptRan(std::string const& a0, std::string const& a1, bool a2){
        enum EventResult (ScriptEventListener::*rv)(std::string const&, std::string const&, bool);
        *((void**)&rv) = dlsym("?onScriptRan@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0_N@Z");
        return (this->*rv)(std::forward<std::string const&>(a0), std::forward<std::string const&>(a1), std::forward<bool>(a2));
    }
    inline enum EventResult onScriptRegisterView(){
        enum EventResult (ScriptEventListener::*rv)();
        *((void**)&rv) = dlsym("?onScriptRegisterView@ScriptEventListener@@UEAA?AW4EventResult@@XZ");
        return (this->*rv)();
    }
    inline enum EventResult onScriptGetComponent(std::string const& a0, enum RegistrationType a1, bool a2){
        enum EventResult (ScriptEventListener::*rv)(std::string const&, enum RegistrationType, bool);
        *((void**)&rv) = dlsym("?onScriptGetComponent@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4RegistrationType@@_N@Z");
        return (this->*rv)(std::forward<std::string const&>(a0), std::forward<enum RegistrationType>(a1), std::forward<bool>(a2));
    }
    inline enum EventResult onScriptAddFilterToView(std::string const& a0){
        enum EventResult (ScriptEventListener::*rv)(std::string const&);
        *((void**)&rv) = dlsym("?onScriptAddFilterToView@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
        return (this->*rv)(std::forward<std::string const&>(a0));
    }
    inline enum EventResult onScriptRegisterSpatialView(std::string const& a0){
        enum EventResult (ScriptEventListener::*rv)(std::string const&);
        *((void**)&rv) = dlsym("?onScriptRegisterSpatialView@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
        return (this->*rv)(std::forward<std::string const&>(a0));
    }
    inline enum EventResult onScriptLoaded(std::string const& a0, unsigned __int64 a1){
        enum EventResult (ScriptEventListener::*rv)(std::string const&, unsigned __int64);
        *((void**)&rv) = dlsym("?onScriptLoaded@ScriptEventListener@@UEAA?AW4EventResult@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_K@Z");
        return (this->*rv)(std::forward<std::string const&>(a0), std::forward<unsigned __int64>(a1));
    }
    */

protected:

private:

};