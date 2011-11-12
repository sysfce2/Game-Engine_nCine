#ifndef CLASS_NCDISPLAYMODE
#define CLASS_NCDISPLAYMODE

#include "ncPoint.h"

/// Display properties
class ncDisplayMode
{
private:
	/// Red component bits
	int m_iRedBits;
	/// Green component bits
	int m_iGreenBits;
	/// Blue component bits
	int m_iBlueBits;
	/// Alpha component bits
	int m_iAlphaBits;
	/// Frame buffer bits
	int m_iBufferBits;
	/// Double buffering flag
	bool m_bIsDoubleBuffered;
	/// Depth buffer size in bit
	int m_iDepthBits;
	/// Stencil buffer size in bit
	int m_iStencilBits;
	/// VSync flag
	bool m_bIsVSynced;
public:
	// Constructor with no parameters
	ncDisplayMode()
		: m_iRedBits(-1), m_iGreenBits(-1), m_iBlueBits(-1), m_iAlphaBits(-1), m_iBufferBits(-1),
		  m_bIsDoubleBuffered(true), m_bIsVSynced(false), m_iDepthBits(-1), m_iStencilBits(-1) { }
	ncDisplayMode(int iRedBits, int iGreenBits, int iBlueBits)
		: m_iRedBits(iRedBits), m_iGreenBits(iGreenBits), m_iBlueBits(iBlueBits),
		  m_iAlphaBits(-1), m_iBufferBits(-1), m_bIsDoubleBuffered(true), m_bIsVSynced(false),
		  m_iDepthBits(-1), m_iStencilBits(-1) { }
	ncDisplayMode(int iRedBits, int iGreenBits, int iBlueBits, int iAlphaBits)
		: m_iRedBits(iRedBits), m_iGreenBits(iGreenBits), m_iBlueBits(iBlueBits),
		  m_iAlphaBits(iAlphaBits), m_iBufferBits(-1), m_bIsDoubleBuffered(true), m_bIsVSynced(false),
		  m_iDepthBits(-1), m_iStencilBits(-1) { }
	ncDisplayMode(bool bDoubleBuffered, bool bVSynced, int iDepthBits, int iStencilBits)
		: m_iRedBits(-1), m_iGreenBits(-1), m_iBlueBits(-1), m_iAlphaBits(-1), m_iBufferBits(-1),
		  m_bIsDoubleBuffered(bDoubleBuffered), m_bIsVSynced(bVSynced),
		  m_iDepthBits(iDepthBits), m_iStencilBits(iStencilBits) { }
	ncDisplayMode(int iRedBits, int iGreenBits, int iBlueBits, int iAlphaBits, int iBufferBits,
				  bool bDoubleBuffered, bool bVSynced, int iDepthBits, int iStencilBits)
		: m_iRedBits(iRedBits), m_iGreenBits(iGreenBits), m_iBlueBits(iBlueBits),
		  m_iAlphaBits(iAlphaBits), m_iBufferBits(iBufferBits),
		  m_bIsDoubleBuffered(bDoubleBuffered), m_bIsVSynced(bVSynced),
		  m_iDepthBits(iDepthBits), m_iStencilBits(iStencilBits) { }
	// Destructor
	~ncDisplayMode() { }

	// Getters
	inline int RedBits() const { return m_iRedBits; }
	inline int GreenBits() const { return m_iGreenBits; }
	inline int BlueBits() const { return m_iBlueBits; }
	inline int AlphaBits() const { return m_iAlphaBits; }
	inline int BufferBits() const { return m_iBufferBits; }
	inline bool isDoubleBuffered() const { return m_bIsDoubleBuffered; }
	inline bool isVSynced() const { return m_bIsVSynced; }
	inline int DepthBits() const { return m_iDepthBits; }
	inline int StencilBits() const { return m_iStencilBits; }
};

#endif