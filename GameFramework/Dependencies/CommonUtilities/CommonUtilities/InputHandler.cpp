#include "InputHandler.h"
#define KEY_DOWN(aBuffer, aKey) ((aBuffer)[aKey] & 0x80)

#ifdef SUPPORT_XBOX_CONTROLLER
const float locUpdateCheckActiveControllers = 2.0f; //Amount of time in seconds
const WORD locNumberOfControllersToCheck = 4; // 0-4 controllers
const WORD locNumberOfButtonsOnController = 14;
#endif

namespace CommonUtilities
{

	InputHandler::InputHandler()
	{

	}

	InputHandler::~InputHandler()
	{

#ifdef SUPPORT_XBOX_CONTROLLER
		delete[] myXboxControllers;
		myXboxControllers = nullptr;
#endif
		TerminateDirectInput();
	}

	bool InputHandler::Init(HINSTANCE aInstanceHandler)
	{
		myInstance = aInstanceHandler;

		//Create direct input object.
		myHRESULT = DirectInput8Create(myInstance, DIRECTINPUT_VERSION,
									   IID_IDirectInput8, (void**) &myLPDirectInput, NULL);

		if FAILED(myHRESULT)
		{
			TerminateDirectInput();
			DL_ASSERT("Couldn't create DirectInput Object.");
		}

		if (CreateMouse() == false)
		{
			TerminateDirectInput();
			return false;
		}

		if (CreateKeyboard() == false)
		{
			TerminateDirectInput();
			return false;
		}

#ifdef SUPPORT_XBOX_CONTROLLER
		myTimeInSecondsSinceLastConnectionUpdate = locUpdateCheckActiveControllers;
		if (CreateXboxControllers() == false)
		{
			TerminateDirectInput();
			return false;
		}
#endif
		return true;
	}

	void InputHandler::TerminateDirectInput()
	{
		if (myLPDirectInput)
		{
			if (myLPDirectInputDeviceKeyboard)
			{
				myLPDirectInputDeviceKeyboard->Unacquire();
				myLPDirectInputDeviceKeyboard->Release();
				myLPDirectInputDeviceKeyboard = nullptr;
			}
			if (myLPDirectInputDeviceMouse)
			{
				myLPDirectInputDeviceMouse->Unacquire();
				myLPDirectInputDeviceMouse->Release();
				myLPDirectInputDeviceMouse = nullptr;
			}
			myLPDirectInput->Release();
			myLPDirectInput = nullptr;
		}
	}

	void InputHandler::SetMousePosition(const Vector2<float>& aMousePosition)
	{
		tagPOINT aNewPosition;

		aNewPosition.x = static_cast<LONG>(aMousePosition.myX);
		aNewPosition.y = static_cast<LONG>(aMousePosition.myY);

		ClientToScreen(GetActiveWindow(), &aNewPosition);
		SetCursorPos(static_cast<int>(aNewPosition.x), static_cast<int>(aNewPosition.y));

	}


	void InputHandler::ProcessKeyboardInput()
	{
		//take data from current and put it in last state
		for (int unsigned i = 0; i < 256; i++)
		{
			myKeyboardLastState[i] = myKeyboardCurrentState[i];
		}
		myHRESULT = myLPDirectInputDeviceKeyboard->Acquire();
		myHRESULT = myLPDirectInputDeviceKeyboard->GetDeviceState(sizeof(myKeyboardCurrentState),
																  (LPVOID) &myKeyboardCurrentState);

		if FAILED(myHRESULT)
		{
			if (myHRESULT == DIERR_INPUTLOST)
			{
				myHRESULT = myLPDirectInputDeviceKeyboard->Acquire();
			}
			if (myHRESULT == DIERR_INPUTLOST)
			{
				assert("Failed to aquire keyboard device");
			}
		}
	}

	void InputHandler::Update(float aDeltaTimeInSeconds)
	{
		ProcessKeyboardInput();
		ProcessMouseInput();

#ifdef SUPPORT_XBOX_CONTROLLER //---------------------------

		ProcessXboxControllers(aDeltaTimeInSeconds);

#else 
		++aDeltaTimeInSeconds;

#endif //---------------------------------------------------

#ifdef SUPPORT_INPUT_WRAPPER_EVENT_LOGGING
		UpdateEventLog();
#endif
	}

	bool InputHandler::GetKeyDown(const unsigned char aKey) const
	{
		if (KEY_DOWN(myKeyboardCurrentState, aKey)
			&& KEY_DOWN(myKeyboardLastState, aKey))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputHandler::GetKeyPressed(const unsigned char aKey) const
	{
		if (KEY_DOWN(myKeyboardCurrentState, aKey)
			&& !KEY_DOWN(myKeyboardLastState, aKey))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputHandler::GetKeyRelease(const unsigned char aKey) const
	{
		if (KEY_DOWN(myKeyboardLastState, aKey)
			&& !KEY_DOWN(myKeyboardCurrentState, aKey))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputHandler::GetIsAnyKeyDown() const
	{
		for (unsigned char i = 0; i < UCHAR_MAX; ++i)
		{
			if (GetKeyDown(i) == true)
			{
				return true;
			}
		}
		return false;
	}

	bool InputHandler::CreateKeyboard()
	{
		//Retrieve Pointer to an IDirectInputDevice8 interface
		myHRESULT = myLPDirectInput->CreateDevice(
			GUID_SysKeyboard, &myLPDirectInputDeviceKeyboard, NULL);

		if FAILED(myHRESULT)
		{
			TerminateDirectInput();
			DL_ASSERT("Couldn't retrieve pointer to input device interface.");
		}

		//Set dataformat of device.
		myHRESULT = myLPDirectInputDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);

		if FAILED(myHRESULT)
		{
			TerminateDirectInput();
			DL_ASSERT("Couldn't set dataformat of device.");
		}

		//Set cooperative level.
		myHRESULT = myLPDirectInputDeviceKeyboard->SetCooperativeLevel(GetActiveWindow(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


		if FAILED(myHRESULT)
		{
			TerminateDirectInput();
			DL_ASSERT("Couldn't set cooperative level of device.");
		}

		//Get Access to the input device
		myHRESULT = myLPDirectInputDeviceKeyboard->Acquire();

		if FAILED(myHRESULT)
		{
			TerminateDirectInput();
			DL_ASSERT("Couldn't acquire device.");
		}
		return true;
	}

	bool InputHandler::CreateMouse()
	{
		myHRESULT = myLPDirectInput->CreateDevice(GUID_SysMouse,
												  &myLPDirectInputDeviceMouse, NULL);

		if FAILED(myHRESULT)
		{
			DL_ASSERT("Couldn't create mouse device.");
			return false;
		}

		myHRESULT = myLPDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse2);

		if FAILED(myHRESULT)
		{
			DL_ASSERT("Couldn't set data format for mouse");
			return false;
		}

		myHRESULT = myLPDirectInputDeviceMouse->SetCooperativeLevel(GetActiveWindow()
																	, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		if FAILED(myHRESULT)
		{
			DL_ASSERT("Couldn't set cooperative level for mouse");
			return false;
		}
		return true;
	}

	void InputHandler::ProcessMouseInput()
	{
		myMouseLastState = myMouseCurrentState;

		myHRESULT = myLPDirectInputDeviceMouse->Acquire();

		if FAILED(myHRESULT)
		{
			return;
		}

		ZeroMemory(&myMouseCurrentState, sizeof(myMouseCurrentState));
		myHRESULT = myLPDirectInputDeviceMouse->GetDeviceState
			(sizeof(DIMOUSESTATE2), &myMouseCurrentState);

		if FAILED(myHRESULT)
		{
			DL_ASSERT("Couldn't get mouse current state level");
		}

		tagPOINT cursorPoint;
		GetCursorPos(&cursorPoint);
		ScreenToClient(GetActiveWindow(), &cursorPoint);
		myMousePositionOnScreen = cursorPoint;
	}

	bool InputHandler::GetMouseButtonDown(
		const eMouseButtons aMouseButton) const
	{

		if (KEY_DOWN(myMouseCurrentState.rgbButtons, static_cast<int>(aMouseButton))
			&& (KEY_DOWN(myMouseLastState.rgbButtons, static_cast<int>(aMouseButton))))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputHandler::GetMouseButtonPressed(const eMouseButtons aMouseButton) const
	{
		if (KEY_DOWN(myMouseCurrentState.rgbButtons, static_cast<int> (aMouseButton))
			&& (!KEY_DOWN(myMouseLastState.rgbButtons, static_cast<int> (aMouseButton))))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputHandler::GetMouseButtonReleased(const eMouseButtons aMouseButton) const
	{
		if (!KEY_DOWN(myMouseCurrentState.rgbButtons, static_cast<int> (aMouseButton))
			&& (KEY_DOWN(myMouseLastState.rgbButtons, static_cast<int> (aMouseButton))))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	const tagPOINT& InputHandler::GetMyMousePositionOnScreen() const
	{
		return myMousePositionOnScreen;
	}

	LONG InputHandler::GetScrollWheelValue()const
	{
		return myMouseCurrentState.lZ;
	}

	MousePosition InputHandler::GetRelativeMousePosition()
	{
		myMousePosition.myX = static_cast<float>(myMouseCurrentState.lX);
		myMousePosition.myY = static_cast<float>(myMouseCurrentState.lY);
		myMousePosition.myScrollWheel = static_cast<float>(myMouseCurrentState.lZ);

		return myMousePosition;
	}

	MousePosition InputHandler::GetAbsoluteMousePosition()
	{
		tagPOINT getMouseXAndY;
		GetCursorPos(&getMouseXAndY);
		ScreenToClient(GetActiveWindow(), &getMouseXAndY);

		myMousePosition.myX = static_cast<float>(getMouseXAndY.x);
		myMousePosition.myY = static_cast<float>(getMouseXAndY.y);
		myMousePosition.myScrollWheel += static_cast<float>(myMouseCurrentState.lZ);

		return myMousePosition;
	}

#ifdef SUPPORT_XBOX_CONTROLLER

	void InputHandler::ProcessXboxControllers(float aDeltaTime)
	{
		for (WORD i = 0; i < locNumberOfControllersToCheck; i++)
		{
			myXboxControllers[i].Update(aDeltaTime);
		}

		myTimeInSecondsSinceLastConnectionUpdate += aDeltaTime;
		if (myTimeInSecondsSinceLastConnectionUpdate > locUpdateCheckActiveControllers)
		{
			for (WORD i = 0; i < locNumberOfControllersToCheck; i++)
			{
				myXboxControllers[i].UpdateConnection();
			}
			myTimeInSecondsSinceLastConnectionUpdate = 0;
		}
	}

	void InputHandler::CheckXboxControllers()
	{
		for (WORD i = 0; i < locNumberOfControllersToCheck; i++)
		{
			myXboxControllers[i].UpdateConnection();
		}
	}

	XboxController& InputHandler::GetMyXboxController(WORD aPlayerNumber)
	{
		assert(aPlayerNumber > 0 && aPlayerNumber <= locNumberOfControllersToCheck
			   && "No controller with player number.");
		return myXboxControllers[aPlayerNumber - 1];
	}

	bool InputHandler::CreateXboxControllers()
	{
		assert(locUpdateCheckActiveControllers > 0 && "Can't have an update time with a negative time.");
		assert(locNumberOfControllersToCheck >= 0 && locNumberOfControllersToCheck <= 4 &&
			   "Can only check 0-4 controllers.");
		myXboxControllers = new XboxController[locNumberOfControllersToCheck];
		for (WORD i = 0; i < locNumberOfControllersToCheck; i++)
		{
			myXboxControllers[i] = XboxController(i);
		}
		return true;
	}

#endif
}
