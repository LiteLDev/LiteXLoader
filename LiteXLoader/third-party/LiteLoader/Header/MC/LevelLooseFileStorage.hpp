// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Core.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LevelLooseFileStorage {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LEVELLOOSEFILESTORAGE
public:
    class LevelLooseFileStorage& operator=(class LevelLooseFileStorage const&) = delete;
    LevelLooseFileStorage(class LevelLooseFileStorage const&) = delete;
    LevelLooseFileStorage() = delete;
#endif

public:
    MCAPI LevelLooseFileStorage(class Core::Path const&, class ContentIdentity const&, class IContentKeyProvider const&);
    MCAPI std::unique_ptr<class PackAccessStrategy> getAccessStrategy() const;

protected:

private:

};