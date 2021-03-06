// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "JsonUtil.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

struct EquipmentTableDefinition {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_EQUIPMENTTABLEDEFINITION
public:
    struct EquipmentTableDefinition& operator=(struct EquipmentTableDefinition const&) = delete;
    EquipmentTableDefinition(struct EquipmentTableDefinition const&) = delete;
    EquipmentTableDefinition() = delete;
#endif

public:
    MCAPI void deserializeData(struct DeserializeDataParams);
    MCAPI void serializeData(class Json::Value&) const;
    MCAPI ~EquipmentTableDefinition();

protected:

private:

};