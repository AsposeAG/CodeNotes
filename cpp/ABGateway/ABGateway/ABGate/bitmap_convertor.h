#pragma once
#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include <windows.h>
#include <gdiplus.h>
#include <exception>
#include "abtypes.h"
#include <drawing/bitmap.h>
#include "memstr_convertor.h"
//adds library to the project, can be added in linker
#pragma comment (lib,"Gdiplus.lib")

namespace ABGate
{
	//function searches image encoders/decoder for GDI+
	//imageFormat - is image format (bmp, png, jpg...)
	//isEncoder - is is we are searching Encoders(true) or decoders(false)
	//returns encoder/decoders ID
	CLSID FindCodecByFormat(const GUID &imageFormat, bool isEncoder = true);

	//function saves ARGB memory bitmap to file
	//memBitmap - is ARGB memory bitmap
	//fileName - is file name
	//imageFormat - is image format (bmp, png, jpg...)
	void SaveMemBitmapToFile(MemBmpARGB &memBitmap, const wchar_t* fileName,
		const System::Drawing::Imaging::ImageFormatPtr &imageFormat = System::Drawing::Imaging::ImageFormat::get_Png());
	//function loads ARGB memory bitmap from file
	//fileName - is file name
	//returns ARGB memory bitmap
	MemBmpARGB LoadMemBitmapFromFile(const wchar_t* fileName);

	//function converts Aspose Bitmap to ARGB memory bitmap
	//bitmap - is Aspose Bitmap
	//returns ARGB memory bitmap
	MemBmpARGB AsposeBitmapToMemBitmap(System::SharedPtr<System::Drawing::Bitmap> bitmap);
	//function converts ARGB memory bitmap to Aspose Bitmap
	//memBitmap - is ARGB memory bitmap
	//returns Aspose Bitmap
	System::SharedPtr<System::Drawing::Bitmap> MemBitmapToAsposeBitmap(MemBmpARGB &memBitmap);

	//function converts GDI+ Bitmap to ARGB memory bitmap
	//bitmap - is GDI+ Bitmap
	//returns ARGB memory bitmap
	MemBmpARGB GdiPlusBitmapToMemBitmap(Gdiplus::Bitmap &bitmap);
	//function converts ARGB memory bitmap to GDI+ Bitmap
	//memBitmap - is ARGB memory bitmap
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> MemBitmapToGdiPlusBitmap(MemBmpARGB &memBitmap);

	//function converts Aspose Bitmap to GDI+ Bitmap
	//abitmap - is Aspose Bitmap
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> AsposeBitmapToGdiPlusBitmap(System::SharedPtr<System::Drawing::Bitmap> abitmap);
	//function converts GDI+ Bitmap to Aspose Bitmap
	//gbitmap - is GDI+ Bitmap
	//returns Aspose Bitmap
	System::SharedPtr<System::Drawing::Bitmap> GdiPlusBitmapToAsposeBitmap(Gdiplus::Bitmap &gbitmap);

	//function load GDI+ Bitmap from memory stream
	//memoryStream - is memory stream
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> GdiPlusBitmapFromMemoryStream(System::SharedPtr<System::IO::MemoryStream> memoryStream);
	//function saves GDI+ Bitmap to memory stream
	//gbitmap - is GDI+ Bitmap
	//imageFormat - is image format (bmp, png, jpg...)
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> GdiPlusBitmapToMemoryStream(Gdiplus::Bitmap &gbitmap, const GUID &imageFormat = Gdiplus::ImageFormatPNG);

	//function saves GDI+ Bitmap to file
	//gbitmap - is GDI+ Bitmap
	//fileName - is file name
	//imageFormat - is image format (bmp, png, jpg...)
	void SaveGdiPlusBitmapToFile(Gdiplus::Bitmap &gbitmap, const wchar_t* fileName, const GUID &imageFormat = Gdiplus::ImageFormatPNG);
	//function loads GDI+ Bitmap from file
	//fileName - is file name
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> LoadGdiPlusBitmapFromFile(const wchar_t* fileName);
}