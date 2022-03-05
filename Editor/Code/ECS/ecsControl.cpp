#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsScript.h"
#include "ecsWorldPlacement.h"
#include "flecs.h"
#include "../Input/InputHandler.h"

void register_ecs_control_systems(flecs::world* ecs)
{
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
}
