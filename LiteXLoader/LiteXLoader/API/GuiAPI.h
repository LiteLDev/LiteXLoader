#pragma once
#include <ScriptX/ScriptX.h>
#include <Kernel/ThirdParty.h>
using namespace script;

//////////////////// Classes ////////////////////

class SimpleFormClass : public ScriptClass
{
private:
    JSON_ROOT form;
    unsigned buttonCount = 0;

public:
    SimpleFormClass();

    JSON_ROOT *get()
    {
        return &form;
    }

    std::map<unsigned, script::Global<Function>> buttonCallbacks;

    static Local<Object> newForm();
    static JSON_ROOT* extract(Local<Value> v);

    Local<Value> setTitle(const Arguments& args);
    Local<Value> setContent(const Arguments& args);

    Local<Value> addButton(const Arguments& args);
};
extern ClassDefine<SimpleFormClass> SimpleFormClassBuilder;


class CustomFormClass : public ScriptClass
{
private:
    JSON_ROOT form;

public:
    CustomFormClass();

    JSON_ROOT* get()
    {
        return &form;
    }

    static Local<Object> newForm();
    static JSON_ROOT* extract(Local<Value> v);

    Local<Value> setTitle(const Arguments& args);

    Local<Value> addLabel(const Arguments& args);
    Local<Value> addInput(const Arguments& args);
    Local<Value> addSwitch(const Arguments& args);
    Local<Value> addDropdown(const Arguments& args);
    Local<Value> addSlider(const Arguments& args);
    Local<Value> addStepSlider(const Arguments& args);
};
extern ClassDefine<CustomFormClass> CustomFormClassBuilder;

// 表单回调
bool CallFormCallback(Player* player, unsigned formId, const std::string& data);