// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class FeatureToggles {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_FEATURETOGGLES
public:
    class FeatureToggles& operator=(class FeatureToggles const&) = delete;
    FeatureToggles(class FeatureToggles const&) = delete;
    FeatureToggles() = delete;
#endif

public:
    /*0*/ virtual ~FeatureToggles();
    /*
    inline  ~FeatureToggles(){
         (FeatureToggles::*rv)();
        *((void**)&rv) = dlsym("??1FeatureToggles@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI FeatureToggles(class AppPlatform&);
    MCAPI class Option* get(enum FeatureOptionID);
    MCAPI bool isEnabled(enum FeatureOptionID) const;

protected:

private:
    MCAPI void _initialize(class AppPlatform&);
    MCAPI void _registerFeature(enum FeatureOptionTabID, enum FeatureOptionID, std::string const&, std::string const&, bool, enum FeatureOptionID, class std::function<void (class Option& )>, class std::function<void (bool& )>);
    MCAPI void _registerFeatures();
    MCAPI void _setupDependencies();
    MCAPI static std::unique_ptr<class FeatureToggles> mFeatureToggles;

};