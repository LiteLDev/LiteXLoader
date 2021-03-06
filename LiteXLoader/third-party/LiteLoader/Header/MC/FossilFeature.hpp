// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Feature.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class FossilFeature : public Feature {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_FOSSILFEATURE
public:
    class FossilFeature& operator=(class FossilFeature const&) = delete;
    FossilFeature(class FossilFeature const&) = delete;
    FossilFeature() = delete;
#endif

public:
    /*0*/ virtual ~FossilFeature();
    /*1*/ virtual void __unk_vfn_0();
    /*2*/ virtual bool place(class BlockSource&, class BlockPos const&, class Random&) const;
    MCAPI static std::string const* const STRUCTURE_LOCATION_FOSSIL;
    MCAPI static std::string const* const STRUCTURE_LOCATION_FOSSIL_COAL;

protected:

private:

};