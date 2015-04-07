#include "XboxController.h"
#include "EnumKeys.h"
#define BUTTON_DOWN(aBuffer, aKey) ((aBuffer.Gamepad.wButtons) & aKey)

const WORD loc1PercentVibration = 655;

namespace CommonUtilities
{
	XboxController::XboxController(WORD aPlayerNumber)
	{
		myControllerNumber = aPlayerNumber;

		myLeftStickX = 0;
		myLeftStickY = 0;
		myLeftStickMagnitude = 0;
		myNormalizedLeftStickX = 0;
		myNormalizedLeftStickY = 0;
		myNormalizedLeftStickMagnitude = 0;

		myRightStickX = 0;
		myRightStickY = 0;
		myRightStickMagnitude = 0;
		myNormalizedRightStickX = 0;
		myNormalizedRightStickY = 0;
		myNormalizedRightStickMagnitude = 0;

		myLeftTrigger = 0;
		myRightTrigger = 0;

		myTimedVibration = false;
		myTimeLeftOnVibration = 0.0f;

		myLeftMotorVibration = 0;
		myRightMotorVibration = 0;

		myIsConnected = false;
		Vibrate();

	}

	XboxController::~XboxController()
	{
		//turn off vibration when shutting down
		Vibrate();
	}

	void XboxController::Update(float aDeltaTime)
	{

		myLastState = myCurrentState;
		XInputGetState(myControllerNumber, &myCurrentState);
		UpdateLeftStick();
		UpdateRightStick();
		UpdateTriggers();
		UpdateVibration(aDeltaTime);

	}

	void XboxController::Vibrate(float aLowFrequencyMotor, float aHighFrequencyMotor
								 , float anAmountOfTimeInSeconds)
	{
		if (aLowFrequencyMotor < 0.f)
		{
			aLowFrequencyMotor = 0.f;
		}
		if (aLowFrequencyMotor > 1.f)
		{
			aLowFrequencyMotor = 1.f;
		}
		if (aHighFrequencyMotor < 0.f)
		{
			aHighFrequencyMotor = 0.f;
		}
		if (aHighFrequencyMotor > 1.f)
		{
			aHighFrequencyMotor = 1.f;
		}

		myLeftMotorVibration = static_cast<WORD>(aLowFrequencyMotor*65535.0f);
		myRightMotorVibration = static_cast<WORD>(aHighFrequencyMotor*65535.0f);

		myVibration.wLeftMotorSpeed = myLeftMotorVibration;
		myVibration.wRightMotorSpeed = myRightMotorVibration;

		if (anAmountOfTimeInSeconds > 0.0f)
		{
			myTimedVibration = true;
			myTimeLeftOnVibration = anAmountOfTimeInSeconds;
		}
		else
		{
			myTimedVibration = false;
		}
		XInputSetState(myControllerNumber, &myVibration);
	}

	void XboxController::UpdateVibration(float aDeltaTime)
	{
		if (myTimedVibration == true)
		{
			myTimeLeftOnVibration -= aDeltaTime;

			if (myTimeLeftOnVibration <= 0)
			{
				Vibrate();
			}
		}
	}

	void XboxController::UpdateTriggers()
	{
		myLeftTriggerPreviousState = myLeftTriggerCuttentState;
		myRightTriggerPreviousState = myRightTriggerCuttentState;

		myLeftTrigger = myCurrentState.Gamepad.bLeftTrigger;
		myRightTrigger = myCurrentState.Gamepad.bRightTrigger;

		if (myLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			myLeftTrigger -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			myNormalizedLeftTrigger = static_cast<float> (myLeftTrigger) / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
			myLeftTriggerCuttentState = true;
		}
		else
		{
			myLeftTriggerCuttentState = false;
			myNormalizedLeftTrigger = 0;
		}

		if (myRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			myRightTrigger -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
			myNormalizedRightTrigger = static_cast<float> (myRightTrigger) / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
			myRightTriggerCuttentState = true;
		}
		else
		{
			myNormalizedRightTrigger = 0;
			myRightTriggerCuttentState = false;
		}
		
	}

	void XboxController::UpdateLeftStick()
	{
		myLeftStickX = myCurrentState.Gamepad.sThumbLX;
		myLeftStickY = myCurrentState.Gamepad.sThumbLY;

		myLeftStickMagnitude = sqrt(myLeftStickX * myLeftStickX + myLeftStickY * myLeftStickY);

		myNormalizedLeftStickMagnitude = 0.0;

		if (myLeftStickMagnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (myLeftStickMagnitude > 32767)
			{
				myLeftStickMagnitude = 32767;
			}

			myLeftStickMagnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			myNormalizedLeftStickMagnitude = myLeftStickMagnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}
		else
		{
			myLeftStickMagnitude = 0.0;
			myNormalizedLeftStickMagnitude = 0.0;
		}

		if (myNormalizedLeftStickMagnitude > 0)
		{
			myNormalizedLeftStickX = myLeftStickX / 32767;
			myNormalizedLeftStickY = myLeftStickY / 32767;
		}
		else
		{
			myNormalizedLeftStickX = 0;
			myNormalizedLeftStickY = 0;
		}


	}

	void XboxController::UpdateRightStick()
	{
		myRightStickX = myCurrentState.Gamepad.sThumbRX;
		myRightStickY = myCurrentState.Gamepad.sThumbRY;

		myRightStickMagnitude = sqrt(myRightStickX * myRightStickX + myRightStickY * myRightStickY);

		myNormalizedRightStickMagnitude = 0.0;

		if (myRightStickMagnitude > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (myRightStickMagnitude > 32767)
			{
				myRightStickMagnitude = 32767;
			}

			myRightStickMagnitude -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

			myNormalizedRightStickMagnitude = myRightStickMagnitude / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		}
		else
		{
			myRightStickMagnitude = 0.0;
			myNormalizedRightStickMagnitude = 0.0;
		}

		if (myNormalizedRightStickMagnitude > 0)
		{
			myNormalizedRightStickX = myRightStickX / 32767;
			myNormalizedRightStickY = myRightStickY / 32767;
		}
		else
		{
			myNormalizedRightStickX = 0;
			myNormalizedRightStickY = 0;
		}
	}

	void XboxController::UpdateConnection()
	{
		myHRESULT = XInputGetState(myControllerNumber, &testState);

		if (myHRESULT == ERROR_SUCCESS)
		{
			myIsConnected = true;
		}
		else
		{
			myIsConnected = false;
		}
	}

	bool XboxController::IsButtonDown(const WORD aButton) const
	{
		if (BUTTON_DOWN(myCurrentState, aButton)
			&& BUTTON_DOWN(myLastState, aButton))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool XboxController::IsButtonPressed(const WORD aButton) const
	{
		if (BUTTON_DOWN(myCurrentState, aButton)
			&& !BUTTON_DOWN(myLastState, aButton))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool XboxController::IsButtonReleased(const WORD aButton) const
	{
		if (BUTTON_DOWN(myLastState, aButton)
			&& !BUTTON_DOWN(myCurrentState, aButton))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool XboxController::IsTriggerDown(const WORD aButton) const
	{
		if (aButton == eXboxAnalogue::LEFT_TRIGGER)
		{
			if (myLeftTriggerCuttentState == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (aButton == eXboxAnalogue::RIGHT_TRIGGER)
		{
			if (myRightTriggerCuttentState == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool XboxController::IsTriggerPressed(const WORD aButton) const
	{
		if (aButton == eXboxAnalogue::LEFT_TRIGGER)
		{
			if (myLeftTriggerCuttentState == true && myLeftTriggerPreviousState == false)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (aButton == eXboxAnalogue::RIGHT_TRIGGER)
		{
			if (myRightTriggerCuttentState == true && myRightTriggerPreviousState == false)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool XboxController::IsTriggerReleased(const WORD aButton) const
	{
		if (aButton == eXboxAnalogue::LEFT_TRIGGER)
		{
			if (myLeftTriggerCuttentState == false && myLeftTriggerPreviousState == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (aButton == eXboxAnalogue::RIGHT_TRIGGER)
		{
			if (myRightTriggerCuttentState == false && myRightTriggerPreviousState == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool XboxController::IsConnected()
	{
		return myIsConnected;
	}

	float XboxController::GetLeftStickX()
	{
		return myNormalizedLeftStickX;
	}

	float XboxController::GetLeftStickY()
	{
		return myNormalizedLeftStickY;
	}

	XboxController::XboxController()
	{

	}

	float XboxController::GetRightStickX()
	{
		return myNormalizedRightStickX;
	}

	float  XboxController::GetRightStickY()
	{
		return myNormalizedRightStickY;
	}

	float XboxController::GetRightTrigger()
	{
		return myNormalizedRightTrigger;
	}

	float XboxController::GetLeftTrigger()
	{
		return myNormalizedLeftTrigger;
	}
}