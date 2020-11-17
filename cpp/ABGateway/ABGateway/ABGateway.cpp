#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include <windows.h>
#include <gdiplus.h>
//how to use GDI+
//https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-getting-started-use
#include <iostream>
#include <system\aspose_cpp_library.h>
#include "example.h"

int main()
{
	std::wstring lExampleFolder = L"d:\\save\\rec\\cpp\\";
	
	//initalize GDI+ (must be inialized in process before any call)
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	/**************************TEST AREA BEGIN*************************************/
	//generation and conversion
	HowToConvertAndSaveMemoryStream(lExampleFolder.data());
	HowToConvertAndSaveMemoryStreamExt(lExampleFolder.data());
	HowToWorkWithMemBmpARGB(lExampleFolder.data());
	HowToWorkWithGdiPlusAndAsposeBitmapConversion(lExampleFolder.data());
	HowToWorkWithGdiPlusAndMemoryStream(lExampleFolder.data());
	HowToDrawBarcodeOnBitmap(lExampleFolder.data());
	HowToDrawBarcodeOnHBITMAP(lExampleFolder.data());
	
	//recognition could be slow in debug version use release version(20-60 times faster)
	HowToRecognize(lExampleFolder.data());
	/**************************TEST AREA END***************************************/


	//unload Aspose.Barcode.Cpp library variables and threads
	System::AsposeCppLibrary::PrepareForUnload();

	//shutdown GDI+ (can be avoided if we terminate the process)
	//but we must be attentive in dll creation
	Gdiplus::GdiplusShutdown(gdiplusToken);
}
