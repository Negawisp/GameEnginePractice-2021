#pragma once

#include "EditorNode.h"
#include "ImguiEditor/ImguiEditor.h"

struct EntityInfo;

class EditorSystem
{
	friend class ImguiEditor;

public:
	const float DEFAULT_HITBOX_SIZE = 3.f;

	EditorSystem();
	~EditorSystem();

	void Init(HWND mainWindowHandle);

	EditorNode* CreateNode(EntityInfo entityInfo, uint32_t id, flecs::entity entity);

	ImguiEditor* GetImguiEditor();
	bool GetCursorPosition(Ogre::Vector2* out_point);

	void SetInspectorCamera(Ogre::Camera* inspectorCamera);
	bool GetInspectorCamera(Ogre::Camera** out_pInspectorCamera);

	bool IsSignalSave();
	void SignalSaved();

private:
	ImguiEditor* m_pImguiEditor;
	bool b_signalSave;

	HWND m_nMainWindowHandle;
	Ogre::Camera* m_pInspectorCamera;

	std::vector<EditorNode*> m_pEditorNodes;

	void SignalSave();
};

