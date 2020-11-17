#pragma once

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include <windows.h>
#include <iostream>
#include <fstream>
#include <exception>
#include "abtypes.h"

#include <system/io/memory_stream.h>
#include <system/array.h>
#include <shlwapi.h>
//add link to Shlwapi
#pragma comment (lib,"Shlwapi.lib")

namespace ABGate
{
	//function saves byte array to file
	//is used for debugging
	//arr - is byte array
	//fileName - is a name of file on disk
	void SaveByteArrayToFile(ByteArray &arr, const wchar_t* fileName);
	//function loads byte array from file
	//is used for debugging
	//fileName - is a name of file on disk
	//returns byte array
	ByteArray LoadByteArrayFromFile(const wchar_t* fileName);

	//function creates MemoryStream from memory buffer
	//buffer - is memory buffer
	//size - is a buffer size
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> MemoryStreamFromBuffer(void* buffer, int size);
	//function converts MemoryStream to std::string as data array
	//memoryStream - is a memory stream
	//returns data array as std::string
	std::string MemoryStreamToString(System::SharedPtr<System::IO::MemoryStream> memoryStream);
	//function coverts data array in std::string to memory stream
	//str - is data array as std::string
	//returns memory steam
	System::SharedPtr<System::IO::MemoryStream> StringToToMemoryStream(std::string &str);

	//function coverts memory stream to byte array
	//memoryStream - is a memory steam
	//returns byte array
	ByteArray MemoryStreamToByteArray(System::SharedPtr<System::IO::MemoryStream> memoryStream);
	//function coverts byte array to memory stream
	//arr - is byte array
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> ByteArrayToMemoryStream(ByteArray &arr);

	//function converts byte array to COM IStream implementation
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//arr - is byte array
	//returns COM IStream implementation
	IStream* ByteArrayToIStream(ByteArray &arr);
	//function coverts COM IStream implementation to byte array
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//istr - is COM IStream implementation
	//returns byte array
	ByteArray IStreamToByteArray(IStream *istr);

	//function coverts memory stream to COM IStream implementation
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//memoryStream - is a memory steam
	//returns COM IStream implementation
	IStream* MemoryStreamToIStream(System::SharedPtr<System::IO::MemoryStream> memoryStream);
	//function coverts COM IStream implementation to memory stream
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//istr - is COM IStream implementation
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> IStreamToMemoryStream(IStream *istr);
}
