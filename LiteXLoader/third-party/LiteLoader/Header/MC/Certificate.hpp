// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Certificate {

#define AFTER_EXTRA
// Add Member There
    char filler[128];

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CERTIFICATE
public:
    class Certificate& operator=(class Certificate const&) = delete;
    Certificate() = delete;
#endif

public:
    MCAPI Certificate(class Certificate const&);
    MCAPI __int64 getExpirationDate() const;
    MCAPI class Json::Value getExtraData(std::string const&, class Json::Value const&) const;
    MCAPI std::string getIdentityPublicKey() const;
    MCAPI __int64 getNotBeforeDate() const;
    MCAPI bool isValid() const;
    MCAPI std::string toString() const;
    MCAPI bool validate(__int64);
    MCAPI ~Certificate();

protected:

private:
    MCAPI Certificate(class UnverifiedCertificate const&, std::unique_ptr<class Certificate>);

};