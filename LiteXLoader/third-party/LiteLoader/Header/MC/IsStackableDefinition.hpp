// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "JsonUtil.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

struct IsStackableDefinition {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ISSTACKABLEDEFINITION
public:
    struct IsStackableDefinition& operator=(struct IsStackableDefinition const&) = delete;
    IsStackableDefinition(struct IsStackableDefinition const&) = delete;
    IsStackableDefinition() = delete;
#endif

public:
    MCAPI void initialize(class EntityContext&);
    MCAPI void uninitialize(class EntityContext&);

protected:

private:

};