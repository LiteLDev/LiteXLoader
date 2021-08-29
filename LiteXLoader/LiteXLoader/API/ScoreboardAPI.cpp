#include "APIHelp.h"
#include <Kernel/Scoreboard.h>
#include <Kernel/Player.h>
#include "ScoreboardAPI.h"
#include "PlayerAPI.h"
#include <optional>
using namespace std;

//////////////////// Class Definition ////////////////////

ClassDefine<ObjectiveClass> ObjectiveClassBuilder =
	defineClass<ObjectiveClass>("LXL_Objective")
		.constructor(nullptr)
		.instanceProperty("name", &ObjectiveClass::getName)
		.instanceProperty("displayName", &ObjectiveClass::getDisplayName)

		.instanceFunction("setDisplay", &ObjectiveClass::setDisplay)
		.instanceFunction("setScore", &ObjectiveClass::setScore)
		.instanceFunction("addScore", &ObjectiveClass::addScore)
		.instanceFunction("reduceScore", &ObjectiveClass::reduceScore)
		.instanceFunction("deleteScore", &ObjectiveClass::deleteScore)
		.instanceFunction("getScore", &ObjectiveClass::getScore)
		.build();

//////////////////// Classes ////////////////////

Local<Object> ObjectiveClass::newObjective(Objective* obj)
{
	if (obj)
	{
		auto newp = new ObjectiveClass(obj);
		return newp->getScriptObject();
	}
}

void ObjectiveClass::set(Objective* obj)
{
	if (obj)
	{
		objname = obj->getName();
		isValid = true;
	}
}

Objective* ObjectiveClass::get()
{
	if (isValid)
		return globalScoreBoard->getObjective(objname);
	return nullptr;
}

Local<Value> ObjectiveClass::getName()
{
	try {
		return String::newString(objname);
	}
	CATCH("Fail in getName!")
}

Local<Value> ObjectiveClass::getDisplayName()
{
	try {
		Objective* obj = get();
		return String::newString(obj->getDisplayName());
	}
	CATCH("Fail in getDisplayName!")
}

Local<Value> ObjectiveClass::setDisplay(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)
	CHECK_ARG_TYPE(args[0], ValueKind::kString)
	if (args.size() == 2)
		CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

	try {
		string slot = args[0].toStr();
		int sort = 0;
		if (args.size() == 2) sort = args[1].toInt();
		bool res = Raw_SetDisplayObjective(objname, slot, sort);
		
		return Boolean::newBoolean(res);
	}
	CATCH("Fail in setDisplay");
}

Local<Value> ObjectiveClass::setScore(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2)
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

	try {
		string id;
		if (args[0].isString())
			id = args[0].toStr();
		else if (IsInstanceOf<PlayerClass>(args[0]))
			id = Raw_GetPlayerName(PlayerClass::extractPlayer(args[0]));
		else
		{
			ERROR("Wrong type of argument in setScore!");
			return Local<Value>();
		}

		int score = args[1].toInt();
		std::optional<int> res = Raw_ModifyScoreInObjective(objname, id, 0, score);

		return res ? Number::newNumber(*res) : Local<Value>();
	}
	CATCH("Fail in setScore");
}

Local<Value> ObjectiveClass::addScore(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2)
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

	try {
		string id;
		if (args[0].isString())
			id = args[0].toStr();
		else if (IsInstanceOf<PlayerClass>(args[0]))
			id = Raw_GetPlayerName(PlayerClass::extractPlayer(args[0]));
		else
		{
			ERROR("Wrong type of argument in addScore!");
			return Local<Value>();
		}

		int score = args[1].toInt();
		std::optional<int> res = Raw_ModifyScoreInObjective(objname, id, 1, score);

		return res ? Number::newNumber(*res) : Local<Value>();
	}
	CATCH("Fail in addScore");
}

Local<Value> ObjectiveClass::reduceScore(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 2)
	CHECK_ARG_TYPE(args[1], ValueKind::kNumber)

	try {
		string id;
		if (args[0].isString())
			id = args[0].toStr();
		else if (IsInstanceOf<PlayerClass>(args[0]))
			id = Raw_GetPlayerName(PlayerClass::extractPlayer(args[0]));
		else
		{
			ERROR("Wrong type of argument in reduceScore!");
			return Local<Value>();
		}

		int score = args[1].toInt();
		std::optional<int> res = Raw_ModifyScoreInObjective(objname, id, 2, score);

		return res ? Number::newNumber(*res) : Local<Value>();
	}
	CATCH("Fail in removeScore");
}

Local<Value> ObjectiveClass::deleteScore(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)

	try {
		string id;
		if (args[0].isString())
			id = args[0].toStr();
		else if (IsInstanceOf<PlayerClass>(args[0]))
			id = Raw_GetPlayerName(PlayerClass::extractPlayer(args[0]));
		else
		{
			ERROR("Wrong type of argument in deleteScore!");
			return Local<Value>();
		}

		bool res = Raw_RemoveFromObjective(objname, id);

		return Boolean::newBoolean(res);
	}
	CATCH("Fail in deleteScore");
}

Local<Value> ObjectiveClass::getScore(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)
		
	try {
		string id;
		if (args[0].isString())
			id = args[0].toStr();
		else if (IsInstanceOf<PlayerClass>(args[0]))
			id = Raw_GetPlayerName(PlayerClass::extractPlayer(args[0]));
		else
		{
			ERROR("Wrong type of argument in getScore!");
			return Local<Value>();
		}

		int res = Raw_GetScore(objname, id);

		return Number::newNumber(res);
	}
	CATCH("Fail in getScore");
}

//////////////////// APIs ////////////////////

Local<Value> GetDisplayObjetives(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try {
		string slot = args[0].toStr();
		auto res = Raw_GetDisplayObjective(slot);

		if (!res) return Local<Value>();
		return ObjectiveClass::newObjective(res);
	}
	CATCH("Fail in GetDisplayObjective");
}

Local<Value> ClearDisplayObjetive(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try {
		string slot = args[0].toStr();
		auto res = Raw_ClearDisplayObjective(slot);

		if (!res) return Local<Value>();
		return ObjectiveClass::newObjective(res);
	}
	CATCH("Fail in ClearDisplayObjective");
}

Local<Value> GetScoreObjetive(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1);
	CHECK_ARG_TYPE(args[0], ValueKind::kString);

	try {
		string name = args[0].toStr();
		auto res = globalScoreBoard->getObjective(name);

		if (!res) return Local<Value>();
		return ObjectiveClass::newObjective(res);
	}
	CATCH("Fail in GetScoreObjective");
}

Local<Value> NewScoreObjective(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)
	CHECK_ARG_TYPE(args[0], ValueKind::kString)
	if(args.size()>=2)
		CHECK_ARG_TYPE(args[1], ValueKind::kString)

	try {
		string name = args[0].toStr();
		string display = name;
		if (args.size() >= 2)
			display = args[1].toStr();

		string criteria = "dummy";
		auto obj = globalScoreBoard->addObjective(name, display, globalScoreBoard->getCriteria(criteria));

		return ObjectiveClass::newObjective(obj);
	}
	CATCH("Fail in NewScoreObjective!")
}

Local<Value> RemoveScoreObjective(const Arguments& args)
{
	CHECK_ARGS_COUNT(args, 1)
	CHECK_ARG_TYPE(args[0], ValueKind::kString)

	try {
		string name = args[0].toStr();
		auto obj = globalScoreBoard->getObjective(name);
		if (obj)
		{
			globalScoreBoard->removeObjective(obj);
			return Boolean::newBoolean(true);
		}
		return Boolean::newBoolean(false);
	}
	CATCH("Fail in RemoveScoreObjective!")
}

Local<Value> GetAllScoreObjectives(const Arguments& args)
{
	try {
		Local<Array> res = Array::newArray();

		auto objs = globalScoreBoard->getObjectives();
		for (auto& obj : objs)
		{
			if (obj)
				res.add(ObjectiveClass::newObjective(obj));
		}
		return res;
	}
	CATCH("Fail in GetAllScoreObjectives!")
}