#pragma once
#include <string>
#include <unordered_map>
#include <bitset>

#include "Input.h"
#include "Ogre.h"

#include "../RenderEngine.h"

class InputHandler
{
public:
	InputHandler(const std::string& strResourceRoot, RenderEngine* renderEngine);
	~InputHandler();

	void Update();

	const std::bitset<eIC_Max>& GetInputState() const;
	bool IsCommandActive(EInputCommand inputCommand) const;

private:
	void LoadConfiguration();

	bool IsKeyDown(int vk_key);
	POINT GetCursorPosition();

	void MapSymbol(std::string strSymbol, int nSymbol);
	void MapInputEvent(int nSymbol, size_t nCommand);
	void MapCommandSymbol(std::string strCommand, size_t nCommand, std::string strDefaultSymbol);
	void Remap();

	RenderEngine* m_pRenderEngine;

	std::string m_strMapFilePath;

	typedef std::unordered_map<std::string, size_t> TCommandMap;
	typedef std::unordered_map<std::string, int> TSymbolMap;
	typedef std::unordered_map<int, size_t> TInputEventMap;
	typedef std::unordered_map<std::string, std::string> TCommandSymbolMap;

	TCommandMap m_commandMap;
	TSymbolMap m_symbolMap;
	TInputEventMap m_inputEventMap;
	TCommandSymbolMap m_commandSymbolMap;

	POINT m_cursorPosition;
	std::bitset<eIC_Max> m_InputState;
};

