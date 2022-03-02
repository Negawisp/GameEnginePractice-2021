#pragma once
#include <vector>
#include "Ogre.h"
#include "OgreCamera.h"
#include "ImguiWrapper/ImguiWrapper.h"

class RenderNode;

class ImguiEditor
{
public:
	void InitImgui();
	void Update(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* camera);

	bool IsSignalSave();
	void SignalSaved();

private:
	bool m_signalSave;

	void AddEditorMenu(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* camera);
	void AddCameraSettings(Ogre::Camera* camera);
	void AddEntityTree(std::vector<RenderNode*>& pRenderNodes);
	
	void SignalSave();
	void WaitMainThreadSaved();
};

