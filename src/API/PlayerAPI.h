#pragma once
#include "ScriptX.h"
using namespace script;

//////////////////// APIs ////////////////////

Local<Value> GetPlayer(const Arguments& args);
Local<Value> GetOnlinePlayers(const Arguments& args);

//////////////////// Classes ////////////////////
class Player;
class PlayerClass : public ScriptClass
{
private:
    Player *player;
public:
	explicit PlayerClass(Player *p)
        :ScriptClass(ScriptClass::ConstructFromCpp<PlayerClass>{}),player(p)
    {}
    Player *get()
    {
        return player;
    }

    Local<Value> getName();
    Local<Value> getPos();
    Local<Value> getRealName();
    Local<Value> getXuid();
    Local<Value> getIP();

    Local<Value> isOP(const Arguments& args);
    Local<Value> getPlayerPermLevel(const Arguments& args);
    Local<Value> setPlayerPermLevel(const Arguments& args);

    Local<Value> runcmdAs(const Arguments& args);
    Local<Value> teleport(const Arguments& args);
    Local<Value> kill(const Arguments& args);
    Local<Value> kick(const Arguments& args);
    Local<Value> tell(const Arguments& args);
    Local<Value> getHand(const Arguments& args);
    Local<Value> rename(const Arguments& args);
};