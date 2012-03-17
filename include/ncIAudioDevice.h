#ifndef CLASS_NCIAUDIODEVICE
#define CLASS_NCIAUDIODEVICE

class ncIAudioPlayer;

/// It represents the interface to the audio device
class ncIAudioDevice
{
public:
	virtual ~ncIAudioDevice() = 0;
	/// Returns the listener gain value
	virtual float Gain() = 0;
	/// Sets the listener gain value
	virtual void SetGain(float fGain) = 0;
	/// Returns the next available source index available for playing
	virtual int NextAvailableSource() = 0;
	/// Register a new stream player for buffer update
	virtual void RegisterPlayer(ncIAudioPlayer *pPlayer) = 0;
	/// Updates players state (and buffer queue in the case of stream players)
	virtual void UpdatePlayers() = 0;
};

inline ncIAudioDevice::~ncIAudioDevice() { }

#endif

#ifndef CLASS_NCNULLAUDIODEVICE
#define CLASS_NCNULLAUDIODEVICE

/// A fake audio device which doesn't play anything
class ncNullAudioDevice : public ncIAudioDevice
{
public:
	virtual float Gain() { return 1.0f; }
	virtual void SetGain(float fGain) { }
	virtual int NextAvailableSource() { return -1; }
	virtual void RegisterPlayer(ncIAudioPlayer *pPlayer) { }
	virtual void UpdatePlayers() { }
};

#endif
