#pragma once
#include <vector>
#include "ImguiWrapper/ImguiWrapper.h"

class RenderNode;

class ImguiEditor
{
public:
	void InitImgui();
	void Update(std::vector<RenderNode*>& pRenderNodes);

private:
	void AddEntityTree(std::vector<RenderNode*>& pRenderNodes);
};

