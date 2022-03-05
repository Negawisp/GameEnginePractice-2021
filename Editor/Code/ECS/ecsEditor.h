#pragma once
#include "flecs.h"
#include "../EditorSystem/EditorNode.h"

struct Selected {};

struct EditorNodeComponent
{
	class EditorNode* ptr;
};

void register_ecs_editor_systems(flecs::world* ecs);