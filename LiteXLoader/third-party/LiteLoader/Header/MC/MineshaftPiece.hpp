// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "StructurePiece.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class MineshaftPiece : public StructurePiece {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_MINESHAFTPIECE
public:
    class MineshaftPiece& operator=(class MineshaftPiece const&) = delete;
    MineshaftPiece(class MineshaftPiece const&) = delete;
    MineshaftPiece() = delete;
#endif

public:
    /*0*/ virtual ~MineshaftPiece();
    /*1*/ virtual class PoolElementStructurePiece* asPoolElement();
    /*2*/ virtual enum StructurePieceType getType() const;
    /*3*/ virtual void addChildren(class StructurePiece&, std::vector<std::unique_ptr<class StructurePiece>>&, class Random&);
    /*4*/ virtual bool postProcess(class BlockSource&, class Random&, class BoundingBox const&) = 0;
    /*5*/ virtual void postProcessMobsAt(class BlockSource&, class Random&, class BoundingBox const&);
    /*6*/ virtual bool canBeReplaced(class BlockSource&, int, int, int, class BoundingBox const&);
    /*7*/ virtual void addHardcodedSpawnAreas(class LevelChunk&) const;
    /*
    inline  ~MineshaftPiece(){
         (MineshaftPiece::*rv)();
        *((void**)&rv) = dlsym("??1MineshaftPiece@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI std::unique_ptr<class StructurePiece> createRandomShaftPiece(struct MineshaftData&, std::vector<std::unique_ptr<class StructurePiece>>&, class Random&, int, int, int, int, int);
    MCAPI class StructurePiece* generateAndAddPiece(class StructurePiece&, std::vector<std::unique_ptr<class StructurePiece>>&, class Random&, int, int, int, int, int);
    MCAPI void setPlanksBlock(class BlockSource&, class Block const&, int, int, int);

protected:

private:

};