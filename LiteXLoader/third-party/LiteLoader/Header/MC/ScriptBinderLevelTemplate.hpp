// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptBinderLevelTemplate {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTBINDERLEVELTEMPLATE
public:
    class ScriptBinderLevelTemplate& operator=(class ScriptBinderLevelTemplate const&) = delete;
    ScriptBinderLevelTemplate(class ScriptBinderLevelTemplate const&) = delete;
#endif

public:
    /*0*/ virtual ~ScriptBinderLevelTemplate();
    /*1*/ virtual std::string const& getTemplateIdentifier() const;
    /*2*/ virtual void applyTemplate(class ScriptObjectBinder&) const;
    MCAPI ScriptBinderLevelTemplate();
    MCAPI static std::unique_ptr<class ScriptObjectBinder> build(class entt::basic_registry<enum entt::entity>&, enum entt::entity);

protected:

private:

};