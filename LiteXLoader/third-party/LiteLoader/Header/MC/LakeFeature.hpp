// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Feature.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LakeFeature : public Feature {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LAKEFEATURE
public:
    class LakeFeature& operator=(class LakeFeature const&) = delete;
    LakeFeature(class LakeFeature const&) = delete;
    LakeFeature() = delete;
#endif

public:
    /*0*/ virtual ~LakeFeature();
    /*1*/ virtual void __unk_vfn_0();
    /*2*/ virtual ~LakeFeature();
    /*
    inline  ~LakeFeature(){
         (LakeFeature::*rv)();
        *((void**)&rv) = dlsym("??1LakeFeature@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI LakeFeature(class Block const&);

protected:

private:
    MCAPI bool _check(class BlockPos const&, class gsl::span<bool, 2048>) const;

};