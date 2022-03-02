#include "LoadingSystem.h"
#include "../EntityManager.h"
#include "../FileSystem/FileSystem.h"
#include "OgreSceneManager.h"
#include "tinyxml.h"
#include <regex>

LoadingSystem::LoadingSystem(EntityManager* pEntityManager, FileSystem* pFileSystem, const std::string& scriptsRoot) :
	m_pEntityManager(pEntityManager),
	m_pFileSystem(pFileSystem),
	m_strSavesRootPath(scriptsRoot)
{

}

void LoadingSystem::LoadFromXML(const std::string fileName)
{
	const auto pathName = m_strSavesRootPath + fileName;

	TiXmlDocument doc(pathName.c_str());

	if (doc.LoadFile())
	{
		const auto elem = doc.FirstChildElement("scene");
		for (TiXmlElement* e = elem->FirstChildElement("character"); e != nullptr; e = e->NextSiblingElement("character"))
		{
			EntityInfo currentCharacter;
			currentCharacter.entityName = e->Attribute("name");
			currentCharacter.meshName = e->Attribute("meshName");
			currentCharacter.scriptName = e->Attribute("scriptName");
			currentCharacter.position = ParsePosition(e->Attribute("position"));
			currentCharacter.rotation = ParseQuaternion(e->Attribute("rotation"));

			m_pEntityManager->CreateEntity(currentCharacter);
		}
	}
}

void LoadingSystem::SaveToXML(const std::string fileName)
{
	const auto pathName = m_strSavesRootPath + fileName;
	TiXmlDocument doc(pathName.c_str());
	TiXmlElement* sceneElem = new TiXmlElement("scene");
	TiXmlNode* sceneNode = doc.LinkEndChild(sceneElem);

	auto entityQueue = m_pEntityManager->GetEntityQueue();

	for (auto& entity : entityQueue)
	{
		auto vecPosition = entity.second.pRenderNode->GetPosition();
		auto quatRotation = entity.second.pRenderNode->GetOrientation();

		TiXmlElement* characterElem = new TiXmlElement("character");
		
		Ogre::String name = entity.second.entityName;
		Ogre::String scriptName = entity.second.pScriptNode->GetScriptName();
		scriptName = scriptName.substr(scriptName.find_last_of(m_pFileSystem->e_cNativeSlash));
		Ogre::String meshName = entity.second.pRenderNode->GetMeshName();
		Ogre::String position = std::to_string(vecPosition.x) + "," + std::to_string(vecPosition.y) + "," + std::to_string(vecPosition.z);
		Ogre::String rotation = std::to_string(quatRotation.x) + "," + std::to_string(quatRotation.y) + "," + std::to_string(quatRotation.z) + "," + std::to_string(quatRotation.w);

		characterElem->SetAttribute("name", name.c_str());
		characterElem->SetAttribute("scriptName", scriptName.c_str());
		characterElem->SetAttribute("meshName", meshName.c_str());
		characterElem->SetAttribute("position", position.c_str());
		characterElem->SetAttribute("rotation", rotation.c_str());

		sceneNode->LinkEndChild(characterElem);
	}

	doc.SaveFile();
}

LoadingSystem::~LoadingSystem()
{

};

Ogre::Vector3 LoadingSystem::ParsePosition(const char* strPosition)
{
	std::regex regex("[+-]?([0-9]*[.])?[0-9]+");
	std::cmatch match;

	Ogre::Vector3 vPosition;

	std::regex_search(strPosition, match, regex);
	vPosition.x = std::stof(match[0]);

	strPosition = match.suffix().first;
	std::regex_search(strPosition, match, regex);
	vPosition.y = std::stof(match[0]);

	strPosition = match.suffix().first;
	std::regex_search(strPosition, match, regex);
	vPosition.z = std::stof(match[0]);

	return vPosition;
}

Ogre::Quaternion LoadingSystem::ParseQuaternion(const char* strQuaternion)
{
	if (strQuaternion == NULL || strlen(strQuaternion) < 1) {
		Ogre::Quaternion quaternion;
		return quaternion;
	}

	std::regex regex("[+-]?([0-9]*[.])?[0-9]+");
	std::cmatch match;

	Ogre::Quaternion quaternion;

	std::regex_search(strQuaternion, match, regex);
	quaternion.x = std::stof(match[0]);

	strQuaternion = match.suffix().first;
	std::regex_search(strQuaternion, match, regex);
	quaternion.y = std::stof(match[0]);

	strQuaternion = match.suffix().first;
	std::regex_search(strQuaternion, match, regex);
	quaternion.z = std::stof(match[0]);

	strQuaternion = match.suffix().first;
	std::regex_search(strQuaternion, match, regex);
	quaternion.w = std::stof(match[0]);

	return quaternion;
}