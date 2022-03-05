#include "EditorSystem.h"
#include "../../Code/EntityManager.h"

EditorSystem::EditorSystem()
{
	b_signalSave = false;
	i_mainWindowHandle = nullptr;
	m_pImguiEditor = new ImguiEditor(this);
}

EditorSystem::~EditorSystem()
{
	delete(m_pImguiEditor);
	for (EditorNode* node : m_pEditorNodes) {
		delete(node);
	}
}

void EditorSystem::Init(HWND mainWindowHandle)
{
	i_mainWindowHandle = mainWindowHandle;
	m_pImguiEditor->Init();
}

EditorNode* EditorSystem::CreateNode(EntityInfo entityInfo, uint32_t id)
{
	EditorNode* node = new EditorNode();
	
	node->SetId(id);
	node->SetEntityName(entityInfo.entityName);
	node->SetMeshName(entityInfo.meshName);
	node->SetPosition(entityInfo.position);
	node->SetRotation(entityInfo.rotation);

	m_pEditorNodes.push_back(node);

	return node;
}

ImguiEditor* EditorSystem::GetImguiEditor()
{
	return m_pImguiEditor;
}

bool EditorSystem::GetCursorPosition(POINT* point)
{
	if (i_mainWindowHandle == nullptr) {
		return false;
	}

	GetCursorPos(point);
	ScreenToClient(i_mainWindowHandle, point);
	return true;
}

bool EditorSystem::IsSignalSave()
{
	return b_signalSave;
}

void EditorSystem::SignalSaved()
{
	b_signalSave = false;
}

void EditorSystem::SignalSave()
{
	b_signalSave = true;
}
