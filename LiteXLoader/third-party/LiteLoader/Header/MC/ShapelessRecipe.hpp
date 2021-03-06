// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Recipe.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ShapelessRecipe : public Recipe {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SHAPELESSRECIPE
public:
    class ShapelessRecipe& operator=(class ShapelessRecipe const&) = delete;
    ShapelessRecipe(class ShapelessRecipe const&) = delete;
    ShapelessRecipe() = delete;
#endif

public:
    /*0*/ virtual ~ShapelessRecipe();
    /*1*/ virtual std::vector<class ItemInstance> const& assemble(class CraftingContainer&) const;
    /*2*/ virtual int getCraftingSize() const;
    /*3*/ virtual class RecipeIngredient const& getIngredient(int, int) const;
    /*4*/ virtual std::vector<class ItemInstance> const& getResultItem() const;
    /*5*/ virtual bool isShapeless() const;
    /*6*/ virtual bool matches(class CraftingContainer&, class Level&) const;
    /*7*/ virtual int size() const;
    /*8*/ virtual class mce::UUID const& getId() const;
    /*9*/ virtual class ItemPack const& getItemPack() const;
    /*10*/ virtual bool isMultiRecipe() const;
    /*11*/ virtual void loadResultList(class BlockPalette const&) const;
    /*
    inline  ~ShapelessRecipe(){
         (ShapelessRecipe::*rv)();
        *((void**)&rv) = dlsym("??1ShapelessRecipe@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ShapelessRecipe(class gsl::basic_string_span<char const, -1>, std::vector<class RecipeIngredient> const&, std::vector<class ItemInstance> const&, class HashedString, int, class mce::UUID const*);

protected:

private:
    MCAPI void init(class gsl::basic_string_span<char const, -1>, int, class mce::UUID const*);

};