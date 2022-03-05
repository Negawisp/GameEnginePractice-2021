#include "ecsMesh.h"
#include "ecsSystems.h"
#include "ecsScript.h"
#include "ecsWorldPlacement.h"

void register_ecs_script_systems(flecs::world* ecs)
{
	static auto scriptSystemQuery = ecs->query<ScriptSystemPtr>();

	ecs->system<ScriptNodeComponent, const Position>()
		.each([&](flecs::entity e, ScriptNodeComponent& scriptNode, const Position& pos)
			{
				scriptNode.ptr->Update(e.delta_time());
			});


	ecs->system<const Controllable, ScriptNodeComponent, CameraPosition>()
		.each([&](flecs::entity e, const Controllable&, ScriptNodeComponent& scriptNode, CameraPosition& cameraPos)
			{
				Ogre::Vector3 vCameraPosition = scriptNode.ptr->GetCameraPosition();
				cameraPos.x = vCameraPosition.x;
				cameraPos.y = vCameraPosition.y;
				cameraPos.z = vCameraPosition.z;
			});

	ecs->system<const Controllable, ScriptNodeComponent, EditorNodeComponent, Position>()
		.each([&](flecs::entity e, const Controllable&, ScriptNodeComponent& scriptNode, EditorNodeComponent& editorNode, Position& pos)
			{
				Ogre::Vector3 vPosition = scriptNode.ptr->GetPosition();
				pos.x = vPosition.x;
				pos.y = vPosition.y;
				pos.z = vPosition.z;

				editorNode.ptr->SetPosition(vPosition);
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
}