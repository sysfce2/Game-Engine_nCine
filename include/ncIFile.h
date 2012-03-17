#ifndef CLASS_NCIFILE
#define CLASS_NCIFILE

#include <cstdio>
#include <stdint.h> // for endianness conversions
#include <cstring> // for strncmp()

/// The interface dealing with file operations
class ncIFile
{
public:
	/// The enumeration for the open mode bitmask
	enum eOpenMode {
		MODE_FD = 1,
		MODE_READ = 2,
		MODE_WRITE = 4,
		MODE_BINARY = 8
	};

protected:
	/// The enumeration of file types
	enum eFileType {
		BASE_TYPE = 0,
		STANDARD_TYPE,
		ASSET_TYPE
	};

	/// File type
	eFileType m_eType;

	/// Maximum number of characters for a file name (path included)
	static const unsigned int s_uMaxFilenameLength = 256;
	/// File name with path
	char m_vFilename[s_uMaxFilenameLength];
	/// Maximum number of characters for a file extension
	static const unsigned int s_uMaxExtensionsLength = 4;
	/// File extension
	char m_vExtension[s_uMaxExtensionsLength];

	/// The path for the application to write files into
	static char m_vDataPath[s_uMaxFilenameLength];

	/// File descriptor for open() and close()
	int m_iFileDescriptor;
	/// File pointer for fopen() and fclose()
	FILE *m_pFilePointer;
	/// Should destructor close the file on exit?
	/*! Useful for ov_open()/ov_fopen() and ov_clear() */
	bool m_bShouldCloseOnExit;

	/// File size in bytes
	long int m_lFileSize;

	/// Private copy constructor (preventing copy at the moment)
	ncIFile(const ncIFile&);
	/// Private assignment operator (preventing copy at the moment)
	ncIFile& operator=(const ncIFile&);

public:
	/// Constructs a base file object
	/*! \param pFilename File name including its path */
	ncIFile(const char *pFilename);
	virtual ~ncIFile() { }

	/// Returns the file type (RTTI)
	eFileType Type() const { return m_eType; }

	/// Tries to open the file
	virtual void Open(unsigned char uMode) = 0;
	/// Closes the file
	virtual void Close() = 0;
	/// Seeks in an opened file
	virtual long int Seek(long int lOffset, int iWhence) const = 0;
	/// Tells the seek position of an opened file
	virtual long int Tell() const = 0;
	/// Read a certain amount of bytes from the file to a buffer
	/*! \return Number of bytes read */
	virtual long int Read(void *pBuffer, int iBytes) const = 0;

	/// Sets the close on exit flag
	inline void SetCloseOnExit(bool bShouldCloseOnExit) { m_bShouldCloseOnExit = bShouldCloseOnExit; }
	// Returns true if the file is already opened
	virtual bool IsOpened() const;

	/// Returns file name with path
	const char* Filename() const { return m_vFilename; }
	/// Returns file extension
	const char* Extension() const { return m_vExtension; }
	// Checks if file extension matches
	bool HasExtension(const char *pExtension) const;

	/// Returns file descriptor
	inline int Fd() const { return m_iFileDescriptor; }
	/// Returns file stream pointer
	inline FILE* Ptr() const { return m_pFilePointer; }
	/// Returns file size in bytes
	inline long int Size() const { return m_lFileSize; }

	/// Reads a little endian 16 bit unsigned integer
	static inline uint16_t Int16FromLE(uint16_t uNumber) { return uNumber; }
	/// Reads a little endian 32 bit unsigned integer
	static inline uint32_t Int32FromLE(uint32_t uNumber) { return uNumber; }
	/// Reads a big endian 16 bit unsigned integer
	static inline uint16_t Int16FromBE(uint16_t uNumber)
	{
		return (uNumber>>8) | (uNumber<<8);
	}
	/// Reads a big endian 32 bit unsigned integer
	static inline uint32_t Int32FromBE(uint32_t uNumber)
	{
		return (uNumber>>24) | ((uNumber<<8) & 0x00FF0000) | ((uNumber>>8) & 0x0000FF00) | (uNumber<<24);
	}

	// Returns the proper file handle according to prepended tags
	static ncIFile* CreateFileHandle(const char *pFilename);
	// Returns the writable directory for data storage
	static char* DataPath();
};

#endif
