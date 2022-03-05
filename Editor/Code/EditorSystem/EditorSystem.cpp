#include "EditorSystem.h"
#include "../../Code/EntityManager.h"

EditorSystem::EditorSystem()
{
	b_signalSave = false;
	m_nMainWindowHandle = nullptr;
	m_pInspectorCamera = nullptr;
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
	m_nMainWindowHandle = mainWindowHandle;
	m_pImguiEditor->Init();
}

EditorNode* EditorSystem::CreateNode(EntityInfo entityInfo, uint32_t id, flecs::entity entity)
{
	EditorNode* node = new EditorNode();
	
	node->SetId(id);
	node->SetEntityName(entityInfo.entityName);
	node->SetMeshName(entityInfo.meshName);
	node->SetPosition(entityInfo.position);
	node->SetRotation(entityInfo.rotation);

	m_pEditorNodes.push_back(node);

	entity.set(SphereHitbox(Ogre::Vector3(0.f, 0.f, 0.f), DEFAULT_HITBOX_SIZE));

	return node;
}

ImguiEditor* EditorSystem::GetImguiEditor()
{
	return m_pImguiEditor;
}

bool EditorSystem::GetCursorPosition(Ogre::Vector2* out_point)
{
	if (m_nMainWindowHandle == nullptr) {
		return false;
	}
	
	RECT windowRect;
	POINT point;

	GetCursorPos(&point);
	GetWindowRect(m_nMainWindowHandle, &windowRect);
	ScreenToClient(m_nMainWindowHandle, &point);

	out_point->x = Ogre::Real(point.x) / (Ogre::Real(windowRect.right - windowRect.left));
	out_point->y = Ogre::Real(point.y) / (Ogre::Real(windowRect.bottom - windowRect.top));

	return true;
}

void EditorSystem::SetInspectorCamera(Ogre::Camera* inspectorCamera)
{
	m_pInspectorCamera = inspectorCamera;
}

bool EditorSystem::GetInspectorCamera(Ogre::Camera** out_pInspectorCamera)
{
	if (!m_pInspectorCamera) {
		return false;
	}

	*out_pInspectorCamera = m_pInspectorCamera;
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
