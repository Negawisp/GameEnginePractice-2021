#include "EntityManager.h"

EntityManager::EntityManager(RenderEngine* pRenderEngine, EditorSystem* pEditorSystem, ScriptSystem* pScriptSystem, flecs::world* ecs) :
	m_pRenderEngine(pRenderEngine),
	m_pEditorSystem(pEditorSystem),
	m_pEcs(ecs),
	m_pScriptSystem(pScriptSystem)
{
}

EntityManager::~EntityManager()
{
	m_entityQueue.clear();
}

void EntityManager::CreateEntity(std::string strScriptName)
{
	flecs::entity newEntity = m_pEcs->entity();
	uint32_t nIndex = GetNewIndex();

	ScriptNode* pScriptNode = m_pScriptSystem->CreateScriptNode(strScriptName, newEntity);

	Ogre::String strMeshName = pScriptNode->GetMeshName();
	RenderNode* pRenderNode = new RenderNode(nIndex, strMeshName);

	newEntity.set(EntityIndex{ nIndex })
		.set(RenderNodeComponent{ pRenderNode })
		.set(ScriptNodeComponent{ pScriptNode });

	m_pRenderEngine->GetRT()->RC_CreateSceneNode(pRenderNode);

	Entity entity;
	entity.pRenderNode = pRenderNode;
	entity.pScriptNode = pScriptNode;

	entity.idx = nIndex;
	
	m_entityQueue[nIndex] = entity;
}


void EntityManager::CreateEntity(const EntityInfo &fromSave)
{
	flecs::entity newEntity = m_pEcs->entity();
	uint32_t nIndex = GetNewIndex();

	EditorNode* pEditorNode = m_pEditorSystem->CreateNode(fromSave, nIndex, newEntity);

	ScriptNode* pScriptNode = m_pScriptSystem->CreateScriptNode(fromSave.scriptName, newEntity);
	pScriptNode->SetPosition(fromSave.position);
	pScriptNode->SetOrientation(fromSave.rotation);

	Ogre::String strEnityName = fromSave.entityName;
	Ogre::String strMeshName = fromSave.meshName;
	RenderNode* pRenderNode = new RenderNode(nIndex, strMeshName);

	newEntity.set(EntityIndex{ nIndex })
		.set(RenderNodeComponent{ pRenderNode })
		.set(EditorNodeComponent{ pEditorNode })
		.set(ScriptNodeComponent{ pScriptNode });

	m_pRenderEngine->GetRT()->RC_CreateSceneNode(pRenderNode);

	Entity entity;
	entity.idx = nIndex;
	entity.entityName = strEnityName;
	entity.pEditorNode = pEditorNode;
	entity.pRenderNode = pRenderNode;
	entity.pScriptNode = pScriptNode;

	m_entityQueue[nIndex] = entity;
}

uint32_t EntityManager::GetNewIndex() const
{
	return m_entityQueue.size();
}

std::unordered_map<uint32_t, Entity> EntityManager::GetEntityQueue() const
{
	return m_entityQueue;
}