// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class CommandOriginLoader {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_COMMANDORIGINLOADER
public:
    class CommandOriginLoader& operator=(class CommandOriginLoader const&) = delete;
    CommandOriginLoader(class CommandOriginLoader const&) = delete;
    CommandOriginLoader() = delete;
#endif

public:
    /*0*/ virtual ~CommandOriginLoader();
    /*1*/ virtual std::unique_ptr<class CommandOrigin> load(class CompoundTag const&);
    /*
    inline  ~CommandOriginLoader(){
         (CommandOriginLoader::*rv)();
        *((void**)&rv) = dlsym("??1CommandOriginLoader@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI CommandOriginLoader(class ServerLevel&);
    MCAPI static std::unique_ptr<class CommandOrigin> load(class CompoundTag const&, class ServerLevel&);

protected:

private:

};