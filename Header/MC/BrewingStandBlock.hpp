// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ActorBlock.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class BrewingStandBlock : public ActorBlock {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_BREWINGSTANDBLOCK
public:
    class BrewingStandBlock& operator=(class BrewingStandBlock const&) = delete;
    BrewingStandBlock(class BrewingStandBlock const&) = delete;
    BrewingStandBlock() = delete;
#endif

public:
    /*0*/ virtual ~BrewingStandBlock();
    /*1*/ virtual bool hasTag(class BlockSource&, class BlockPos const&, class Block const&, std::string const&) const;
    /*2*/ virtual bool isObstructingChests(class BlockSource&, class BlockPos const&) const;
    /*3*/ virtual class Vec3 randomlyModifyPosition(class BlockPos const&) const;
    /*4*/ virtual void addAABBs(class Block const&, class BlockSource&, class BlockPos const&, class AABB const*, std::vector<class AABB>&) const;
    /*5*/ virtual class AABB const& getAABB(class BlockSource const&, class BlockPos const&, class Block const&, class AABB&, bool) const;
    /*6*/ virtual bool addCollisionShapes(class Block const&, class BlockSource&, class BlockPos const&, class AABB const*, std::vector<class AABB>&, class optional_ref<struct IActorMovementProxy>) const;
    /*7*/ virtual void onProjectileHit(class BlockSource&, class BlockPos const&, class Actor const&) const;
    /*8*/ virtual void onLightningHit(class BlockSource&, class BlockPos const&) const;
    /*9*/ virtual bool liquidCanFlowIntoFromDirection(unsigned char, class std::function<class Block const& (class BlockPos const& )> const&, class BlockPos const&) const;
    /*10*/ virtual void __unk_vfn_0();
    /*11*/ virtual bool isStrippable(class Block const&) const;
    /*12*/ virtual class Block const& getStrippedBlock(class Block const&) const;
    /*13*/ virtual class CopperBehavior const* tryGetCopperBehavior() const;
    /*14*/ virtual void __unk_vfn_1();
    /*15*/ virtual void __unk_vfn_2();
    /*16*/ virtual void __unk_vfn_3();
    /*17*/ virtual void __unk_vfn_4();
    /*18*/ virtual void __unk_vfn_5();
    /*19*/ virtual void __unk_vfn_6();
    /*20*/ virtual void __unk_vfn_7();
    /*21*/ virtual void __unk_vfn_8();
    /*22*/ virtual void __unk_vfn_9();
    /*23*/ virtual void __unk_vfn_10();
    /*24*/ virtual bool isDoubleSlabBlock() const;
    /*25*/ virtual void __unk_vfn_11();
    /*26*/ virtual void __unk_vfn_12();
    /*27*/ virtual void __unk_vfn_13();
    /*28*/ virtual void __unk_vfn_14();
    /*29*/ virtual void __unk_vfn_15();
    /*30*/ virtual void __unk_vfn_16();
    /*31*/ virtual bool canBeAscendedByJumping(class Actor const&, class BlockPos const&) const;
    /*32*/ virtual bool isValidAuxValue(int) const;
    /*33*/ virtual bool canFillAtPos(class BlockSource&, class BlockPos const&, class Block const&) const;
    /*34*/ virtual void onFillBlock(class BlockSource&, class BlockPos const&, class Block const&) const;
    /*35*/ virtual int getDirectSignal(class BlockSource&, class BlockPos const&, int) const;
    /*36*/ virtual void __unk_vfn_17();
    /*37*/ virtual void __unk_vfn_18();
    /*38*/ virtual bool shouldConnectToRedstone(class BlockSource&, class BlockPos const&, int) const;
    /*39*/ virtual void handlePrecipitation(class BlockSource&, class BlockPos const&, float, float) const;
    /*40*/ virtual float getFlexibility(class BlockSource&, class BlockPos const&) const;
    /*41*/ virtual bool checkIsPathable(class Actor&, class BlockPos const&, class BlockPos const&) const;
    /*42*/ virtual bool shouldDispense(class BlockSource&, class Container&) const;
    /*43*/ virtual bool dispense(class BlockSource&, class Container&, int, class Vec3 const&, unsigned char) const;
    /*44*/ virtual void transformOnFall(class BlockSource&, class BlockPos const&, class Actor*, float) const;
    /*45*/ virtual void onRedstoneUpdate(class BlockSource&, class BlockPos const&, int, bool) const;
    /*46*/ virtual void onMove(class BlockSource&, class BlockPos const&, class BlockPos const&) const;
    /*47*/ virtual void __unk_vfn_19();
    /*48*/ virtual void movedByPiston(class BlockSource&, class BlockPos const&) const;
    /*49*/ virtual void onStructureBlockPlace(class BlockSource&, class BlockPos const&) const;
    /*50*/ virtual void onStructureNeighborBlockPlace(class BlockSource&, class BlockPos const&) const;
    /*51*/ virtual void setupRedstoneComponent(class BlockSource&, class BlockPos const&) const;
    /*52*/ virtual enum BlockProperty getRedstoneProperty(class BlockSource&, class BlockPos const&) const;
    /*53*/ virtual void __unk_vfn_20();
    /*54*/ virtual bool isFilteredOut(enum BlockRenderLayer) const;
    /*55*/ virtual void __unk_vfn_21();
    /*56*/ virtual bool ignoreEntitiesOnPistonMove(class Block const&) const;
    /*57*/ virtual bool onFertilized(class BlockSource&, class BlockPos const&, class Actor*, enum FertilizerType) const;
    /*58*/ virtual bool mayConsumeFertilizer(class BlockSource&) const;
    /*59*/ virtual bool canBeFertilized(class BlockSource&, class BlockPos const&, class Block const&) const;
    /*60*/ virtual bool mayPick() const;
    /*61*/ virtual bool mayPlace(class BlockSource&, class BlockPos const&, unsigned char) const;
    /*62*/ virtual bool mayPlaceOn(class BlockSource&, class BlockPos const&) const;
    /*63*/ virtual bool tryToTill(class BlockSource&, class BlockPos const&, class Actor&, class ItemStack&) const;
    /*64*/ virtual void destroy(class BlockSource&, class BlockPos const&, class Block const&, class Actor*) const;
    /*65*/ virtual bool getIgnoresDestroyPermissions(class Actor&, class BlockPos const&) const;
    /*66*/ virtual bool getSecondPart(class BlockSource const&, class BlockPos const&, class BlockPos&) const;
    /*67*/ virtual int getResourceCount(class Randomize&, class Block const&, int) const;
    /*68*/ virtual class ItemInstance getResourceItem(class Randomize&, class Block const&, int) const;
    /*69*/ virtual class ItemInstance asItemInstance(class BlockSource&, class BlockPos const&, class Block const&) const;
    /*70*/ virtual void __unk_vfn_22();
    /*71*/ virtual class Block const& getPlacementBlock(class Actor&, class BlockPos const&, unsigned char, class Vec3 const&, int) const;
    /*72*/ virtual bool isAttachedTo(class BlockSource&, class BlockPos const&, class BlockPos&) const;
    /*73*/ virtual bool attack(class Player*, class BlockPos const&) const;
    /*74*/ virtual void handleEntityInside(class BlockSource&, class BlockPos const&, class Actor*, class Vec3&) const;
    /*75*/ virtual void entityInside(class BlockSource&, class BlockPos const&, class Actor&) const;
    /*76*/ virtual int getExperienceDrop(class Random&) const;
    /*77*/ virtual void __unk_vfn_23();
    /*78*/ virtual float calcGroundFriction(struct IMobMovementProxy const&, class BlockPos const&) const;
    /*79*/ virtual void __unk_vfn_24();
    /*80*/ virtual void __unk_vfn_25();
    /*81*/ virtual int getComparatorSignal(class BlockSource&, class BlockPos const&, class Block const&, unsigned char) const;
    /*82*/ virtual bool canSpawnAt(class BlockSource const&, class BlockPos const&) const;
    /*83*/ virtual void notifySpawnedAt(class BlockSource&, class BlockPos const&) const;
    /*84*/ virtual void __unk_vfn_26();
    /*85*/ virtual int getIconYOffset() const;
    /*86*/ virtual std::string buildDescriptionId(class Block const&) const;
    /*87*/ virtual bool isAuxValueRelevantForPicking() const;
    /*88*/ virtual int getColor(class Block const&) const;
    /*89*/ virtual int getColor(class BlockSource&, class BlockPos const&, class Block const&) const;
    /*90*/ virtual int getColorAtPos(class BlockSource&, class BlockPos const&) const;
    /*91*/ virtual bool isSeasonTinted(class Block const&, class BlockSource&, class BlockPos const&) const;
    /*92*/ virtual class AABB const& getVisualShape(class Block const&, class AABB&, bool) const;
    /*93*/ virtual void __unk_vfn_27();
    /*94*/ virtual class Block const& getRenderBlock() const;
    /*95*/ virtual unsigned char getMappedFace(unsigned char, class Block const&) const;
    /*96*/ virtual enum Flip getFaceFlip(unsigned char, class Block const&) const;
    /*97*/ virtual void animateTick(class BlockSource&, class BlockPos const&, class Random&) const;
    /*98*/ virtual void __unk_vfn_28();
    /*99*/ virtual class Block const* tryLegacyUpgrade(unsigned short) const;
    /*100*/ virtual bool dealsContactDamage(class Actor const&, class Block const&, bool) const;
    /*101*/ virtual class Block const* tryGetInfested(class Block const&) const;
    /*102*/ virtual class Block const* tryGetUninfested(class Block const&) const;
    /*103*/ virtual void onRemove(class BlockSource&, class BlockPos const&) const;
    /*104*/ virtual void onExploded(class BlockSource&, class BlockPos const&, class Actor*) const;
    /*105*/ virtual void onStandOn(class Actor&, class BlockPos const&) const;
    /*106*/ virtual void onStepOn(class Actor&, class BlockPos const&) const;
    /*107*/ virtual void __unk_vfn_29();
    /*108*/ virtual void __unk_vfn_30();
    /*109*/ virtual void onPlace(class BlockSource&, class BlockPos const&) const;
    /*110*/ virtual void tick(class BlockSource&, class BlockPos const&, class Random&) const;
    /*111*/ virtual void __unk_vfn_31();
    /*112*/ virtual bool use(class Player&, class BlockPos const&, unsigned char) const;
    /*113*/ virtual bool canSurvive(class BlockSource&, class BlockPos const&) const;
    /*114*/ virtual int getExtraRenderLayers() const;
    /*115*/ virtual class mce::Color getMapColor(class BlockSource&, class BlockPos const&) const;
    /*116*/ virtual void __unk_vfn_32();
    /*117*/ virtual void __unk_vfn_33();
    /*
    inline bool hasComparatorSignal() const{
        bool (BrewingStandBlock::*rv)() const;
        *((void**)&rv) = dlsym("?hasComparatorSignal@BrewingStandBlock@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isCraftingBlock() const{
        bool (BrewingStandBlock::*rv)() const;
        *((void**)&rv) = dlsym("?isCraftingBlock@BrewingStandBlock@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isContainerBlock() const{
        bool (BrewingStandBlock::*rv)() const;
        *((void**)&rv) = dlsym("?isContainerBlock@BrewingStandBlock@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isInteractiveBlock() const{
        bool (BrewingStandBlock::*rv)() const;
        *((void**)&rv) = dlsym("?isInteractiveBlock@BrewingStandBlock@@UEBA_NXZ");
        return (this->*rv)();
    }
    */
    MCAPI BrewingStandBlock(std::string const&, int);

protected:

private:

};