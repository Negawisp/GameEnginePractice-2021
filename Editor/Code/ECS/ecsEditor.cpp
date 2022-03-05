#include "ecsSystems.h"
#include "ecsEditor.h"
#include "ecsScript.h"
#include "ecsWorldPlacement.h"
#include "../Input/InputHandler.h"

void register_ecs_editor_systems(flecs::world* ecs)
{
	static auto editorQuery = ecs->query<EditorSystemPtr>();
	static auto inputQuery = ecs->query<InputHandlerPtr>();
	static auto selectionQuery = ecs->query<Position>();

	// Make entity "hovered"
	ecs->system<InputHandlerPtr>()
		.each([&](flecs::entity e, const InputHandlerPtr& input)
			{
				if (!input.ptr->GetInputState().test(eIC_Select)) {
					return;
				}

				POINT a;
				input.ptr->GetCursorPosition(&a);

				// Ray ray = RayFromCameraToMouse();
				// float l_min = infinity;
				// node selected = null;

				selectionQuery.each([&](Position position)
					{
						// l = ray.intersects(sphere(position, r=100.f));
						// if (l < l_min) { l_min = l; selected = position->node; }
					});
			});

	// Apply position and rotation from editorNode to scriptNode
	ecs->system<const EditorNodeComponent, ScriptNodeComponent>()
		.each([&](const EditorNodeComponent& editorNode, ScriptNodeComponent& scriptNode)
			{
				scriptNode.ptr->SetPosition(editorNode.ptr->GetPosition());
				scriptNode.ptr->SetOrientation(editorNode.ptr->GetOrientation());
			});
}

