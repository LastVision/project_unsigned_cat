#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include <dinput.h>
#include "EnumKeys.h"
#include "Vector.h"
#include "DL_Debug.h"

//Uncomment to support controllers
#define SUPPORT_XBOX_CONTROLLER 

#ifdef SUPPORT_XBOX_CONTROLLER
#include "XboxController.h"
#endif

namespace CommonUtilities
{
	struct MousePosition
	{
		float myX;
		float myY;
		float myScrollWheel = 0.0f;
	};
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void Update(float aDeltaTime);

		bool Init(HINSTANCE aInstanceHandler);

		bool GetKeyDown(const unsigned char aKey) const;
		bool GetKeyPressed(const unsigned char aKey) const;
		bool GetKeyRelease(const unsigned char aKey) const;

		bool GetIsAnyKeyDown() const;

		bool GetMouseButtonDown(const eMouseButtons aMouseButton) const;
		bool GetMouseButtonPressed(const eMouseButtons aMouseButton) const;
		bool GetMouseButtonReleased(const eMouseButtons aMouseButton) const;

		MousePosition GetRelativeMousePosition();
		MousePosition GetAbsoluteMousePosition();

		void SetMousePosition(const Vector2<float>& aMousePosition);

#ifdef SUPPORT_XBOX_CONTROLLER

		XboxController& GetMyXboxController(WORD aPlayerNumber);

#endif
		LONG GetScrollWheelValue()const;
		const tagPOINT& GetMyMousePositionOnScreen() const;

	private:
		HINSTANCE myInstance;
		HRESULT myHRESULT;
		LPDIRECTINPUT8 myLPDirectInput;
		LPDIRECTINPUTDEVICE8 myLPDirectInputDeviceKeyboard;
		LPDIRECTINPUTDEVICE8 myLPDirectInputDeviceMouse;

		tagPOINT myMousePositionOnScreen;

		DIMOUSESTATE2 myMouseCurrentState;
		DIMOUSESTATE2 myMouseLastState;
		MousePosition myMousePosition;
		char myKeyboardCurrentState[256];
		char myKeyboardLastState[256];

		bool CreateKeyboard();
		bool CreateMouse();

		void TerminateDirectInput();
		void ProcessKeyboardInput();
		void ProcessMouseInput();


#ifdef SUPPORT_XBOX_CONTROLLER

		void ProcessXboxControllers(float aDeltaTime);

		XboxController *myXboxControllers;
		float myTimeInSecondsSinceLastConnectionUpdate;
		void CheckXboxControllers();
		bool CreateXboxControllers();

#endif
	};

}

namespace CU = CommonUtilities;