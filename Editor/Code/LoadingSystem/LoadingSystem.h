#pragma once

#include <string>
#include "Ogre.h"

class EntityManager;
class FileSystem;

class LoadingSystem
{
public:
	LoadingSystem(EntityManager* pEntityManager, FileSystem* pFileSystem, const std::string& scriptsRoot);

	~LoadingSystem();
	void LoadFromXML(const std::string fileName);
	void SaveToXML(const std::string fileName);

private:
	EntityManager* m_pEntityManager;
	FileSystem* m_pFileSystem;
	std::string m_strSavesRootPath;

	Ogre::Vector3 ParsePosition(const char* strPosition);
	Ogre::Quaternion ParseQuaternion(const char* strQuaternion);
};

