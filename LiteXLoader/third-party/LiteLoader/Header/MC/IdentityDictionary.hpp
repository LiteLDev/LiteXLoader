// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class IdentityDictionary {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_IDENTITYDICTIONARY
public:
    class IdentityDictionary& operator=(class IdentityDictionary const&) = delete;
    IdentityDictionary(class IdentityDictionary const&) = delete;
#endif

public:
    MCAPI IdentityDictionary();
    MCAPI bool clearIdentity(struct ScoreboardId const&);
    MCAPI struct ScoreboardId const& convertFakeToReal(struct ScoreboardId const&, struct PlayerScoreboardId const&);
    MCAPI ~IdentityDictionary();

protected:

private:

};