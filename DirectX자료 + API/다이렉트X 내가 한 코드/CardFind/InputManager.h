#pragma once

#define INPUTMGR InputManager::GetInstance()
#define KEYBOARDMAX 255

class InputManager
{
	SINGLETONE(InputManager);

	BYTE			m_KeyboardState[KEYBOARDMAX];

public:
	void SetUp(void);
	void Update(void);
	bool GetKeyDown(BYTE key);
	bool GetKeyUp(BYTE key);
	bool GetKey(BYTE key);

};

