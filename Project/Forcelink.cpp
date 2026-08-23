#include "Forcelink.h"

#include "Assets/Player.h"
#include "Assets/Simon.h"
#include "Assets/ObstacleSpawner.h"
#include "Assets/Obstacle.h"
#include "Assets/Scripts/PlayerMovement.h"




#ifdef ECLIPSED_EDITOR
CREATE_COMPONENT(Player);
CREATE_COMPONENT(Simon);
CREATE_COMPONENT(ObstacleSpawner);
CREATE_COMPONENT(Obstacle);
CREATE_COMPONENT(PlayerMovement);


static ComponentEntry g_components[] = {
	COMPONENT_ENTRY(Player)
	COMPONENT_ENTRY(Simon)
	COMPONENT_ENTRY(ObstacleSpawner)
	COMPONENT_ENTRY(Obstacle)
	COMPONENT_ENTRY(PlayerMovement)
};
#else
#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"

#define COMP_REG(TYPE)																						\
Eclipse::ComponentRegistry::Register(#TYPE, REGISTER_COMPONENT_CALLBACK(TYPE));								\
Eclipse::ComponentRegistry::RegisterInspector(#TYPE, REGISTER_COMPONENT_CALLBACK_NORMAL(TYPE));
#endif

ComponentRegistrySnapshot __cdecl RegisterComponents()
{
#ifdef ECLIPSED_EDITOR
	ComponentRegistrySnapshot snapshot;

	snapshot.components = g_components;
	snapshot.count = static_cast<int>(sizeof(g_components) / sizeof(g_components[0]));

	return snapshot;
#else
	COMP_REG(Player);
	COMP_REG(Simon);
	COMP_REG(ObstacleSpawner);
	COMP_REG(Obstacle);
	return {};
#endif
}
