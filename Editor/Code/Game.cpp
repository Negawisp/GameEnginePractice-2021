#include "Game.h"
#include "ECS/ecsEditor.h"
#include "ECS/ecsMesh.h"
#include "ECS/ecsSystems.h"
#include "ECS/ecsWorldPlacement.h"
#include "ECS/ecsControl.h"
#include <stdlib.h>

Game::Game()
{
	m_pEcs = new flecs::world();
	m_pFileSystem = new FileSystem();
	m_pEditorSystem = new EditorSystem();
	m_pResourceManager = new ResourceManager(m_pFileSystem->GetMediaRoot());
	m_pInputHandler = new InputHandler(m_pFileSystem->GetMediaRoot());
	m_pRenderEngine = new RenderEngine(m_pResourceManager, m_pEditorSystem, m_pInputHandler);
	m_pScriptSystem = new ScriptSystem(m_pInputHandler, m_pFileSystem->GetScriptsRoot());
	m_pEntityManager = new EntityManager(m_pRenderEngine, m_pEditorSystem, m_pScriptSystem, m_pEcs);
	m_pLoadingSystem = new LoadingSystem(m_pEntityManager, m_pFileSystem, m_pFileSystem->GetSavesRoot());

	m_Timer.Start();
	
	m_pEcs->entity("inputHandler")
		.set(InputHandlerPtr{ m_pInputHandler });
	m_pEcs->entity("scriptSystem")
		.set(ScriptSystemPtr{ m_pScriptSystem });
	m_pEcs->entity("editorSystem")
		.set(EditorSystemPtr{ m_pEditorSystem });

	m_pLoadingSystem->LoadFromXML("initialScene.xml");

	register_ecs_control_systems(m_pEcs);
	register_ecs_placement_systems(m_pEcs);
	register_ecs_script_systems(m_pEcs);
	register_ecs_editor_systems(m_pEcs);
	register_ecs_static_systems(m_pEcs);
	register_ecs_mesh_systems(m_pEcs);
}

Game::~Game()
{
	SAFE_DELETE(m_pEcs);
	SAFE_DELETE(m_pFileSystem);
	SAFE_DELETE(m_pEditorSystem);
	SAFE_DELETE(m_pResourceManager);
	SAFE_DELETE(m_pInputHandler);
	SAFE_DELETE(m_pRenderEngine);
	SAFE_DELETE(m_pScriptSystem);
	SAFE_DELETE(m_pEntityManager);
	SAFE_DELETE(m_pLoadingSystem);
}

void Game::Run()
{
	m_Timer.Reset();

	m_pEcs->progress();

	while (true)
	{
		m_pRenderEngine->GetRT()->RC_BeginFrame();

		m_Timer.Tick();

		if (m_pInputHandler)
			m_pInputHandler->Update();

		if (!Update())
			break;

		m_pRenderEngine->GetRT()->RC_EndFrame();
	}
}

bool Game::Update()
{
	m_pEcs->progress();

	if (m_pEditorSystem->IsSignalSave()) {
		m_pLoadingSystem->SaveToXML("initialScene.xml");
		m_pEditorSystem->SignalSaved();
	}

	return true;
}
