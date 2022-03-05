#pragma once
#include "Ogre.h"
#include "../ECS/ecsEditor.h"

class EditorNode
{
public:

	uint32_t GetId() const { return m_nIdx; }
	void SetId(uint32_t idx) { m_nIdx = idx; }

	Ogre::String GetEntityName() const { return m_strEntityName; }
	void SetEntityName(Ogre::String name) { m_strEntityName = name; }

	Ogre::String GetMeshName() const { return m_strMeshName; }
	void SetMeshName(Ogre::String name) { m_strMeshName = name; }

	Ogre::Vector3 GetPosition() const { return m_vPosition; }
	void SetPosition(Ogre::Vector3 position) { m_vPosition = position; }

	Ogre::Quaternion GetOrientation() const { return m_qRotation; }
	void SetRotation(Ogre::Quaternion rotation) { m_qRotation = rotation; }

private:

	uint32_t m_nIdx;
	Ogre::String m_strEntityName;
	Ogre::String m_strMeshName;
	Ogre::Vector3 m_vPosition;
	Ogre::Quaternion m_qRotation;

};
