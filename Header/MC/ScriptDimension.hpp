// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Scripting.hpp"
#include "ScriptObject.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptDimension : public ScriptObject {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTDIMENSION
public:
    class ScriptDimension& operator=(class ScriptDimension const&) = delete;
    ScriptDimension(class ScriptDimension const&) = delete;
    ScriptDimension() = delete;
#endif

public:
    /*0*/ virtual ~ScriptDimension();
    /*
    inline  ~ScriptDimension(){
         (ScriptDimension::*rv)();
        *((void**)&rv) = dlsym("??1ScriptDimension@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI class Scripting::Result<void> createExplosion(class Vec3 const&, float, struct Scripting::TypedObjectHandle<struct ScriptExplosionOptions>) const;
    MCAPI class Scripting::StrongTypedObjectHandle<class ScriptBlock> getBlock(class Scripting::WeakLifetimeScope, class BlockPos const&);
    MCAPI class Dimension* getDimension() const;
    MCAPI std::vector<class Scripting::StrongTypedObjectHandle<class ScriptActor>> getEntitiesAtBlockLocation(class BlockPos const&) const;
    MCAPI bool isEmpty(class BlockPos const&) const;
    MCAPI class Scripting::Result<class Scripting::StrongTypedObjectHandle<class ScriptActor> > spawnEntity(std::string const&, class BlockPos const&) const;
    MCAPI static class Scripting::ClassBindingBuilder<class ScriptDimension> bind(struct Scripting::Version);
    MCAPI static class Scripting::StrongTypedObjectHandle<class ScriptDimension> getOrCreateHandle(class Dimension&, class Scripting::WeakLifetimeScope const&);
    MCAPI static class Scripting::StrongTypedObjectHandle<class ScriptDimension> getOrCreateHandle(class AutomaticID<class Dimension, int>, class Level&, class Scripting::WeakLifetimeScope const&);

protected:

private:

};