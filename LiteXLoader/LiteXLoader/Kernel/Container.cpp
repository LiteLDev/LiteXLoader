#include "Container.h"
#include "Global.h"
#include "SymbolHelper.h"
using namespace std;

bool Raw_AddItem(Container* container, ItemStack* item)
{
	if (!Raw_HasRoomFor(container,item))
		return false;
	container->addItem(*item);
	return true;
}

bool Raw_AddItemToFirstEmptySlot(Container* container, ItemStack* item)
{
	return container->addItemToFirstEmptySlot(*item);
}

bool Raw_HasRoomFor(Container* container, ItemStack* item)
{
	return container->hasRoomForItem(*item);
}

bool Raw_RemoveItem(Container* container, int slot, int number)
{
	if (slot > Raw_GetContainerSize(container))
		return false;
	container->removeItem(slot, number);
	return true;
}

ItemStack* Raw_GetSlot(Container* container, int slot)
{
	if (slot > Raw_GetContainerSize(container))
		return nullptr;
	auto list = Raw_GetAllSlots(container);
	return list[slot];
}

std::vector<ItemStack*> Raw_GetAllSlots(Container* container)
{
	return SymCall("?getSlots@Container@@UEBA?BV?$vector@PEBVItemStack@@V?$allocator@PEBVItemStack@@@std@@@std@@XZ",
		vector<ItemStack*>, Container*)(container);
}

bool Raw_RemoveAllItems(Container* container)
{
	container->removeAllItems();
	return true;
}

bool Raw_IsEmpty(Container* container)
{
	return container->isEmpty();
}

int Raw_GetContainerSize(Container* container)
{
	using _QWORD = int8_t;
	return (*(__int64 (**)(void))(*(_QWORD*)container + 112i64))();		//IDA char __fastcall Container::addItemToFirstEmptySlot
}

bool Raw_HasContainer(FloatVec4 pos)
{
	return Raw_GetContainer(pos) != nullptr;
}

class DropperBlockActor;
Container* Raw_GetContainer(FloatVec4 pos)
{
	Vec3 vec{ pos.x, pos.y, pos.z };

	// This function didn't use 'this' pointer
	Container* container = SymCall("?_getContainerAt@DropperBlockActor@@AEAAPEAVContainer@@AEAVBlockSource@@AEBVVec3@@@Z",
		Container*, DropperBlockActor*, BlockSource*, Vec3*)(nullptr, Raw_GetBlockSourceByDim(pos.dim), &vec);

	return container;
}