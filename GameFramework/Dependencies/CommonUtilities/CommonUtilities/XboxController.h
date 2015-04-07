#pragma once
#pragma comment (lib, "Xinput9_1_0.lib")
#include <Windows.h>
#include <Xinput.h>
#include <assert.h>
#include <cmath>

namespace CommonUtilities
{
	class XboxController
	{
	public:

		XboxController(WORD aPlayerNumber);
		XboxController();
		~XboxController();
		void Update(float aDeltaTime);
		void UpdateConnection();
		bool IsConnected();

		//----------------------------------------
		//Frequency motors range from 0.0f - 1.0f.
		//Vibration until next vibrate() call is default value on time variable.
		void Vibrate(float aLowFrequencyMotor = 0.0f, float aHighFrequencyMotor = 0.0f
					 , float anAmountOfTimeInSeconds = 0.0f);

		float GetLeftStickX();
		float GetLeftStickY();
		float GetRightStickX();
		float GetRightStickY();
		float GetRightTrigger();
		float GetLeftTrigger();

		bool IsButtonDown(const WORD aButton) const;
		bool IsButtonPressed(const WORD aButton) const;
		bool IsButtonReleased(const WORD aButton) const;

		bool IsTriggerDown(const WORD aTrigger) const;
		bool IsTriggerPressed(const WORD aTrigger) const;
		bool IsTriggerReleased(const WORD aTrigger) const;

	private:

		WORD myControllerNumber;
		WORD myLeftMotorVibration;
		WORD myRightMotorVibration;

		float myLeftStickX;
		float myLeftStickY;
		float myLeftStickMagnitude;
		float myNormalizedLeftStickX;
		float myNormalizedLeftStickY;
		float myNormalizedLeftStickMagnitude;

		float myRightStickX;
		float myRightStickY;
		float myRightStickMagnitude;
		float myNormalizedRightStickX;
		float myNormalizedRightStickY;
		float myNormalizedRightStickMagnitude;

		float myTimeLeftOnVibration;
		bool myTimedVibration;
		bool myIsConnected;

		BYTE myLeftTrigger;
		BYTE myRightTrigger;
		float myNormalizedLeftTrigger;
		float myNormalizedRightTrigger;
		bool myLeftTriggerCuttentState;
		bool myLeftTriggerPreviousState;
		bool myRightTriggerCuttentState;
		bool myRightTriggerPreviousState;


		XINPUT_VIBRATION myVibration;

		HRESULT myHRESULT;

		XINPUT_STATE myCurrentState;
		XINPUT_STATE myLastState;
		XINPUT_STATE testState;

		void UpdateRightStick();
		void UpdateLeftStick();
		void UpdateTriggers();
		void UpdateVibration(float aDeltaTime);

	};
}

namespace CU = CommonUtilities;