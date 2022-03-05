#pragma once

#include "EditorNode.h"
#include "ImguiEditor/ImguiEditor.h"

struct EntityInfo;

class EditorSystem
{
	friend class ImguiEditor;

public:
	EditorSystem();
	~EditorSystem();

	void Init(HWND mainWindowHandle);

	EditorNode* CreateNode(EntityInfo entityInfo, uint32_t id);

	ImguiEditor* GetImguiEditor();
	bool GetCursorPosition(POINT* out_point);

	bool IsSignalSave();
	void SignalSaved();

private:
	ImguiEditor* m_pImguiEditor;
	HWND i_mainWindowHandle;
	bool b_signalSave;

	std::vector<EditorNode*> m_pEditorNodes;

	void SignalSave();
};

