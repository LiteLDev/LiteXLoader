// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ItemStackRequestActionCreate {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ITEMSTACKREQUESTACTIONCREATE
public:
    class ItemStackRequestActionCreate& operator=(class ItemStackRequestActionCreate const&) = delete;
    ItemStackRequestActionCreate(class ItemStackRequestActionCreate const&) = delete;
    ItemStackRequestActionCreate() = delete;
#endif

public:
    /*0*/ virtual ~ItemStackRequestActionCreate();
    /*1*/ virtual void __unk_vfn_0();
    /*2*/ virtual void __unk_vfn_1();
    /*3*/ virtual void __unk_vfn_2();
    /*4*/ virtual void _write(class BinaryStream&) const;
    /*5*/ virtual bool _read(class ReadOnlyBinaryStream&);
    MCAPI unsigned char getResultsIndex() const;

protected:

private:

};