#pragma once

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <tchar.h>

namespace ImguiWrapper {
	void CleanupRenderTarget();
	void CreateRenderTarget();
	void CleanupDeviceD3D();
	bool CreateDeviceD3D(HWND hWnd);
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Init();

	void StartFrame();
	void Render();
};