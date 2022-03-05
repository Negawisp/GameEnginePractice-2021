#include "ecsSystems.h"
#include "ecsEditor.h"
#include "ecsScript.h"
#include "ecsWorldPlacement.h"
#include "../Input/InputHandler.h"
#include "../EditorSystem/EditorSystem.h"

void register_ecs_editor_systems(flecs::world* ecs)
{
	static auto editorQuery = ecs->query<EditorSystemPtr>();
	static auto inputQuery = ecs->query<InputHandlerPtr>();
	static auto selectionQuery = ecs->query<Position, SphereHitbox>();

	static Ogre::Ray lastRay;
	static float lmin = INFINITY;
	static flecs::entity prevSelected;
	static bool prevSelectedExists = false;

	ecs->system<Position, SphereHitbox>()
		.each([&](flecs::entity e, Position& position, SphereHitbox& hitbox) {
			// Checking "select" input
			bool isSelectInput = false;

			inputQuery.each([&](InputHandlerPtr& inputHandler) {
				isSelectInput = inputHandler.ptr->GetInputState().test(eIC_Select);
			});
			if (!isSelectInput) {
				return;
			}

			// Checking if window and camera are active and receiving cursor pos and camera
			Ogre::Vector2 cursorPos;
			Ogre::Camera* cam;
			bool camAndCursorOk = true;

			editorQuery.each([&](EditorSystemPtr& editorSystem) {
				camAndCursorOk &= editorSystem.ptr->GetCursorPosition(&cursorPos);
				camAndCursorOk &= editorSystem.ptr->GetInspectorCamera(&cam);
			});
			if (!camAndCursorOk) {
				return;
			}

			// Raycasting from cam to scene
			Ogre::Ray ray;
			cam->getCameraToViewportRay(cursorPos.x, cursorPos.y, &ray);
			ray.setOrigin(cam->getPosition());

			Ogre::Ray rayLast = lastRay;

			if (FLT_EPSILON < (lastRay.getDirection() - ray.getDirection()).normalise() ||
				FLT_EPSILON < (lastRay.getOrigin() - ray.getOrigin()).normalise() ) {
				lastRay = ray;
				lmin = INFINITY;

				if (prevSelectedExists) {
					prevSelected.remove<Selected>();
				}
				prevSelectedExists = false;
			}

			// Intersecting with entities
			std::pair<bool, Ogre::Real> intersectionResult(false, 0.);

			Ogre::Sphere positionedHitbox(position + hitbox.getCenter(), hitbox.getRadius());
			intersectionResult = ray.intersects(positionedHitbox);
				
			if (intersectionResult.first && intersectionResult.second < lmin) {
				if (prevSelectedExists) {
					prevSelected.remove<Selected>();
				}
				lmin = intersectionResult.second;
				e.add<Selected>();
				prevSelected = e;
				prevSelectedExists = true;
			}
		});

	// Apply position and rotation from editorNode to scriptNode
	ecs->system<const EditorNodeComponent, ScriptNodeComponent>()
		.each([&](const EditorNodeComponent& editorNode, ScriptNodeComponent& scriptNode) {
			scriptNode.ptr->SetPosition(editorNode.ptr->GetPosition());
			scriptNode.ptr->SetOrientation(editorNode.ptr->GetOrientation());
		});

	// Move selected entity with arrow/WASD inputs
	static Ogre::Real editorVelocity(0.1f);
	static Ogre::Vector3 directionLeft(-1.0f, 0.0f, 0.0f);
	static Ogre::Vector3 directionRight(1.0f, 0.0f, 0.0f);
	static Ogre::Vector3 directionUp(0.0f, 1.0f, 0.0f);
	static Ogre::Vector3 directionDown(0.0f, -1.0f, 0.0f);
	ecs->system<const Selected, ScriptNodeComponent>()
		.each([&](flecs::entity e, const Selected&, ScriptNodeComponent& scriptNode) {
			Ogre::Quaternion cameraRotation;
			bool cameraObtained;
			Ogre::Camera* camera;

			editorQuery.each([&](EditorSystemPtr& editor) {
				cameraObtained = editor.ptr->GetInspectorCamera(&camera);
			});
			if (!cameraObtained) {
				return;
			}
			cameraRotation = camera->getOrientation();

			Ogre::Vector3 position = scriptNode.ptr->GetPosition();
			Ogre::Vector3 direction(0.0f, 0.0f, 0.0f);
			inputQuery.each([&](InputHandlerPtr& inputHandler) {
				if (inputHandler.ptr->GetInputState().test(eIC_MoveForward)) {
					direction += directionUp;
				}
				if (inputHandler.ptr->GetInputState().test(eIC_MoveBack)) {
					direction += directionDown;
				}
				if (inputHandler.ptr->GetInputState().test(eIC_TurnLeft)) {
					direction += directionLeft;
				}
				if (inputHandler.ptr->GetInputState().test(eIC_TurnRight)) {
					direction += directionRight;
				}
			});

			position += cameraRotation * direction * editorVelocity;
			scriptNode.ptr->SetPosition(position);
		});
}

