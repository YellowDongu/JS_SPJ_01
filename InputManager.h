#pragma once

enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	Space = VK_SPACE,

	Q = 'Q',
	W = 'W',
	E = 'E',
	R = 'R',
	T = 'T',
	Y = 'Y',
	U = 'U',
	I = 'I',
	O = 'O',
	P = 'P',

	A = 'A',
	S = 'S',
	D = 'D',
	F = 'F',
	G = 'G',
	H = 'H',
	J = 'J',
	K = 'K',
	L = 'L',

	Z = 'Z',
	X = 'X',
	C = 'C',
	V = 'V',
	B = 'B',
	N = 'N',
	M = 'M',
	Shift = VK_SHIFT,
	Ctrl = VK_CONTROL,
	Menu = VK_MENU,
	Escape = VK_ESCAPE,
	Caps = VK_CAPITAL,

	Delete = VK_DELETE,
	Insert = VK_INSERT,
	Home = VK_HOME,
	End = VK_END,
	Pgup = VK_PRIOR,
	Pgdn = VK_NEXT,

	F1 = VK_F1,
	F2 = VK_F2,
	F3 = VK_F3,
	F4 = VK_F4,
	F5 = VK_F5,
	F6 = VK_F6,
	F7 = VK_F7,
	F8 = VK_F8,
	F9 = VK_F9,
	F10 = VK_F10,
	F11 = VK_F11,
	F12 = VK_F12,

	NUMPAD0 = VK_NUMPAD0,
	NUMPAD1 = VK_NUMPAD1,
	NUMPAD2 = VK_NUMPAD2,
	NUMPAD3 = VK_NUMPAD3,
	NUMPAD4 = VK_NUMPAD4,
	NUMPAD5 = VK_NUMPAD5,
	NUMPAD6 = VK_NUMPAD6,
	NUMPAD7 = VK_NUMPAD7,
	NUMPAD8 = VK_NUMPAD8,
	NUMPAD9 = VK_NUMPAD9,

	N1 = '1',
	N2 = '2',
	N3 = '3',
	N4 = '4',
	N5 = '5',
	N6 = '6',
	N7 = '7',
	N8 = '8',
	N9 = '9',
	N0 = '0'
};

enum class KeyState
{
	None,
	Down,
	Press,
	Up,

	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<INT32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<INT32>(KeyState::END)
};


/*
매 프레임마다 키 상태를 확인하는 것은 메시지 기반 처리보다 CPU에 부하를 줌
그러나 현대적인 게임 환경에서 이 정도의 오버헤드는 문제 없을정도
게임의 입력 반응성을 높이는 데 더 효과적인 방법이라 인풋매니저를 만들 이유가 있음
*/


class InputManager
{
	DECLARE_SINGLETON(InputManager)

public:
	void Init(HWND _hwnd);
	void update();

	bool getButton(KeyType key) { return getState(key) == KeyState::Press; }
	bool getButtonDown(KeyType key) { return getState(key) == KeyState::Down; }
	bool getButtonUp(KeyType key) { return getState(key) == KeyState::Up; }
	POINT getMousePos() { return mousePos; }
	bool wheelUp() { return mouseWheel == 1; }
	bool wheelDown() { return mouseWheel == -1; }

private:
	KeyState getState(KeyType key) { return states[static_cast<UINT8>(key)]; }

	HWND hwnd = 0;
	std::vector<KeyState> states = {};
	POINT mousePos = { (0,0) };
	int mouseWheel = 0;
};

#define Input GET_SINGLETON(InputManager)




class PlayerInput
{
	DECLARE_SINGLETON(PlayerInput)

public:
	int horizontal() { return horizontalInput; }
	int vertical() { return verticalInput; }

	void Update();
	void changeKeyVMinus(KeyType key) { vMinus = key; }
	void changeKeyvPlus(KeyType key) { vPlus = key; }
	void changeKeyhMinus(KeyType key) { hMinus = key; }
	void changeKeyhPlus(KeyType key) { hPlus = key; }

private:
	int horizontalInput = 0, verticalInput = 0;
	KeyType vMinus = KeyType::S;
	KeyType vPlus = KeyType::W;
	KeyType hMinus = KeyType::A;
	KeyType hPlus = KeyType::D;

	void checkInput();
};

#define vhInput GET_SINGLETON(PlayerInput)
