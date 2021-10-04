#include "APIHelp.h"
#include "DataAPI.h"
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <Engine/EngineOwnData.h>
#include <Kernel/System.h>
#include <Kernel/Data.h>
#include <Kernel/Utils.h>

using namespace script;
using namespace std;


//////////////////// Class Definition ////////////////////

ClassDefine<void> DataClassBuilder =
    defineClass("data")
        .function("xuid2name", &DataClass::xuid2name)
        .function("name2xuid", &DataClass::name2xuid)
        .function("parseJson", &DataClass::parseJson)
        .function("toJson", &DataClass::toJson)
        .function("toMD5", &DataClass::toMD5)
        .function("toSHA1", &DataClass::toSHA1)
        .function("toBase64", &DataClass::toBase64)
        .function("fromBase64", &DataClass::fromBase64)

        //For Compatibility
        .function("openDB", &DataClass::openDB)
        .function("openConfig", &DataClass::openConfig)
        .build();

ClassDefine<void> MoneyClassBuilder =
    defineClass("money")
        .function("set", &MoneyClass::set)
        .function("get", &MoneyClass::get)
        .function("add", &MoneyClass::add)
        .function("reduce", &MoneyClass::reduce)
        .function("trans", &MoneyClass::trans)
        .function("getHistory", &MoneyClass::getHistory)
        .function("clearHistory", &MoneyClass::clearHistory)
        .build();

ClassDefine<DbClass> DbClassBuilder =
    defineClass<DbClass>("KVDatabase")
        .constructor(&DbClass::constructor)
        .instanceFunction("get", &DbClass::get)
        .instanceFunction("set", &DbClass::set)
        .instanceFunction("delete", &DbClass::del)
        .instanceFunction("close", &DbClass::close)
        .instanceFunction("listKey", &DbClass::listKey)
        .build();

ClassDefine<ConfJsonClass> ConfJsonClassBuilder =
    defineClass<ConfJsonClass>("JsonConfigFile")
        .constructor(&ConfJsonClass::constructor)
        .instanceFunction("init", &ConfJsonClass::init)
        .instanceFunction("get", &ConfJsonClass::get)
        .instanceFunction("set", &ConfJsonClass::set)
        .instanceFunction("delete", &ConfJsonClass::del)
        .instanceFunction("reload", selectOverloadedFunc<Local<Value> (ConfJsonClass::*)(const Arguments&)>(&ConfJsonClass::reload))
        .instanceFunction("close", selectOverloadedFunc<Local<Value>(ConfJsonClass::*)(const Arguments&)>(&ConfJsonClass::close))
        .instanceFunction("getPath", &ConfJsonClass::getPath)
        .instanceFunction("read", &ConfJsonClass::read)
        .instanceFunction("write", &ConfJsonClass::write)
        .build();

ClassDefine<ConfIniClass> ConfIniClassBuilder =
    defineClass<ConfIniClass>("IniConfigFile")
        .constructor(&ConfIniClass::constructor)
        .instanceFunction("init", &ConfIniClass::init)
        .instanceFunction("set", &ConfIniClass::set)
        .instanceFunction("getStr", &ConfIniClass::getStr)
        .instanceFunction("getInt", &ConfIniClass::getInt)
        .instanceFunction("getFloat", &ConfIniClass::getFloat)
        .instanceFunction("getBool", &ConfIniClass::getBool)
        .instanceFunction("delete", &ConfIniClass::del)
        .instanceFunction("reload", selectOverloadedFunc<Local<Value>(ConfIniClass::*)(const Arguments&)>(&ConfIniClass::reload))
        .instanceFunction("close", selectOverloadedFunc<Local<Value>(ConfIniClass::*)(const Arguments&)>(&ConfIniClass::close))
        .instanceFunction("getPath", &ConfIniClass::getPath)
        .instanceFunction("read", &ConfIniClass::read)
        .instanceFunction("write", &ConfIniClass::write)
        .build();


//////////////////// Classes Db ////////////////////

//生成函数
DbClass::DbClass(const Local<Object>& scriptObj, const string &dir) :ScriptClass(scriptObj)
{
    kvdb = Raw_NewDB(dir);
}

DbClass::DbClass(const string& dir)
    : ScriptClass(script::ScriptClass::ConstructFromCpp<DbClass>{})
{
    kvdb = Raw_NewDB(dir);
}

DbClass::~DbClass()
{
    if (isValid())
    {
        Raw_DBClose(kvdb);
        kvdb = nullptr;
    }
}

DbClass* DbClass::constructor(const Arguments& args)
{
    CHECK_ARGS_COUNT_C(args, 1);
    CHECK_ARG_TYPE_C(args[0], ValueKind::kString);

    try {
        auto res = new DbClass(args.thiz(), args[0].toStr());
        if (res->isValid())
            return res;
        else
            return nullptr;
    }
    CATCH_C("Fail in Open Database!");
}

Local<Value> DbClass::get(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        if (!isValid())
            return Local<Value>();

        string res;
        if(!Raw_DBGet(kvdb,args[0].asString().toString(),res))
            return Local<Value>();
        
        return JsonToValue(res);
    }
    CATCH("Fail in DbGet!")
}

Local<Value> DbClass::set(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        if (!isValid())
            return Local<Value>();

        return Boolean::newBoolean(Raw_DBSet(kvdb,args[0].asString().toString(),ValueToJson(args[1])));
    }
    CATCH("Fail in DbSet!")
}

Local<Value> DbClass::del(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        if (!isValid())
            return Local<Value>();

        return Boolean::newBoolean(Raw_DBDel(kvdb,args[0].asString().toString()));
    }
    CATCH("Fail in DbDel!")
}

Local<Value> DbClass::close(const Arguments& args)
{
    try
    {
        if (isValid())
        {
            Raw_DBClose(kvdb);
            kvdb = nullptr;
        }
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in DbClose!")
}

Local<Value> DbClass::listKey(const Arguments& args)
{
    try
    {
        if (!isValid())
            return Local<Value>();

        auto list = Raw_DBListKey(kvdb);
        Local<Array> arr = Array::newArray();
        for (auto& key : list)
        {
            arr.add(String::newString(key));
        }
        return arr;
    }
    CATCH("Fail in DbListKey!")
}


//////////////////// Classes ConfBase ////////////////////

ConfBaseClass::ConfBaseClass(const string& dir)
    :confPath(dir)
{ }

Local<Value> ConfBaseClass::getPath(const Arguments& args)
{
    try
    {
        return String::newString(confPath);
    }
    CATCH("Fail in confGetPath!")
}

Local<Value> ConfBaseClass::read(const Arguments& args)
{
    try
    {
        string content;
        if (!Raw_FileReadFrom(confPath, content))
            return Local<Value>();
        else
            return String::newString(content);
    }
    CATCH("Fail in confRead!")
}

//////////////////// Classes ConfJson ////////////////////

//生成函数
ConfJsonClass::ConfJsonClass(const Local<Object>& scriptObj, const string& path, const string& defContent)
    :ScriptClass(scriptObj), ConfBaseClass(path)
{
    jsonConf = Raw_JsonOpen(path, defContent);
}

ConfJsonClass::ConfJsonClass(const string& path, const string& defContent)
    :ScriptClass(ScriptClass::ConstructFromCpp<ConfJsonClass>{}), ConfBaseClass(path)
{
    jsonConf = Raw_JsonOpen(path, defContent);
}

ConfJsonClass::~ConfJsonClass()
{
    close();
}

ConfJsonClass* ConfJsonClass::constructor(const Arguments& args)
{
    CHECK_ARGS_COUNT_C(args, 1);
    CHECK_ARG_TYPE_C(args[0], ValueKind::kString);
    if (args.size() >= 2)
        CHECK_ARG_TYPE_C(args[1], ValueKind::kString);

    try {
        string path = args[0].toStr();
        if (path.empty())
            return nullptr;

        if (args.size() >= 2)
            return new ConfJsonClass(args.thiz(), path, args[1].toStr());
        else
            return new ConfJsonClass(args.thiz(), path, "{}");
    }
    CATCH_C("Fail in Open JsonConfigFile!");
}

Local<Value> ConfJsonClass::init(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        return JsonToValue(jsonConf.at(args[0].toStr()));
    }
    catch (const std::out_of_range& e)
    {
        jsonConf[args[0].toStr()] = JSON_VALUE::parse(ValueToJson(args[1]));
        flush();
        return args[1];
    }
    catch (const JSON_VALUE::exception& e)
    {
        jsonConf[args[0].toStr()] = JSON_VALUE::parse(ValueToJson(args[1]));
        flush();
        return args[1];
    }
    CATCH("Fail in confJsonSet!");
}

Local<Value> ConfJsonClass::get(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        return JsonToValue(jsonConf.at(args[0].toStr()));
    }
    catch (const std::out_of_range& e)
    {
        return args.size() >= 2 ? args[1] : Local<Value>();
    }
    catch (const JSON_VALUE::exception& e)
    {
        return args.size() >= 2 ? args[1] : Local<Value>();
    }
    CATCH("Fail in confJsonGet!")
}

Local<Value> ConfJsonClass::set(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        jsonConf[args[0].toStr()] = JSON_VALUE::parse(ValueToJson(args[1]));
        return Boolean::newBoolean(flush());
    }
    catch (const JSON_VALUE::exception& e)
    {
        return Boolean::newBoolean(false);
    }
    CATCH("Fail in confJsonSet!");
}

Local<Value> ConfJsonClass::del(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        if (jsonConf.erase(args[0].toStr()) <= 0)
            return Boolean::newBoolean(false);

        return Boolean::newBoolean(flush());
    }
    catch (const JSON_VALUE::exception& e)
    {
        return Boolean::newBoolean(false);
    }
    CATCH("Fail in confJsonDelete!");
}

Local<Value> ConfJsonClass::reload(const Arguments& args)
{
    try
    {
        return Boolean::newBoolean(reload());
    }
    catch (const JSON_VALUE::exception& e)
    {
        ERROR("Fail to parse json content in file!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    CATCH("Fail in confJsonReload!");
}

Local<Value> ConfJsonClass::close(const Arguments& args)
{
    try
    {
        return Boolean::newBoolean(close());
    }
    CATCH("Fail in confJsonClose!");
}

Local<Value> ConfJsonClass::write(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        bool res = Raw_FileWriteTo(confPath, args[0].toStr());
        reload();
        return Boolean::newBoolean(res);
    }
    CATCH("Fail in confJsonWrite!");
}

bool ConfJsonClass::flush()
{
    ofstream jsonFile(confPath);
    if (jsonFile.is_open())
    {
        jsonFile << jsonConf.dump(4);
        jsonFile.close();
        return true;
    }
    else
        return false;
}

bool ConfJsonClass::close()
{
    reload();
    return true;
}

bool ConfJsonClass::reload()
{
    string jsonTexts;
    if (!Raw_FileReadFrom(confPath, jsonTexts))
        return false;

    jsonConf = JSON_VALUE::parse(jsonTexts);
    return true;
}


//////////////////// Classes ConfIni ////////////////////

//生成函数
ConfIniClass::ConfIniClass(const Local<Object>& scriptObj, const string& path, const string& defContent)
    :ScriptClass(scriptObj), ConfBaseClass(path)
{
    iniConf = Raw_IniOpen(path, defContent);
}

ConfIniClass::ConfIniClass(const string& path, const string& defContent)
    :ScriptClass(ScriptClass::ConstructFromCpp<ConfIniClass>{}), ConfBaseClass(path)
{
    iniConf = Raw_IniOpen(path, defContent);
}

ConfIniClass::~ConfIniClass()
{
    close();
}

ConfIniClass* ConfIniClass::constructor(const Arguments& args)
{
    CHECK_ARGS_COUNT_C(args, 1);
    CHECK_ARG_TYPE_C(args[0], ValueKind::kString);
    if (args.size() >= 2)
        CHECK_ARG_TYPE_C(args[1], ValueKind::kString);

    try {
        string path = args[0].toStr();
        if (path.empty())
            return nullptr;

        if (args.size() >= 2)
            return new ConfIniClass(args.thiz(), path, args[1].toStr());
        else
            return new ConfIniClass(args.thiz(), path, "");
    }
    CATCH_C("Fail in Open JsonConfigFile!");
}

bool ConfIniClass::flush()
{
    return iniConf->SaveFile(iniConf->filePath.c_str(), true);
}

bool ConfIniClass::close()
{
    if (isValid())
    {
        reload();
        Raw_IniClose(iniConf);
        iniConf = nullptr;
    }
    return true;
}
bool ConfIniClass::reload()
{
    if (!isValid())
        return false;

    Raw_IniClose(iniConf);
    iniConf = Raw_IniOpen(confPath);
    return true;
}

Local<Value> ConfIniClass::init(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 3);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);

    try
    {
        if (!isValid())
            return Local<Value>();

        string section = args[0].toStr();
        string key = args[1].toStr();
        Local<Value> res;

        switch (args[2].getKind())
        {
        case ValueKind::kString:
        {
            string def = args[2].toStr();
            string data = Raw_IniGetString(iniConf, section, key, def);
            if (data == def)
            {
                Raw_IniSetString(iniConf, section, key, def);
                flush();
            }
            res = String::newString(data);
            break;
        }
        case ValueKind::kNumber:
        {
            if (CheckIsFloat(args[2]))
            {
                //Float
                float def = args[2].asNumber().toFloat();
                float data = Raw_IniGetFloat(iniConf, section, key, def);
                if (data == def)
                {
                    Raw_IniSetFloat(iniConf, section, key, def);
                    flush();
                }
                res = Number::newNumber(data);
            }
            else
            {
                //Int
                int def = args[2].toInt();
                int data = Raw_IniGetInt(iniConf, section, key, def);
                if (data == def)
                {
                    Raw_IniSetInt(iniConf, section, key, def);
                    flush();
                }
                res = Number::newNumber(data);
            }
            break;
        }
        case ValueKind::kBoolean:
        {
            bool def = args[2].asBoolean().value();
            bool data = Raw_IniGetBool(iniConf, section, key, def);
            if (data == def)
            {
                Raw_IniSetBool(iniConf, section, key, def);
                flush();
            }
            res = Boolean::newBoolean(data);
            break;
        }
        default:
            ERROR("Ini file don't support this type of data!");
            return Local<Value>();
            break;
        }
        return res;
    }
    CATCH("Fail in confIniInit!")
}

Local<Value> ConfIniClass::set(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 3);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);

    try
    {
        if (!isValid())
            return Local<Value>();
        
        string section = args[0].toStr();
        string key = args[1].toStr();
        switch (args[2].getKind())
        {
        case ValueKind::kString:
            Raw_IniSetString(iniConf, section, key, args[2].toStr());
            break;
        case ValueKind::kNumber:
            if (CheckIsFloat(args[2]))
                Raw_IniSetFloat(iniConf, section, key, args[2].asNumber().toFloat());
            else
                Raw_IniSetInt(iniConf, section, key, args[2].toInt());
            break;
        case ValueKind::kBoolean:
            Raw_IniSetBool(iniConf, section, key, args[2].asBoolean().value());
            break;
        default:
            ERROR("Ini file don't support this type of data!");
            return Local<Value>();
            break;
        }
        flush();
        return Boolean::newBoolean(true);
    }
    CATCH("Fail in confIniSet!")
}

Local<Value> ConfIniClass::getStr(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    if (args.size() >= 3)
        CHECK_ARG_TYPE(args[2], ValueKind::kString)

    try
    {
        if (!isValid())
            return Local<Value>();

        return String::newString(Raw_IniGetString(iniConf, args[0].toStr(), args[1].toStr(), 
            args.size() >= 3 ? args[2].toStr() : ""));
    }
    CATCH("Fail in confIniGetStr!")
}

Local<Value> ConfIniClass::getInt(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    if (args.size() >= 3)
        CHECK_ARG_TYPE(args[2], ValueKind::kNumber)

    try
    {
        if (!isValid())
            return Local<Value>();

        return Number::newNumber(Raw_IniGetInt(iniConf, args[0].toStr(), args[1].toStr(), 
            args.size() >= 3 ? args[2].asNumber().toInt32() : 0));
    }
    CATCH("Fail in ConfIniGetInt!");
}

Local<Value> ConfIniClass::getFloat(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    if (args.size() >= 3)
        CHECK_ARG_TYPE(args[2], ValueKind::kNumber);

    try
    {
        if (!isValid())
            return Local<Value>();

        return Number::newNumber(Raw_IniGetFloat(iniConf, args[0].toStr(), args[1].toStr(), 
            args.size() >= 3 ? (float)args[2].asNumber().toDouble() : 0.0));
    }
    CATCH("Fail in ConfIniGetFloat!");
}

Local<Value> ConfIniClass::getBool(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    if (args.size() >= 3)
        CHECK_ARG_TYPE(args[2], ValueKind::kBoolean);

    try
    {
        if (!isValid())
            return Local<Value>();

        return Boolean::newBoolean(Raw_IniGetBool(iniConf, args[0].toStr(), args[1].toStr(), 
            args.size() >= 3 ? args[2].asBoolean().value() : false));
    }
    CATCH("Fail in ConfIniGetBool");
}

Local<Value> ConfIniClass::del(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);

    try
    {
        if (!isValid())
            return Local<Value>();

        bool res = Raw_IniDeleteKey(iniConf, args[0].toStr(), args[1].toStr());
        flush();
        return Boolean::newBoolean(res);
    }
    CATCH("Fail in confIniDelete!");
}

Local<Value> ConfIniClass::reload(const Arguments& args)
{
    try
    {
        return Boolean::newBoolean(reload());
    }
    CATCH("Fail in confReload!");
}

Local<Value> ConfIniClass::write(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        bool res = Raw_FileWriteTo(confPath, args[0].toStr());
        reload();
        return Boolean::newBoolean(res);
    }
    CATCH("Fail in confIniWrite!");
}

Local<Value> ConfIniClass::close(const Arguments& args)
{
    try
    {
        return Boolean::newBoolean(close());
    }
    CATCH("Fail in confClose!");
}


//////////////////// APIs ////////////////////

Local<Value> MoneyClass::set(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

    try
    {
        return Boolean::newBoolean(Raw_SetMoney(stoull(args[0].toStr()), args[1].asNumber().toInt64()));
    }
    catch (const std::invalid_argument& e)
    {
        ERROR("Bad argument in MoneySet!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    catch (const std::out_of_range& e)
    {
        ERROR("Bad argument in MoneySet!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    CATCH("Fail in MoneySet!");
}

Local<Value> MoneyClass::get(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        return Number::newNumber(Raw_GetMoney(stoull(args[0].toStr())));
    }
    catch (const std::invalid_argument& e)
    {
        ERROR("Bad argument in MoneyGet!");
        ERRPRINT(e.what());
        return Number::newNumber(0);
    }
    catch (const std::out_of_range& e)
    {
        ERROR("Bad argument in MoneyGet!");
        ERRPRINT(e.what());
        return Number::newNumber(0);
    }
    CATCH("Fail in MoneyGet!");
}

Local<Value> MoneyClass::add(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

    try
    {
        return Boolean::newBoolean(Raw_AddMoney(stoull(args[0].toStr()), args[1].asNumber().toInt64()));
    }
    catch (const std::invalid_argument& e)
    {
        ERROR("Bad argument in MoneyAdd!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    catch (const std::out_of_range& e)
    {
        ERROR("Bad argument in MoneyAdd!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    CATCH("Fail in MoneyAdd!");
}

Local<Value> MoneyClass::reduce(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

    try
    {
        return Boolean::newBoolean(Raw_ReduceMoney(stoull(args[0].toStr()), args[1].asNumber().toInt64()));
    }
    catch (const std::invalid_argument& e)
    {
        ERROR("Bad argument in MoneyReduce!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    catch (const std::out_of_range& e)
    {
        ERROR("Bad argument in MoneyReduce!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    CATCH("Fail in MoneyReduce!");
}

Local<Value> MoneyClass::trans(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 3);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kString);
    CHECK_ARG_TYPE(args[2], ValueKind::kNumber);

    try
    {
        string note = "";
        if (args.size() >= 4 && args[3].getKind() == ValueKind::kString)
            note = args[3].toStr();
        return Boolean::newBoolean(Raw_TransMoney(stoull(args[0].toStr()), stoull(args[1].toStr()),
                args[2].asNumber().toInt64(), note));
    }
    catch (const std::invalid_argument& e)
    {
        ERROR("Bad argument in MoneyTrans!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    catch (const std::out_of_range& e)
    {
        ERROR("Bad argument in MoneyTrans!");
        ERRPRINT(e.what());
        return Boolean::newBoolean(false);
    }
    CATCH("Fail in MoneyTrans!");
}

Local<Value> MoneyClass::getHistory(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 2);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

    try
    {
        string res{ Raw_GetMoneyHist(stoull(args[0].toStr()), args[1].asNumber().toInt64()) };
        auto list = SplitStrWithPattern(res, "\n");
        // from -> to money time (note)

        Local<Array> arr = Array::newArray();

        string from, to, time1, time2, note, tmp;
        long long money;
        for(auto &str : list)
        {
            if (str.back() == '\n')
                str.pop_back();

            istringstream sin(str);
            Local<Object> obj = Object::newObject();

            note.clear();
            sin >> from >> tmp >> to >> money >> time1 >> time2;
            sin.get();
            getline(sin, note);
            if (note.front() == '(')
                note.erase(0, 1);
            if (note.back() == '\n')
                note.pop_back();
            if (note.back() == ')')
                note.pop_back();

            time1 += " " + time2;

            obj.set("from", String::newString(from));
            obj.set("to", String::newString(to));
            obj.set("money", Number::newNumber(money));
            obj.set("time", String::newString(time1));
            obj.set("note", String::newString(note));
            arr.add(obj);
        }
        return arr;
    }
    catch (const std::invalid_argument& e)
    {
        ERROR("Bad argument in MoneyGetHintory!");
        ERRPRINT(e.what());
        return Local<Value>();
    }
    catch (const std::out_of_range& e)
    {
        ERROR("Bad argument in MoneyGetHintory!");
        ERRPRINT(e.what());
        return Local<Value>();
    }
    CATCH("Fail in MoneyGetHintory!");
}

Local<Value> MoneyClass::clearHistory(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kNumber);

    try
    {
        return Boolean::newBoolean(Raw_ClearMoneyHist(args[0].asNumber().toInt64()));
    }
    CATCH("Fail in MoneyClearHistory!");
}

Local<Value> DataClass::xuid2name(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        return String::newString(Raw_Xuid2Name(args[0].toStr()));
    }
    CATCH("Fail in Xuid2Name!");
}

Local<Value> DataClass::name2xuid(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        return String::newString(Raw_Name2Xuid(args[0].toStr()));
    }
    CATCH("Fail in Name2Xuid!");
}

Local<Value> DataClass::toJson(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    if (args.size() >= 2)
        CHECK_ARG_TYPE(args[1], ValueKind::kNumber);

    try
    {
        int spaces = -1;
        if (args.size() >= 2)
        {
            int newSpaces = args[1].toInt();
            if (newSpaces > 0)
                spaces = newSpaces;
        }
        try
        {
            return String::newString(ValueToJson(args[0],spaces));
        }
        catch (...)
        {
            ERROR("Failed to transform into Json.");
            return Local<Value>();
        }
    }
    CATCH("Fail in ToJson!");
}

Local<Value> DataClass::parseJson(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try
    {
        try
        {
            return JsonToValue(args[0].toStr());
        }
        catch (...)
        {
            ERROR("Failed to parse from Json.");
            return Local<Value>();
        }
    }
    CATCH("Fail in ParseJson!");
}

Local<Value> DataClass::toMD5(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try {
        string data;
        if (args[0].isString())
            data = args[0].toStr();
        else if (args[0].isByteBuffer())
        {
            Local<ByteBuffer> buf = args[0].asByteBuffer();
            data = string((char*)buf.getRawBytes(), buf.byteLength());
        }
        else
        {
            ERROR("Wrong type of argument in ToMD5");
            return Local<Value>();
        }
        return String::newString(Raw_toMD5(data));
    }
    CATCH("Fail in ToMD5!");
}

Local<Value> DataClass::toSHA1(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try {
        string data;
        if (args[0].isString())
            data = args[0].toStr();
        else if (args[0].isByteBuffer())
        {
            Local<ByteBuffer> buf = args[0].asByteBuffer();
            data = string((char*)buf.getRawBytes(), buf.byteLength());
        }
        else
        {
            ERROR("Wrong type of argument in ToSHA1");
            return Local<Value>();
        }
        return String::newString(Raw_toSHA1(data));
    }
    CATCH("Fail in ToSHA1!");
}

Local<Value> DataClass::toBase64(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);

    try {
        string data;
        if (args[0].isString())
            data = args[0].toStr();
        else if (args[0].isByteBuffer())
        {
            Local<ByteBuffer> buf = args[0].asByteBuffer();
            data = string((char*)buf.getRawBytes(), buf.byteLength());
        }
        else
        {
            ERROR("Wrong type of argument in ToBase64");
            return Local<Value>();
        }
        return String::newString(Raw_ToBase64(data));
    }
    CATCH("Fail in ToBase64!");
}

Local<Value> DataClass::fromBase64(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    try {
        return String::newString(Raw_FromBase64(args[0].toStr()));
    }
    CATCH("Fail in FromBase64!");
}


//For Compability

Local<Value> DbClass::newDb(const string& dir)
{
    auto newp = new DbClass(dir);

    if (newp->isValid())
        return newp->getScriptObject();
    else
    {
        delete newp;
        return Local<Value>();
    }
}

Local<Value> ConfJsonClass::newConf(const string& path, const string& defContent)
{
    auto newp = new ConfJsonClass(path, defContent);
    return newp->getScriptObject();
}


Local<Value> ConfIniClass::newConf(const string& path, const string& defContent)
{
    auto newp = new ConfIniClass(path, defContent);
    if (newp)
        return newp->getScriptObject();
    else
        return Local<Value>();
}

Local<Value> DataClass::openConfig(const Arguments& args)
{
    enum GlobalConfType { json, ini };

    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);
    if (args.size() >= 2)
        CHECK_ARG_TYPE(args[1], ValueKind::kString);
    if (args.size() >= 3)
        CHECK_ARG_TYPE(args[2], ValueKind::kString);

    try {
        string path = args[0].toStr();
        GlobalConfType confType = GlobalConfType::ini;

        if (path.empty())
            return Boolean::newBoolean(false);

        if (args.size() >= 2)
        {
            string fileType = args[1].toStr();
            if (fileType == "json" || fileType == "Json")
                confType = GlobalConfType::json;
        }

        if (confType == GlobalConfType::ini)
        {
            if (args.size() >= 3)
                return ConfIniClass::newConf(path, args[2].toStr());
            else
                return ConfIniClass::newConf(path);
        }
        else    //json
        {
            if (args.size() >= 3)
                return ConfJsonClass::newConf(path, args[2].toStr());
            else
                return ConfJsonClass::newConf(path, "{}");
        }
    }
    CATCH("Fail in OpenConfig!");
}

Local<Value> DataClass::openDB(const Arguments& args)
{
    CHECK_ARGS_COUNT(args, 1);
    CHECK_ARG_TYPE(args[0], ValueKind::kString);

    return DbClass::newDb(args[0].toStr());
}