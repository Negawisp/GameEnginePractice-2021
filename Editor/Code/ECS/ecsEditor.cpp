#include "ecsEditor.h"
#include "ecsScript.h"
#include "ecsWorldPlacement.h"

void register_ecs_editor_systems(flecs::world* ecs)
{
	ecs->system<const EditorNodeComponent, ScriptNodeComponent>()
		.each([&](const EditorNodeComponent& editorNode, ScriptNodeComponent& scriptNode)
			{
				scriptNode.ptr->SetPosition(editorNode.ptr->GetPosition());
				scriptNode.ptr->SetOrientation(editorNode.ptr->GetOrientation());
			});
}

