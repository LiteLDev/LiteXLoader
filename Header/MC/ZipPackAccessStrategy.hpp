// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Core.hpp"
#include "Bedrock.hpp"
#include "PackAccessStrategy.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ZipPackAccessStrategy : public PackAccessStrategy {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ZIPPACKACCESSSTRATEGY
public:
    class ZipPackAccessStrategy& operator=(class ZipPackAccessStrategy const&) = delete;
    ZipPackAccessStrategy(class ZipPackAccessStrategy const&) = delete;
    ZipPackAccessStrategy() = delete;
#endif

public:
    /*0*/ virtual ~ZipPackAccessStrategy();
    /*1*/ virtual unsigned __int64 getPackSize() const;
    /*2*/ virtual class ResourceLocation const& getPackLocation() const;
    /*3*/ virtual std::string const& getPackName() const;
    /*4*/ virtual bool isWritable() const;
    /*5*/ virtual void setIsTrusted(bool);
    /*6*/ virtual bool isTrusted() const;
    /*7*/ virtual bool hasAsset(class Core::Path const&, bool) const;
    /*8*/ virtual bool hasFolder(class Core::Path const&) const;
    /*9*/ virtual bool getAsset(class Core::Path const&, std::string&, bool) const;
    /*10*/ virtual bool deleteAsset(class Core::PathBuffer<std::string > const&);
    /*11*/ virtual bool writeAsset(class Core::Path const&, std::string const&);
    /*12*/ virtual void forEachIn(class Core::Path const&, class std::function<void (class Core::Path const& )>, bool) const;
    /*13*/ virtual void forEachInAssetSet(class Core::Path const&, class std::function<void (class Core::Path const& )>) const;
    /*14*/ virtual enum PackAccessStrategyType getStrategyType() const;
    /*15*/ virtual class Core::PathBuffer<std::string > const& getSubPath() const;
    /*16*/ virtual std::unique_ptr<class PackAccessStrategy> createSubPack(class Core::Path const&) const;
    /*17*/ virtual bool canRecurse() const;
    /*18*/ virtual void unload();
    /*19*/ virtual class ContentIdentity readContentIdentity() const;
    /*
    inline  ~ZipPackAccessStrategy(){
         (ZipPackAccessStrategy::*rv)();
        *((void**)&rv) = dlsym("??1ZipPackAccessStrategy@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ZipPackAccessStrategy(class gsl::not_null<class Bedrock::NonOwnerPointer<class IFileAccess> > const&, class ResourceLocation const&, class Core::Path const&);

protected:

private:
    MCAPI bool _tryReadFromPendingQueue(class Core::Path const&, std::string&) const;

};