// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "Monster.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Blaze : public Monster {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_BLAZE
public:
    class Blaze& operator=(class Blaze const&) = delete;
    Blaze(class Blaze const&) = delete;
    Blaze() = delete;
#endif

public:
    /*0*/ virtual ~Blaze();
    /*1*/ virtual bool isRuntimePredictedMovementEnabled() const;
    /*2*/ virtual void __unk_vfn_0();
    /*3*/ virtual class Vec3 getInterpolatedRidingOffset(float) const;
    /*4*/ virtual void __unk_vfn_1();
    /*5*/ virtual void normalTick();
    /*6*/ virtual float getRidingHeight();
    /*7*/ virtual void __unk_vfn_2();
    /*8*/ virtual void __unk_vfn_3();
    /*9*/ virtual float getCameraOffset() const;
    /*10*/ virtual void __unk_vfn_4();
    /*11*/ virtual float getBrightness(float) const;
    /*12*/ virtual void __unk_vfn_5();
    /*13*/ virtual void playerTouch(class Player&);
    /*14*/ virtual void __unk_vfn_6();
    /*15*/ virtual void __unk_vfn_7();
    /*16*/ virtual bool isDamageBlocked(class ActorDamageSource const&) const;
    /*17*/ virtual bool isOnFire() const;
    /*18*/ virtual void __unk_vfn_8();
    /*19*/ virtual void __unk_vfn_9();
    /*20*/ virtual void __unk_vfn_10();
    /*21*/ virtual void __unk_vfn_11();
    /*22*/ virtual bool isValidTarget(class Actor*) const;
    /*23*/ virtual void adjustDamageAmount(int&) const;
    /*24*/ virtual void onTame();
    /*25*/ virtual void onFailedTame();
    /*26*/ virtual void vehicleLanded(class Vec3 const&, class Vec3 const&);
    /*27*/ virtual void onBounceStarted(class BlockPos const&, class Block const&);
    /*28*/ virtual float getPickRadius();
    /*29*/ virtual void awardKillScore(class Actor&, int);
    /*30*/ virtual class HashedString const& queryEntityRenderer() const;
    /*31*/ virtual struct ActorUniqueID getSourceUniqueID() const;
    /*32*/ virtual int getPortalWaitTime() const;
    /*33*/ virtual bool canChangeDimensions() const;
    /*34*/ virtual void __unk_vfn_12();
    /*35*/ virtual struct ActorUniqueID getControllingPlayer() const;
    /*36*/ virtual bool canPickupItem(class ItemStack const&) const;
    /*37*/ virtual bool canBePulledIntoVehicle() const;
    /*38*/ virtual void __unk_vfn_13();
    /*39*/ virtual bool canSynchronizeNewEntity() const;
    /*40*/ virtual void __unk_vfn_14();
    /*41*/ virtual void __unk_vfn_15();
    /*42*/ virtual bool isWorldBuilder() const;
    /*43*/ virtual void __unk_vfn_16();
    /*44*/ virtual bool isAdventure() const;
    /*45*/ virtual bool canDestroyBlock(class Block const&) const;
    /*46*/ virtual void setAuxValue(int);
    /*47*/ virtual void stopSpinAttack();
    /*48*/ virtual void __unk_vfn_17();
    /*49*/ virtual void __unk_vfn_18();
    /*50*/ virtual void __unk_vfn_19();
    /*51*/ virtual void __unk_vfn_20();
    /*52*/ virtual void __unk_vfn_21();
    /*53*/ virtual void spawnAnim();
    /*54*/ virtual void travel(float, float, float);
    /*55*/ virtual void aiStep();
    /*56*/ virtual bool checkSpawnRules(bool);
    /*57*/ virtual int getItemUseDuration() const;
    /*58*/ virtual float getItemUseStartupProgress() const;
    /*59*/ virtual float getItemUseIntervalProgress() const;
    /*60*/ virtual void __unk_vfn_22();
    /*61*/ virtual bool isAlliedTo(class Mob*);
    /*62*/ virtual void __unk_vfn_23();
    /*63*/ virtual void sendArmorDamage(class std::bitset<4> const&);
    /*64*/ virtual void onBorn(class Actor&, class Actor&);
    /*65*/ virtual int getAttackTime();
    /*66*/ virtual void __unk_vfn_24();
    /*67*/ virtual void _serverAiMobStep();
    /*68*/ virtual void __unk_vfn_25();
    /*69*/ virtual bool isDarkEnoughToSpawn() const;
    /*
    inline bool useNewAi() const{
        bool (Blaze::*rv)() const;
        *((void**)&rv) = dlsym("?useNewAi@Blaze@@MEBA_NXZ");
        return (this->*rv)();
    }
    */
    MCAPI Blaze(class ActorDefinitionGroup*, struct ActorDefinitionIdentifier const&, class OwnerPtrT<struct EntityRefTraits> const&);

protected:

private:

};