#ifndef CLASS_MYEVENTHANDLER
#define CLASS_MYEVENTHANDLER

#include "IAppEventHandler.h"
#include "IInputEventHandler.h"

namespace ncine{

class SceneNode;
class Texture;
class Sprite;

}

namespace nc = ncine;

/// My nCine event handler
class MyEventHandler
	: public nc::IAppEventHandler,
	  public nc::IInputEventHandler
{
  public:
	virtual void onInit();
	virtual void onFrameStart();
	virtual void onFrameEnd() { }
	virtual void onShutdown();

#ifdef __ANDROID__
	virtual void onTouchDown(const nc::TouchEvent &event);
	virtual void onTouchUp(const nc::TouchEvent &event);
#else
	virtual void onKeyReleased(const nc::KeyboardEvent &event);
	virtual void onMouseButtonPressed(const nc::MouseEvent &event);
	virtual void onMouseButtonReleased(const nc::MouseEvent &event);
#endif

  private:
	static const int NumTextures = 4;
	static const int NumRowSprites = 8;
	static const int NumColSprites = 8;

	bool pause_;
	float angle_;
	nc::SceneNode *dummy_;
	nc::Texture *megaTexture_;
	nc::Sprite **sprites_;
};

#endif