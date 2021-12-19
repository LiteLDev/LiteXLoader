// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class AppPlatformListener {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_APPPLATFORMLISTENER
public:
    class AppPlatformListener& operator=(class AppPlatformListener const&) = delete;
    AppPlatformListener(class AppPlatformListener const&) = delete;
#endif

public:
    /*0*/ virtual ~AppPlatformListener();
    /*
    inline void onResizeEnd(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onResizeEnd@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onAppPreSuspended(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppPreSuspended@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onAppFocusGained(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppFocusGained@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onAppPaused(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppPaused@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onResizeBegin(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onResizeBegin@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onOperationModeChanged(enum OperationMode a0){
        void (AppPlatformListener::*rv)(enum OperationMode);
        *((void**)&rv) = dlsym("?onOperationModeChanged@AppPlatformListener@@UEAAXW4OperationMode@@@Z");
        return (this->*rv)(std::forward<enum OperationMode>(a0));
    }
    inline void onAppUnpaused(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppUnpaused@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onAppFocusLost(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppFocusLost@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onPushNotificationReceived(class PushNotificationMessage const& a0){
        void (AppPlatformListener::*rv)(class PushNotificationMessage const&);
        *((void**)&rv) = dlsym("?onPushNotificationReceived@AppPlatformListener@@UEAAXAEBVPushNotificationMessage@@@Z");
        return (this->*rv)(std::forward<class PushNotificationMessage const&>(a0));
    }
    inline void onAppSuspended(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppSuspended@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onPerformanceModeChanged(bool a0){
        void (AppPlatformListener::*rv)(bool);
        *((void**)&rv) = dlsym("?onPerformanceModeChanged@AppPlatformListener@@UEAAX_N@Z");
        return (this->*rv)(std::forward<bool>(a0));
    }
    inline void onDeviceLost(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onDeviceLost@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onLowMemory(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onLowMemory@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onAppTerminated(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppTerminated@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline void onAppResumed(){
        void (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("?onAppResumed@AppPlatformListener@@UEAAXXZ");
        return (this->*rv)();
    }
    inline  ~AppPlatformListener(){
         (AppPlatformListener::*rv)();
        *((void**)&rv) = dlsym("??1AppPlatformListener@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI AppPlatformListener();
    MCAPI void initListener(float);
    MCAPI void terminate();

protected:

private:

};