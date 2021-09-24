#include "pch.h"

#include "McAPI.h"

ClassDefine<void> McClassBuilder =
	defineClass("mc")
		.function("getBDSVersion", &McClass::getBDSVersion)
		.function("runcmd", &McClass::runcmd)
		.function("runcmdEx", &McClass::runcmdEx)
		.function("regPlayerCmd", &McClass::regPlayerCmd)
		.function("broadcast", &McClass::broadcast)
		.function("listen", &McClass::listen)
		.function("getPlayer", &McClass::getPlayer)
		.function("getOnlinePlayers", &McClass::getOnlinePlayers)
		.function("getAllEntities", McClass::getAllEntities)
		.function("newItem", &McClass::newItem)
		.function("spawnMob", &McClass::spawnMob)
		.function("spawnItem", &McClass::spawnItem)
		.function("explode", &McClass::explode)
		.function("getBlock", &McClass::getBlock)
		.function("setBlock", &McClass::setBlock)
		.function("spawnParticle", &McClass::spawnParticle)
		.function("newSimpleForm", &McClass::newSimpleForm)
		.function("newCustomForm", &McClass::newCustomForm)
		.function("regConsoleCmd", &McClass::regConsoleCmd)
		.function("setMotd", &McClass::setMotd)
		.function("sendCmdOutput", &McClass::sendCmdOutput)
		.function("newIntPos", &McClass::newIntPos)
		.function("newFloatPos", &McClass::newFloatPos)
		.function("getDisplayObjective", &McClass::getDisplayObjective)
		.function("clearDisplayObjective", &McClass::clearDisplayObjective)
		.function("getScoreObjective", &McClass::getScoreObjective)
		.function("newScoreObjective", &McClass::newScoreObjective)
		.function("removeScoreObjective", &McClass::removeScoreObjective)
		.function("getAllScoreObjectives", &McClass::getAllScoreObjectives)

		//For Compatity
		.function("getAllScoreObjective", &McClass::getAllScoreObjectives)
		.function("getDisplayObjectives", &McClass::getDisplayObjective)
		.function("crash", &McClass::crashBDS)
		.build();