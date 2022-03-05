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
	void Update(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* camera);

private:
	EditorSystem* m_pEditorSystem;
	
	void AddEditorMenu(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* camera);
	void AddCursorPosition();
	void AddCameraSettings(Ogre::Camera* camera);
	void AddEntityTree();
};

