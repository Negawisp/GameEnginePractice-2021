#pragma once
#include "flecs.h"
#include <OgreVector3.h>

struct Position : public Ogre::Vector3
{
	using Ogre::Vector3::Vector3;
};

struct Orientation : public Ogre::Quaternion
{
	using Ogre::Quaternion::Quaternion;
};

void register_ecs_placement_systems(flecs::world* ecs);