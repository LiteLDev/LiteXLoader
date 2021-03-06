// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "BaseMoveToGoal.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class MoveToPOIGoal : public BaseMoveToGoal {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MOVETOPOIGOAL
public:
    class MoveToPOIGoal& operator=(class MoveToPOIGoal const&) = delete;
    MoveToPOIGoal(class MoveToPOIGoal const&) = delete;
    MoveToPOIGoal() = delete;
#endif

public:
    /*0*/ virtual ~MoveToPOIGoal();
    /*1*/ virtual bool canUse();
    /*2*/ virtual void __unk_vfn_0();
    /*3*/ virtual void stop();
    /*4*/ virtual void tick();
    /*5*/ virtual void appendDebugInfo(std::string&) const;
    /*6*/ virtual void __unk_vfn_1();
    /*7*/ virtual void __unk_vfn_2();
    /*8*/ virtual bool isValidTarget(class BlockSource&, class BlockPos const&);
    /*9*/ virtual void _moveToBlock();
    /*10*/ virtual class Vec3 _getTargetPosition() const;
    /*11*/ virtual unsigned __int64 _getRepathTime() const;
    /*12*/ virtual bool getPOI(enum POIType);
    /*13*/ virtual class std::weak_ptr<class POIInstance> _getOwnedPOI(enum POIType) const;
    /*
    inline  ~MoveToPOIGoal(){
         (MoveToPOIGoal::*rv)();
        *((void**)&rv) = dlsym("??1MoveToPOIGoal@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI MoveToPOIGoal(class Mob&, float, enum POIType, float);

protected:
    MCAPI bool _canReachPOI(class Vec3 const&, float, bool);

private:
    MCAPI void _updatePOIBooking();

};