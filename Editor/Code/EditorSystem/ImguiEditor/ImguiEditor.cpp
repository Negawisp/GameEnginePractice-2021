#include <math.h>
#include "ImguiEditor.h"
#include "../EditorSystem.h"
#include "../../RenderNode.h"
#include "../../EntityManager.h"

ImguiEditor::ImguiEditor(EditorSystem* pEditorSystem) :
	m_pEditorSystem(pEditorSystem)
{
}

void ImguiEditor::Init() {
	ImguiWrapper::Init();
}

void ImguiEditor::Update(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* pCamera) {
	ImguiWrapper::StartFrame();

	AddEditorMenu(pRenderNodes, pCamera);

	ImguiWrapper::Render();
}

void ImguiEditor::AddEditorMenu(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* camera) {
	ImGui::Begin("Editor");
	
	AddCursorPosition();

	if (!m_pEditorSystem->IsSignalSave()) {
		AddCameraSettings(camera);
		AddEntityTree();
		if (ImGui::Button("Save")) {
			m_pEditorSystem->SignalSave();
		}
	}
	else {
		ImGui::Text("Saving...");
	}

	ImGui::End();
}

void ImguiEditor::AddCursorPosition() {
	POINT point;
	if (!m_pEditorSystem->GetCursorPosition(&point)) {
		return;
	}
	ImGui::Text(("Mouse pos x=" + std::to_string(point.x) + " y=" + std::to_string(point.y)).c_str());
}

void ImguiEditor::AddCameraSettings(Ogre::Camera* camera) {
	// Position
	{
		Ogre::Vector3 cameraPos = camera->getPosition();
		ImGui::DragFloat3("Camera position", &cameraPos.x, 0.1f);
		camera->setPosition(cameraPos);
	}

	// Rotation
	{
		static Ogre::Vector3 prevCameraRotation;
		static Ogre::Vector3 cameraRotation(0., 0., 0.);

		Ogre::Vector3 vRotationDelta;
		Ogre::Quaternion qRotationDelta;
		Ogre::Quaternion rotation = camera->getOrientation();
		float phi = 0;

		ImGui::DragFloat3("Camera rotation", &cameraRotation.x, 0.01f);

		vRotationDelta = cameraRotation - prevCameraRotation;
		qRotationDelta = Ogre::Quaternion((Ogre::Radian)vRotationDelta.normalise(), vRotationDelta.normalisedCopy());
		camera->setOrientation(rotation * qRotationDelta);

		prevCameraRotation = cameraRotation;
	}
}


void ImguiEditor::AddEntityTree() {
	for (EditorNode* node : m_pEditorSystem->m_pEditorNodes) {
	//for (auto& renderNode : pRenderNodes) {
		if (ImGui::TreeNode((node->GetEntityName() + std::to_string(node->GetId())).c_str())) {
			ImGui::TreePop();
			{
				Ogre::Vector3 pos = node->GetPosition();
				Ogre::Quaternion orient = node->GetOrientation();

				ImGui::DragFloat3(("Entity " + std::to_string(node->GetId()) + " pos").c_str(), &pos.x, .1f);
				node->SetPosition(pos);
			}

			{
				static Ogre::Vector3 prevRotation(0., 0., 0.);
				static Ogre::Vector3 vRotation(0., 0., 0.);

				Ogre::Vector3 vRotationDelta;
				Ogre::Quaternion qRotationDelta;
				Ogre::Quaternion qRotation = node->GetOrientation();
				float phi = 0;

				ImGui::DragFloat3(("Entity " + std::to_string(node->GetId()) + " rotation").c_str(), &vRotation.x, 0.01f);

				vRotationDelta = vRotation - prevRotation;
				qRotationDelta = Ogre::Quaternion((Ogre::Radian)vRotationDelta.normalise(), vRotationDelta.normalisedCopy());
				node->SetRotation(qRotationDelta * qRotation);

				prevRotation = vRotation;
			}
		}
	}
}

/*
void ImguiEditor::AddEntityTree() {
	for (Entity& entity : m_pEditorSystem->m_entities) {
		if (ImGui::TreeNode((entity.entityName + std::to_string(entity.idx)).c_str())) {
			ImGui::TreePop();
			{
				Ogre::Vector3 pos = entity.pScriptNode->GetPosition();
				Ogre::Quaternion orient = entity.pScriptNode->GetOrientation();

				ImGui::DragFloat3(("Entity " + std::to_string(entity.idx) + " pos").c_str(), &pos.x, .1f);
				entity.pScriptNode->SetPosition(pos);
			}

			{
				static Ogre::Vector3 prevRotation(0., 0., 0.);
				static Ogre::Vector3 vRotation(0., 0., 0.);

				Ogre::Vector3 vRotationDelta;
				Ogre::Quaternion qRotationDelta;
				Ogre::Quaternion qRotation = entity.pScriptNode->GetOrientation();
				float phi = 0;

				ImGui::DragFloat3(("Entity " + std::to_string(entity.idx) + " rotation").c_str(), &vRotation.x, 0.01f);

				vRotationDelta = vRotation - prevRotation;
				//entity.pScriptNode->Rotate(rotationDelta.normalisedCopy(), (Ogre::Radian)rotationDelta.normalise());

				qRotationDelta = Ogre::Quaternion((Ogre::Radian)vRotationDelta.normalise(), vRotationDelta.normalisedCopy());
				entity.pScriptNode->SetRotation(qRotationDelta * qRotation);

				prevRotation = vRotation;
			}
		}
	}
}
*/