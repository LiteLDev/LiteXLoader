// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class BiomeRegistryMergeStrategy {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_BIOMEREGISTRYMERGESTRATEGY
public:
    class BiomeRegistryMergeStrategy& operator=(class BiomeRegistryMergeStrategy const&) = delete;
    BiomeRegistryMergeStrategy(class BiomeRegistryMergeStrategy const&) = delete;
    BiomeRegistryMergeStrategy() = delete;
#endif

public:
    /*0*/ virtual ~BiomeRegistryMergeStrategy();
    /*1*/ virtual void mergeFiles(std::vector<class LoadedResourceData> const&);
    /*
    inline  ~BiomeRegistryMergeStrategy(){
         (BiomeRegistryMergeStrategy::*rv)();
        *((void**)&rv) = dlsym("??1BiomeRegistryMergeStrategy@@UEAA@XZ");
        return (this->*rv)();
    }
    */

protected:

private:

};