// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Vec3 {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_VEC3
public:
    class Vec3& operator=(class Vec3 const&) = delete;
    Vec3(class Vec3 const&) = delete;
    Vec3() = delete;
#endif

public:
    MCAPI class Vec3 abs() const;
    MCAPI class Vec3 ceil() const;
    MCAPI float distanceToLineSquared(class Vec3 const&, class Vec3 const&) const;
    MCAPI float distanceToSqr(class Vec3 const&) const;
    MCAPI class Vec3 floor(float) const;
    MCAPI bool isNan() const;
    MCAPI bool isNear(class Vec3 const&, float) const;
    MCAPI float maxComponent() const;
    MCAPI class Vec3 normalized() const;
    MCAPI class Vec3 operator+(class Vec3 const&);
    MCAPI class Vec3 operator-(class Vec3 const&);
    MCAPI bool operator==(class Vec3 const&);
    MCAPI std::string toString() const;
    MCAPI class Vec3 xz() const;
    MCAPI static class Vec3 const HALF;
    MCAPI static class Vec3 const MAX;
    MCAPI static class Vec3 const MIN;
    MCAPI static class Vec3 const NEG_UNIT_X;
    MCAPI static class Vec3 const NEG_UNIT_Y;
    MCAPI static class Vec3 const NEG_UNIT_Z;
    MCAPI static class Vec3 const ONE;
    MCAPI static class Vec3 const TWO;
    MCAPI static class Vec3 const UNIT_X;
    MCAPI static class Vec3 const UNIT_Y;
    MCAPI static class Vec3 const UNIT_Z;
    MCAPI static class Vec3 const ZERO;
    MCAPI static class Vec3 clamp(class Vec3 const&, class Vec3 const&, class Vec3 const&);
    MCAPI static class Vec3 directionFromRotation(class Vec2 const&);
    MCAPI static class Vec2 rotationFromDirection(class Vec3 const&);

protected:

private:

};