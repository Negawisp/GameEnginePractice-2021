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

	/*
	ecs->system<RenderNodeComponent, const Orientation>()
		.each([&](RenderNodeComponent& renderNode, const Orientation& orient)
			{
				renderNode.ptr->SetOrientation(orient);
			});
	/*
	static auto inputQuery = ecs->query<InputHandlerPtr>();
	static auto selectionQuery = ecs->query<Position>();

	ecs->system<InputHandlerPtr>()
		.each([&](flecs::entity e, const InputHandlerPtr& input)
			{
				if (!input.ptr->GetInputState().test(eIC_Select)) {
					return;
				}
				// Ray ray = RayFromCameraToMouse();
				// float l_min = infinity;
				// node selected = null;

				selectionQuery.each([&](Position position)
					{
						// l = ray.intersects(sphere(position, r=100.f));
						// if (l < l_min) { l_min = l; selected = position->node; }
					});
			});

	ecs->system<const Controllable, ScriptNodeComponent, CameraPosition>()
		.each([&](flecs::entity e, const Controllable&, ScriptNodeComponent& scriptNode, CameraPosition& cameraPos)
			{
				Ogre::Vector3 vCameraPosition = scriptNode.ptr->GetCameraPosition();
				cameraPos.x = vCameraPosition.x;
				cameraPos.y = vCameraPosition.y;
				cameraPos.z = vCameraPosition.z;
			});

	ecs->system<const Controllable, ScriptNodeComponent, Position>()
		.each([&](flecs::entity e, const Controllable&, ScriptNodeComponent& scriptNode, Position& pos)
			{
				Ogre::Vector3 vPosition = scriptNode.ptr->GetPosition();
				pos.x = vPosition.x;
				pos.y = vPosition.y;
				pos.z = vPosition.z;
			});

	ecs->system<ScriptNodeComponent, Orientation>()
		.each([&](flecs::entity e, ScriptNodeComponent& scriptNode, Orientation& orient)
			{
				Ogre::Quaternion orientation = scriptNode.ptr->GetOrientation();
				orient.x = orientation.x;
				orient.y = orientation.y;
				orient.z = orientation.z;
				orient.w = orientation.w;
			});
	*/
}

