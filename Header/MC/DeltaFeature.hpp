// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Feature.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class DeltaFeature : public Feature {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_DELTAFEATURE
public:
    class DeltaFeature& operator=(class DeltaFeature const&) = delete;
    DeltaFeature(class DeltaFeature const&) = delete;
    DeltaFeature() = delete;
#endif

public:
    /*0*/ virtual ~DeltaFeature();
    /*1*/ virtual void __unk_vfn_0();
    /*2*/ virtual bool place(class BlockSource&, class BlockPos const&, class Random&) const;

protected:

private:
    MCAPI class std::optional<class BlockPos> _findDeltaLevel(class BlockSource&, class BlockPos) const;
    MCAPI bool _isValidPlacement(class BlockSource&, class BlockPos) const;

};