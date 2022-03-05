#pragma once
#include <vector>
#include "Ogre.h"
#include "OgreCamera.h"
#include "ImguiWrapper/ImguiWrapper.h"

class RenderNode;
class EditorSystem;

class ImguiEditor
{
public:
	ImguiEditor(EditorSystem* pEditorSystem);

	void Init();
	void Update();

private:
	EditorSystem* m_pEditorSystem;
	
	void AddEditorMenu();
	void AddCursorPosition();
	void AddCameraSettings();
	void AddEntityTree();
};

