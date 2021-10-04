#include "APIHelp.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <sstream>

#include <API/BaseAPI.h>
#include <API/BlockAPI.h>
#include <API/EntityAPI.h>
#include <API/ItemAPI.h>
#include <API/PlayerAPI.h>
#include <API/DeviceAPI.h>
#include <API/ItemAPI.h>
#include <API/EntityAPI.h>
#include <API/ContainerAPI.h>
#include <API/NbtAPI.h>
#include <API/GuiAPI.h>
#include <API/DataAPI.h>
#include <API/PlayerAPI.h>
#include <Kernel/Global.h>
#include <Engine/EngineOwnData.h>
using namespace script;
using namespace std;

//////////////////// APIs ////////////////////

void PrintValue(std::ostream &out, Local<Value> v)
{
    switch(v.getKind())
    {
        case ValueKind::kString:
            out << v.asString().toString();
            break;
        case ValueKind::kNumber:
            if(CheckIsFloat(v))
                out << v.asNumber().toDouble();
            else
                out << v.asNumber().toInt64();
            break;
        case ValueKind::kBoolean:
            out << v.asBoolean().value();
            break;
        case ValueKind::kNull:
            out << "<Null>";
            break;
        case ValueKind::kArray:
        {
            Local<Array> arr=v.asArray();
            if(arr.size() == 0)
                out << "[]";
            else
            {
                out << '[';
                PrintValue(out,arr.get(0));
                for(int i=1;i<arr.size();++i)
                {
                    out << ',';
                    PrintValue(out,arr.get(i));
                }
                out << ']';
            }
            break;
        }
        case ValueKind::kObject:
        {
            //自定义类型也会被识别为Object，优先处理
            //IntPos
            IntPos* intpos = IntPos::extractPos(v);
            if (intpos != nullptr)
            {
                out << DimId2Name(intpos->dim) << "(" << intpos->x << "," << intpos->y << "," << intpos->z << ")";
                break;
            }

            //FloatPos
            FloatPos* floatpos = FloatPos::extractPos(v);
            if (floatpos != nullptr)
            {
                out << fixed << setprecision(2) << DimId2Name(floatpos->dim) << "(" << floatpos->x << "," << floatpos->y << "," << floatpos->z << ")";
                break;
            }

            //其他自定义类型
            if (IsInstanceOf<BlockClass>(v))
            {
                out << "<Block>";
                break;
            }
            if (IsInstanceOf<DbClass>(v))
            {
                out << "<Database>";
                break;
            }
            if (IsInstanceOf<ConfJsonClass>(v))
            {
                out << "<ConfJson>";
                break;
            }
            if (IsInstanceOf<ConfIniClass>(v))
            {
                out << "<ConfIni>";
                break;
            }
            if (IsInstanceOf<DeviceClass>(v))
            {
                out << "<DeviceInfo>";
                break;
            }
            if (IsInstanceOf<ContainerClass>(v))
            {
                out << "<Container>";
                break;
            }
            if (IsInstanceOf<EntityClass>(v))
            {
                out << "<Entity>";
                break;
            }
            if (IsInstanceOf<SimpleFormClass>(v))
            {
                out << "<SimpleForm>";
                break;
            }
            if (IsInstanceOf<CustomFormClass>(v))
            {
                out << "<CustomForm>";
                break;
            }
            if (IsInstanceOf<ItemClass>(v))
            {
                out << "<Item>";
                break;
            }
            if (IsInstanceOf<PlayerClass>(v))
            {
                out << "<Player>";
                break;
            }
            if (IsNbtClass(v))
            {
                out << "<NbtClass>";
                break;
            }

            Local<Object> obj = v.asObject();
            std::vector<std::string> keys = obj.getKeyNames();
            if(keys.empty())
                out << "{}";
            else
            {
                out << '{';
                out << keys[0]+":";
                PrintValue(out,obj.get(keys[0]));
                for(int i=1;i<keys.size();++i)
                {
                    out << ","+keys[i]+":";
                    PrintValue(out,obj.get(keys[i]));
                }
                out << '}';
            }
            break;
        }
        case ValueKind::kByteBuffer:
        {
            Local<ByteBuffer> bytes = v.asByteBuffer();
            out.write((const char*)bytes.getRawBytes(),bytes.byteLength());
            break;
        }
        case ValueKind::kFunction:
        {
            out << "<Function>";
            break;
        }
        default:
        {
            out << "<Unknown>";
            break;
        }
    }
}

std::string ValueToString(Local<Value> v)
{
    std::ostringstream sout;
    PrintValue(sout, v);
    return sout.str();
}

bool CheckIsFloat(const Local<Value> &num)
{
    try
    {
        return fabs(num.asNumber().toDouble() - num.asNumber().toInt64()) >= 1e-15;
    }
    catch (...)
    {
        return false;
    }
}


///////////////////// Json To Value /////////////////////

void JsonToValue_Helper(Local<Array> &res, JSON_VALUE &j);

void JsonToValue_Helper(Local<Object> &res, const string &key, JSON_VALUE &j)
{
    switch (j.type())
    {
    case JSON_VALUE::value_t::string:
        res.set(key, String::newString(j.get<string>()));
        break;
    case JSON_VALUE::value_t::number_integer:
    case JSON_VALUE::value_t::number_unsigned:
        res.set(key, Number::newNumber(j.get<int>()));
        break;
    case JSON_VALUE::value_t::number_float:
        res.set(key, Number::newNumber(j.get<double>()));
        break;
    case JSON_VALUE::value_t::boolean:
        res.set(key, Boolean::newBoolean(j.get<bool>()));
        break;
    case JSON_VALUE::value_t::null:
        res.set(key, Local<Value>());
        break;
    case JSON_VALUE::value_t::array:
    {
        Local<Array> arrToAdd = Array::newArray();
        for (JSON_VALUE::iterator it = j.begin(); it != j.end(); ++it)
            JsonToValue_Helper(arrToAdd, *it);
        res.set(key, arrToAdd);
        break;
    }
    case JSON_VALUE::value_t::object:
    {
        Local<Object> objToAdd = Object::newObject();
        for (JSON_VALUE::iterator it = j.begin(); it != j.end(); ++it)
            JsonToValue_Helper(objToAdd, it.key(), it.value());
        res.set(key, objToAdd);
        break;
    }
    default:
        res.set(key, Local<Value>());
        break;
    }
}

void JsonToValue_Helper(Local<Array> &res, JSON_VALUE &j)
{
    switch (j.type())
    {
    case JSON_VALUE::value_t::string:
        res.add(String::newString(j.get<string>()));
        break;
    case JSON_VALUE::value_t::number_integer:
    case JSON_VALUE::value_t::number_unsigned:
        res.add(Number::newNumber(j.get<int>()));
        break;
    case JSON_VALUE::value_t::number_float:
        res.add(Number::newNumber(j.get<double>()));
        break;
    case JSON_VALUE::value_t::boolean:
        res.add(Boolean::newBoolean(j.get<bool>()));
        break;
    case JSON_VALUE::value_t::null:
        res.add(Local<Value>());
        break;
    case JSON_VALUE::value_t::array:
    {
        Local<Array> arrToAdd = Array::newArray();
        for (JSON_VALUE::iterator it = j.begin(); it != j.end(); ++it)
            JsonToValue_Helper(arrToAdd, *it);
        res.add(arrToAdd);
        break;
    }
    case JSON_VALUE::value_t::object:
    {
        Local<Object> objToAdd = Object::newObject();
        for (JSON_VALUE::iterator it = j.begin(); it != j.end(); ++it)
            JsonToValue_Helper(objToAdd, it.key(), it.value());
        res.add(objToAdd);
        break;
    }
    default:
        res.add(Local<Value>());
        break;
    }
}

Local<Value> JsonToValue(JSON_VALUE j)
{
    Local<Value> res;

    switch (j.type())
    {
    case JSON_VALUE::value_t::string:
        res = String::newString(j.get<string>());
        break;
    case JSON_VALUE::value_t::number_integer:
    case JSON_VALUE::value_t::number_unsigned:
        res = Number::newNumber(j.get<int>());
        break;
    case JSON_VALUE::value_t::number_float:
        res = Number::newNumber(j.get<double>());
        break;
    case JSON_VALUE::value_t::boolean:
        res = Boolean::newBoolean(j.get<bool>());
        break;
    case JSON_VALUE::value_t::null:
        res = Local<Value>();
        break;
    case JSON_VALUE::value_t::array:
    {
        Local<Array> resArr = Array::newArray();
        for (JSON_VALUE::iterator it = j.begin(); it != j.end(); ++it)
            JsonToValue_Helper(resArr, *it);
        res = resArr;
        break;
    }
    case JSON_VALUE::value_t::object:
    {
        Local<Object> resObj = Object::newObject();
        for (JSON_VALUE::iterator it = j.begin(); it != j.end(); ++it)
            JsonToValue_Helper(resObj, it.key(), it.value());
        res = resObj;
        break;
    }
    default:
        res = Local<Value>();
        break;
    }
    
    return res;
}

Local<Value> JsonToValue(std::string jsonStr)
{
    try
    {
        if (jsonStr.empty())
            return String::newString("");
        if (jsonStr.front() == '\"' && jsonStr.back() == '\"')
            return String::newString(jsonStr.substr(1,jsonStr.size()-2));
        auto j = JSON_VALUE::parse(jsonStr);
        return JsonToValue(j);
    }
    catch (const JSON_VALUE::exception &e)
    {
        WARN(_TRS("api.parseJson.fail") + e.what());
        return String::newString(jsonStr);
    }
}


///////////////////// Value To Json /////////////////////

void ValueToJson_Obj_Helper(JSON_VALUE& res, const Local<Object>& v);

void ValueToJson_Arr_Helper(JSON_VALUE &res, const Local<Array> &v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        switch (v.get(i).getKind())
        {
        case ValueKind::kString:
            res.push_back(v.get(i).asString().toString());
            break;
        case ValueKind::kNumber:
            if (CheckIsFloat(v))
                res.push_back(v.get(i).asNumber().toDouble());
            else
                res.push_back(v.get(i).asNumber().toInt64());
            break;
        case ValueKind::kBoolean:
            res.push_back(v.get(i).asBoolean().value());
            break;
        case ValueKind::kNull:
            res.push_back(nullptr);
            break;
        case ValueKind::kArray:
        {
            Local<Array> arrToAdd = v.get(i).asArray();
            if (arrToAdd.size() == 0)
                res.push_back(JSON_VALUE::array());
            else
            {
                JSON_VALUE arrJson = JSON_VALUE::array();
                ValueToJson_Arr_Helper(arrJson, arrToAdd);
                res.push_back(arrJson);
            }
            break;
        }
        case ValueKind::kObject:
        {
            Local<Object> objToAdd = v.get(i).asObject();
            if (objToAdd.getKeyNames().empty())
                res.push_back(JSON_VALUE::object());
            else
            {
                JSON_VALUE objJson = JSON_VALUE::object();
                ValueToJson_Obj_Helper(objJson, objToAdd);
                res.push_back(objJson);
            }
            break;
        }
        default:
            res.push_back(nullptr);
            break;
        }
    }
}

void ValueToJson_Obj_Helper(JSON_VALUE& res, const Local<Object>& v)
{
    auto keys = v.getKeyNames();
    for (auto &key : keys)
    {
        switch (v.get(key).getKind())
        {
        case ValueKind::kString:
            res.push_back({ key,v.get(key).asString().toString() });
            break;
        case ValueKind::kNumber:
            if (CheckIsFloat(v))
                res.push_back({ key,v.get(key).asNumber().toDouble() });
            else
                res.push_back({ key,v.get(key).asNumber().toInt64() });
            break;
        case ValueKind::kBoolean:
            res.push_back({ key,v.get(key).asBoolean().value() });
            break;
        case ValueKind::kNull:
            res.push_back({ key, nullptr });
            break;
        case ValueKind::kArray:
        {
            Local<Array> arrToAdd = v.get(key).asArray();
            if (arrToAdd.size() == 0)
                res.push_back({ key,JSON_VALUE::array() });
            else
            {
                JSON_VALUE arrJson = JSON_VALUE::array();
                ValueToJson_Arr_Helper(arrJson, arrToAdd);
                res.push_back({ key,arrJson });
            }
            break;
        }
        case ValueKind::kObject:
        {
            Local<Object> objToAdd = v.get(key).asObject();
            if (objToAdd.getKeyNames().empty())
                res.push_back({ key,JSON_VALUE::object() });
            else
            {
                JSON_VALUE objJson = JSON_VALUE::object();
                ValueToJson_Obj_Helper(objJson, objToAdd);
                res.push_back({ key,objJson });
            }
            break;
        }
        default:
            res.push_back({ key,nullptr });
            break;
        }
    }
}

std::string ValueToJson(Local<Value> v,int formatIndent)
{
    string result;
    switch (v.getKind())
    {
    case ValueKind::kString:
        result = "\"" + v.asString().toString() + "\"";
        break;
    case ValueKind::kNumber:
        if (CheckIsFloat(v))
            result = std::to_string(v.asNumber().toDouble());
        else
            result = std::to_string(v.asNumber().toInt64());
        break;
    case ValueKind::kBoolean:
        result = std::to_string(v.asBoolean().value());
        break;
    case ValueKind::kNull:
        result = "";
        break;
    case ValueKind::kArray:
    {
        JSON_VALUE jsonRes = JSON_VALUE::array();
        ValueToJson_Arr_Helper(jsonRes, v.asArray());
        result = jsonRes.dump(formatIndent);
        break;
    }
    case ValueKind::kObject:
    {
        JSON_VALUE jsonRes = JSON_VALUE::object();
        ValueToJson_Obj_Helper(jsonRes, v.asObject());
        result = jsonRes.dump(formatIndent);
        break;
    }
    default:
        result = "";
        break;
    }
    return result;
}