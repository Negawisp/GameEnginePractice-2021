#pragma once
#include "flecs.h"
#include "../EditorSystem/EditorNode.h"

struct Hovered {};

struct Selected {};

struct EditorNodeComponent
{
	class EditorNode* ptr;
};

struct SphereHitbox : public Ogre::Sphere {
	using Ogre::Sphere::Sphere;
};

void register_ecs_editor_systems(flecs::world* ecs);