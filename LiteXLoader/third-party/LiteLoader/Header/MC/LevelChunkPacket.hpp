// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class LevelChunkPacket : public Packet {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_LEVELCHUNKPACKET
public:
    class LevelChunkPacket& operator=(class LevelChunkPacket const&) = delete;
    LevelChunkPacket(class LevelChunkPacket const&) = delete;
#endif

public:
    /*0*/ virtual ~LevelChunkPacket();
    /*1*/ virtual enum MinecraftPacketIds getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*4*/ virtual bool disallowBatching() const;
    /*5*/ virtual enum StreamReadResult _read(class ReadOnlyBinaryStream&);
    /*
    inline  ~LevelChunkPacket(){
         (LevelChunkPacket::*rv)();
        *((void**)&rv) = dlsym("??1LevelChunkPacket@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI LevelChunkPacket(class ChunkPos const&, bool);
    MCAPI LevelChunkPacket();
    MCAPI void pushSubChunkMetadata(unsigned __int64);

protected:

private:

};