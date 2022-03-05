#pragma once

#include "Ogre.h"
#include "OgreRoot.h"
#include "OgreWindow.h"
#include "OgreItem.h"
#include "OgreMeshManager2.h"
#include "OgreMesh2.h"

#include "Compositor/OgreCompositorManager2.h"

#include "RenderSystems/Direct3D11/OgreD3D11Plugin.h"

#include "RenderThread.h"
#include "RenderNode.h"
#include "ResourceManager.h"

class EditorSystem;
class InputHandler;

class RenderEngine
{
	friend class RenderThread;

public:
	RenderEngine(ResourceManager* pResourceManager, EditorSystem* pEditorEngine, InputHandler* pInputHandler);
	~RenderEngine();
	RenderEngine(const RenderEngine&) = delete;
	RenderEngine& operator=(const RenderEngine&) = delete;

	void Update();

	bool GetQuit() { return m_bQuit; }
	void SetQuit(bool bQuit) { m_bQuit = bQuit; }

	RenderThread* GetRT() const { return m_pRT; }

	HWND GetWindowHanlde();

private:
	bool SetOgreConfig();

	void RT_Init();
	void RT_SetupDefaultCamera();
	void RT_SetupDefaultCompositor();
	void RT_LoadDefaultResources();
	void RT_SetupDefaultLight();
	void RT_CreateSceneNode(RenderNode* pRenderNode);

	void ImportV1Mesh(Ogre::String strMeshName);

	Ogre::Root* m_pRoot;
	Ogre::Window* m_pRenderWindow;
	Ogre::SceneManager* m_pSceneManager;
	Ogre::Camera* m_pCamera;
	Ogre::CompositorWorkspace* m_pWorkspace;
	Ogre::D3D11Plugin* m_pD3D11Plugin;

	RenderThread* m_pRT;
	ResourceManager* m_pResourceManager;
	
	EditorSystem* m_pEditorSystem;
	InputHandler* m_pInputHandler;

	std::vector<RenderNode*> m_RenderNodes;

	bool m_bQuit;
};

