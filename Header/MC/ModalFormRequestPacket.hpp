// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ModalFormRequestPacket : public Packet {

#define AFTER_EXTRA
// Add Member There
    char filler[40];

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MODALFORMREQUESTPACKET
public:
    class ModalFormRequestPacket& operator=(class ModalFormRequestPacket const&) = delete;
    ModalFormRequestPacket(class ModalFormRequestPacket const&) = delete;
#endif

public:
    /*0*/ virtual ~ModalFormRequestPacket();
    /*1*/ virtual enum MinecraftPacketIds getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*4*/ virtual bool disallowBatching() const;
    /*5*/ virtual enum StreamReadResult _read(class ReadOnlyBinaryStream&);
    MCAPI ModalFormRequestPacket();

protected:

private:

};