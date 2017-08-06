#ifndef CLASS_NCINE_ANDROIDINPUTMANAGER
#define CLASS_NCINE_ANDROIDINPUTMANAGER

#include <android/keycodes.h>
#include "IInputManager.h"

struct AInputEvent;
struct ASensorManager;
struct ASensor;
struct ASensorEventQueue;

namespace ncine {

class AndroidApplication;
class Timer;

/// Utility functions to convert between engine key enumerations and Android ones
class AndroidKeys
{
  public:
	static KeySym keySymValueToEnum(int keysym);
	static KeyMod keyModValueToEnum(int keymod);
};

/// Simulated information about Android keyboard state
class AndroidKeyboardState : public KeyboardState
{
  public:
	AndroidKeyboardState()
	{
		for (unsigned int i = 0; i < KEYSYM_COUNT; i++) { keys_[i] = 0; }
	}

	inline bool isKeyDown(KeySym key) const
	{
		if (key == KEY_UNKNOWN) { return false; }
		else { return keys_[key] != 0; }
	}

  private:
	unsigned char keys_[KEYSYM_COUNT];

	friend class AndroidInputManager;
};

/// Information about Android mouse state
class AndroidMouseState : public MouseState
{
  public:
	AndroidMouseState() : buttonState_(0) { }

	bool isLeftButtonDown() const;
	bool isMiddleButtonDown() const;
	bool isRightButtonDown() const;
	bool isFourthButtonDown() const;
	bool isFifthButtonDown() const;

  private:
	int buttonState_;

	friend class AndroidInputManager;
};

/// Information about an Android mouse event
class AndroidMouseEvent : public MouseEvent
{
  public:
	AndroidMouseEvent() : button_(0) { }

	bool isLeftButton() const;
	bool isMiddleButton() const;
	bool isRightButton() const;
	bool isFourthButton() const;
	bool isFifthButton() const;

  private:
	int button_;

	friend class AndroidInputManager;
};

/// Information about Android joystick state
class AndroidJoystickState : JoystickState
{
  public:
	AndroidJoystickState();

	bool isButtonPressed(int buttonId) const;
	short int axisValue(int axisId) const;
	float axisNormValue(int axisId) const;

  private:
	static const unsigned int MaxNameLength = 256;
	/// All AKEYCODE_BUTTON_* plus AKEYCODE_BACK
	static const int MaxButtons = AKEYCODE_ESCAPE - AKEYCODE_BUTTON_A + 1;
	static const int MaxAxes = 10;
	static const int NumAxesToMap = 8;
	static const int AxesToMap[NumAxesToMap];

	int deviceId_;
	char guid_[33];
	char name_[MaxNameLength];

	int numButtons_;
	int numAxes_;
	bool hasDPad_;
	short int buttonsMapping_[MaxButtons];
	short int axesMapping_[MaxAxes];
	bool buttons_[MaxButtons];
	float axesValues_[MaxAxes];

	friend class AndroidInputManager;
};

/// The class for parsing and dispatching Android input events
class AndroidInputManager : public IInputManager
{
  public:
	explicit AndroidInputManager(struct android_app *state);

	/// Enables the accelerometer sensor
	static void enableAccelerometerSensor();
	/// Disables the accelerometer sensor
	static void disableAccelerometerSensor();

	/// Allows the application to make use of the accelerometer
	static void enableAccelerometer(bool enabled);

	inline const MouseState &mouseState() { return mouseState_; }
	inline const KeyboardState &keyboardState() const { return keyboardState_; }

	/// Parses an Android sensor event related to the accelerometer
	static void parseAccelerometerEvent();
	/// Parses an Android input event
	static bool parseEvent(const AInputEvent *event);

	bool isJoyPresent(int joyId) const;
	const char *joyName(int joyId) const;
	const char *joyGuid(int joyId) const;
	int joyNumButtons(int joyId) const;
	int joyNumAxes(int joyId) const;
	const JoystickState &joystickState(int joyId) const;

	void setMouseCursorMode(MouseCursorMode mode) { mouseCursorMode_ = mode; }

  private:
	static const int MaxNumJoysticks = 4;

	static ASensorManager *sensorManager_;
	static const ASensor *accelerometerSensor_;
	static ASensorEventQueue *sensorEventQueue_;
	static bool accelerometerEnabled_;

	static AccelerometerEvent accelerometerEvent_;
	static TouchEvent touchEvent_;
	static AndroidKeyboardState keyboardState_;
	static KeyboardEvent keyboardEvent_;
	static AndroidMouseState mouseState_;
	static AndroidMouseEvent mouseEvent_;
	static ScrollEvent scrollEvent_;
	/// Back and forward key events triggered by the mouse are simulated as right and middle button
	static int simulatedMouseButtonState_;

	static AndroidJoystickState nullJoystickState_;
	static AndroidJoystickState joystickStates_[MaxNumJoysticks];
	static JoyButtonEvent joyButtonEvent_;
	static JoyAxisEvent joyAxisEvent_;
	static JoyConnectionEvent joyConnectionEvent_;
	/// Update rate of `updateJoystickConnections()` in seconds
	static const float JoyCheckRate;
	static Timer joyCheckTimer_;

	/// Processes a gamepad event
	static bool processGamepadEvent(const AInputEvent *event);
	/// Processes a keyboard event
	static bool processKeyboardEvent(const AInputEvent *event);
	/// Processes a touch event
	static bool processTouchEvent(const AInputEvent *event);
	/// Processes a mouse event
	static bool processMouseEvent(const AInputEvent *event);
	/// Processes a keycode event generated by the mouse, like the back key on right mouse click
	static bool processMouseKeyEvent(const AInputEvent *event);

	/// Initializes the accelerometer sensor
	static void initAccelerometerSensor(struct android_app *state);

	/// Updates joystick states after connections and disconnections
	static void updateJoystickConnections();
	/// Checks if a previously connected joystick has been disconnected
	static void checkDisconnectedJoysticks();
	/// Checks if a new joystick has been connected
	static void checkConnectedJoysticks();

	static int findJoyId(int deviceId);
	static bool isDeviceConnected(int deviceId);
	static void deviceInfo(int deviceId, int joyId);

	/// To update joystick connections in `AndroidApplication::androidMain()`
	friend class AndroidApplication;
};

}

#endif
