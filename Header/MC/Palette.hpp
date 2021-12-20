// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Palette {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_PALETTE
public:
    class Palette& operator=(class Palette const&) = delete;
    Palette(class Palette const&) = delete;
    Palette() = delete;
#endif

public:
    MCAPI static class mce::Color const BLACK;
    MCAPI static class mce::Color const BLUE;
    MCAPI static class mce::Color const BROWN;
    MCAPI static class mce::Color const CYAN;
    MCAPI static class mce::Color const GRAY;
    MCAPI static class mce::Color const GREEN;
    MCAPI static class mce::Color const LIGHT_BLUE;
    MCAPI static class mce::Color const LIGHT_GREEN;
    MCAPI static class mce::Color const MAGENTA;
    MCAPI static class mce::Color const ORANGE;
    MCAPI static class mce::Color const PINK;
    MCAPI static class mce::Color const PURPLE;
    MCAPI static class mce::Color const RED;
    MCAPI static class mce::Color const SILVER;
    MCAPI static class mce::Color const WHITE;
    MCAPI static class mce::Color const YELLOW;
    MCAPI static enum PaletteColor fromByte(unsigned char);
    MCAPI static class mce::Color const& getColor(enum PaletteColor);

protected:

private:

};