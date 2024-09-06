#pragma once
#include "PhysicsContact.h"


class b2Contact;

namespace Hydro
{
    struct PhysicsContact2D : PhysicsContact<class PhysicsWorld2D, class PhysicsBody2D, b2Contact> {};
}
