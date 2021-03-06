// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Bedrock.hpp"
#include "Core.hpp"
#include "VolumeEntityManager.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class VolumeEntityManagerServer {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_VOLUMEENTITYMANAGERSERVER
public:
    class VolumeEntityManagerServer& operator=(class VolumeEntityManagerServer const&) = delete;
    VolumeEntityManagerServer(class VolumeEntityManagerServer const&) = delete;
    VolumeEntityManagerServer() = delete;
#endif

public:
    /*0*/ virtual ~VolumeEntityManagerServer();
    MCAPI VolumeEntityManagerServer(class gsl::not_null<class Bedrock::NonOwnerPointer<class IEntityRegistryOwner> >);
    MCAPI std::vector<class WeakRefT<struct EntityRefTraits>> getAllVolumesOverlappingChunkPosition(class ChunkPos const&, class AutomaticID<class Dimension, int>) const;
    MCAPI void loadVolumeFiles(class Core::PathBuffer<std::string > const&, bool);
    MCAPI void sendAllVolumesToClient(class UserEntityIdentifierComponent const&, class NetworkIdentifier const&, class PacketSender&) const;
    MCAPI static class SemVersion const MAXIMUM_SUPPORTED_VERSION;
    MCAPI static class SemVersion const MINIMUM_SUPPORTED_VERSION;

protected:

private:
    MCAPI class DefinitionInstanceGroup _createDefinitionGroup(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>, class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>, class rapidjson::CrtAllocator>&, class SemVersion const&) const;
    MCAPI bool _parseAndRegisterVolume(std::string const&, class SemVersion const&, class Core::PathBuffer<std::string > const&);
    MCAPI void _readVolumesFromJson(std::vector<class Core::PathBuffer<std::string >> const&, bool);
    MCAPI bool _registerVolume(class rapidjson::GenericDocument<struct rapidjson::UTF8<char>, class rapidjson::MemoryPoolAllocator<class rapidjson::CrtAllocator>, class rapidjson::CrtAllocator>&, class SemVersion const&, class Core::PathBuffer<std::string > const&);
    MCAPI bool _serializeVolume(struct VolumeEntityManager::VolumeEntityDefinition const&, class EntityContext const&, class CompoundTag&) const;

};