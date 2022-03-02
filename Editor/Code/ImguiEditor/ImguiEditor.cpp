#include <math.h>
#include "ImguiEditor.h"
#include "../RenderNode.h"

void ImguiEditor::InitImgui() {
	ImguiWrapper::Init();
}

void ImguiEditor::Update(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* pCamera) {
	ImguiWrapper::StartFrame();

	AddEditorMenu(pRenderNodes, pCamera);

	ImguiWrapper::Render();
}

void ImguiEditor::AddEditorMenu(std::vector<RenderNode*>& pRenderNodes, Ogre::Camera* camera) {
	ImGui::Begin("Editor");

	if (!IsSignalSave()) {
		AddCameraSettings(camera);
		AddEntityTree(pRenderNodes);
		if (ImGui::Button("Save")) {
			SignalSave();
		}
	}
	else {
		ImGui::Text("Saving...");
	}

	ImGui::End();
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

		Ogre::Vector3 rotationDelta;
		float phi = 0;

		ImGui::DragFloat3("Camera rotation", &cameraRotation.x, 0.01f);

		rotationDelta = cameraRotation - prevCameraRotation;
		camera->rotate(rotationDelta.normalisedCopy(), (Ogre::Radian)rotationDelta.normalise());

		prevCameraRotation = cameraRotation;
	}
}

void ImguiEditor::AddEntityTree(std::vector<RenderNode*>& pRenderNodes) {
	for (auto& renderNode : pRenderNodes) {
		if (ImGui::TreeNode((renderNode->GetMeshName() + std::to_string(renderNode->GetId())).c_str())) {
			ImGui::TreePop();
			{
				Ogre::Vector3 pos = renderNode->GetPosition();
				Ogre::Quaternion orient = renderNode->GetOrientation();

				ImGui::DragFloat3(("Entity " + std::to_string(renderNode->GetId()) + " pos").c_str(), &pos.x, .1f);
				renderNode->SetPosition(pos);
			}

			{
				static Ogre::Vector3 prevRotation(0., 0., 0.);
				static Ogre::Vector3 rotation(0., 0., 0.);

				Ogre::Vector3 rotationDelta;
				float phi = 0;

				ImGui::DragFloat3(("Entity " + std::to_string(renderNode->GetId()) + " rotation").c_str(), &rotation.x, 0.01f);

				rotationDelta = rotation - prevRotation;
				renderNode->Rotate(rotationDelta.normalisedCopy(), (Ogre::Radian)rotationDelta.normalise());

				prevRotation = rotation;
			}
		}
	}
}

void ImguiEditor::SignalSave() {
	m_signalSave = true;
}

void ImguiEditor::SignalSaved() {
	m_signalSave = false;
}

bool ImguiEditor::IsSignalSave() {
	return m_signalSave;
}

void ImguiEditor::WaitMainThreadSaved() {

}