#pragma once
#include <vector>
#include <memory>
#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>

namespace ABGate
{
	//byte type
	typedef unsigned char Byte;
	//byte array
	typedef std::vector<Byte> ByteArray;

	//memory structure in ARGB(alpha, red, green, blue: 8 bits) format
	//which represents color matrix and can be used to copy data 
	//into non Aspose and non GDI+ graphic libraries
	struct MemBmpARGB
	{
		//bitmap width in ARGB pixels
		int Width = 0;
		//bitmap height in ARGB pixels
		int Height = 0;
		//bitmap array in ARGB pixels
		//size is Width * Height * 4
		//format:
		//row0(width)
		//...
		//row_height-1(width)
		ByteArray Data;

		//ARGB memory bitmap constructor
		MemBmpARGB(int _width, int _height)
		{
			Width = _width;
			Height = _height;
			Data.resize(_width * _height * 4);//PARGB = 8888 4 bytes
		}
	};
}