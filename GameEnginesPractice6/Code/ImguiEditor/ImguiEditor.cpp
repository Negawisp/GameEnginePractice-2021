#include "ImguiEditor.h"
#include "../RenderNode.h"

void ImguiEditor::InitImgui() {
	ImguiWrapper::Init();
}

void ImguiEditor::Update(std::vector<RenderNode*>& pRenderNodes) {
	ImguiWrapper::StartFrame();
	ImguiWrapper::Render();
}

void ImguiEditor::AddEntityTree(std::vector<RenderNode*>& pRenderNodes)
{
}
