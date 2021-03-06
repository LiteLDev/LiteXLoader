// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ActorDamageSource.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ActorDamageByActorSource : public ActorDamageSource {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ACTORDAMAGEBYACTORSOURCE
public:
    class ActorDamageByActorSource& operator=(class ActorDamageByActorSource const&) = delete;
    ActorDamageByActorSource(class ActorDamageByActorSource const&) = delete;
    ActorDamageByActorSource() = delete;
#endif

public:
    /*0*/ virtual ~ActorDamageByActorSource();
    /*1*/ virtual bool isEntitySource() const;
    /*2*/ virtual void __unk_vfn_0();
    /*3*/ virtual bool isBlockSource() const;
    /*4*/ virtual struct std::pair<std::string, std::vector<std::string> > getDeathMessage(std::string, class Actor*) const;
    /*5*/ virtual bool getIsCreative() const;
    /*6*/ virtual bool getIsWorldBuilder() const;
    /*7*/ virtual void __unk_vfn_1();
    /*8*/ virtual void __unk_vfn_2();
    /*9*/ virtual enum ActorCategory getEntityCategories() const;
    /*10*/ virtual bool getDamagingEntityIsCreative() const;
    /*11*/ virtual bool getDamagingEntityIsWorldBuilder() const;
    /*12*/ virtual struct ActorUniqueID getDamagingEntityUniqueID() const;
    /*13*/ virtual enum ActorType getDamagingEntityType() const;
    /*14*/ virtual enum ActorCategory getDamagingEntityCategories() const;
    /*15*/ virtual std::unique_ptr<class ActorDamageSource> clone() const;
    /*
    inline  ~ActorDamageByActorSource(){
         (ActorDamageByActorSource::*rv)();
        *((void**)&rv) = dlsym("??1ActorDamageByActorSource@@UEAA@XZ");
        return (this->*rv)();
    }
    inline enum ActorType getEntityType() const{
        enum ActorType (ActorDamageByActorSource::*rv)() const;
        *((void**)&rv) = dlsym("?getEntityType@ActorDamageByActorSource@@UEBA?AW4ActorType@@XZ");
        return (this->*rv)();
    }
    inline struct ActorUniqueID getEntityUniqueID() const{
        struct ActorUniqueID (ActorDamageByActorSource::*rv)() const;
        *((void**)&rv) = dlsym("?getEntityUniqueID@ActorDamageByActorSource@@UEBA?AUActorUniqueID@@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ActorDamageByActorSource(class Actor&, enum ActorDamageCause);

protected:

private:

};