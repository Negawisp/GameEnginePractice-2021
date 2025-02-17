#pragma once

#include <string>

#include "../Input/InputHandler.h"
#include "../RenderNode.h"

#include "LuaBridge.h"
#include "flecs.h"
#include "../ECS/ecsWorldPlacement.h"
#include "../ECS/ecsControl.h"
#include "../ECS/ecsMesh.h"
#include "../ECS/ecsControl.h"
#include "../ECS/ecsStatic.h"
#include "../ECS/ecsScript.h"
#include "../FileSystem/GEFile.h"

template <typename T>
struct EnumWrapper
{
	static typename std::enable_if<std::is_enum<T>::value, void>::type push(lua_State* L, T value)
	{
		lua_pushnumber(L, static_cast<std::size_t> (value));
	}

	static typename std::enable_if<std::is_enum<T>::value, T>::type get(lua_State* L, int index)
	{
		return static_cast <T> (lua_tointeger(L, index));
	}
};

namespace luabridge {

	template <>
	struct luabridge::Stack <EInputCommand> : EnumWrapper <EInputCommand>
	{
	};

}

class ScriptNode
{
public:
	ScriptNode(std::string strScriptPath, InputHandler* pInputHandler, flecs::entity& ent);
	~ScriptNode();

	void Update(float dt);
	void ReloadScript();

	Ogre::Vector3 GetPosition() const;
	void SetPosition(Ogre::Vector3 position);
	
	Ogre::Quaternion GetOrientation() const;
	void SetOrientation(Ogre::Quaternion orientation);

	Ogre::Vector3 GetCameraPosition() const;
	std::string GetMeshName() const;
	std::string GetScriptName() const;
	bool GetIsStatic() const;

private:
	std::string m_strScriptPath;

	InputHandler* m_pInputHandler;
	
	lua_State* m_script;
	GEFile* m_pScriptFile;

	void AddDependencies(lua_State* L);

	const char* m_EntityFieldName = "Entity";
	const char* m_PropertiesFieldName = "Properties";
	const char* m_ControllableFieldName = "Controllable";
	const char* m_CameraFieldName = "Camera";
	const char* m_MeshNameFieldName = "MeshName";
	const char* m_NameFieldName = "Name";
	const char* m_ParametersFieldName = "Parameters";
	const char* m_StaticsFieldName = "IsStatic";

	const char* m_GetPositionFunctionName = "GetPosition";
	const char* m_SetPositionFunctionName = "SetPosition";
	const char* m_GetCameraPositionFunctionName = "GetCameraPosition";
	const char* m_GetCameraOffsetFunctionName = "GetCameraOffset";
	const char* m_SetCameraOffsetFunctionName = "SetCameraOffset";
	const char* m_GetOrientationFunctionName = "GetOrientation";
	const char* m_SetOrientationFunctionName = "SetOrientation";
	const char* m_OnInitFunctionName = "OnInit";
	const char* m_OnUpdateFunctionName = "OnUpdate";
};
