#pragma once

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include <windows.h>
#include <iostream>
#include <exception>

#include "ABGate/memstr_convertor.h"
#include "ABGate/bitmap_convertor.h"


//test examples
//functions demonstrates how to extract data from and to memory stream
void HowToConvertAndSaveMemoryStream(const wchar_t* pathName);

//functions demonstrates how to extract data from and to memory stream
//with special data types like memory buffer or std::string
void HowToConvertAndSaveMemoryStreamExt(const wchar_t* pathName);

//functions demonstrates how to extract from and to ARGB memory bitmap
void HowToWorkWithMemBmpARGB(const wchar_t* pathName);

//functions demonstrates how to convert data between GDI+ and Aspose bitmap objects
void HowToWorkWithGdiPlusAndAsposeBitmapConversion(const wchar_t* pathName);

//functions demonstrates how to load and save GDI+ bitmaps to memory stream
void HowToWorkWithGdiPlusAndMemoryStream(const wchar_t* pathName);

//functions demonstrates how to draw barcodes on GDI+ bitmap
void HowToDrawBarcodeOnBitmap(const wchar_t* pathName);

//functions demonstrates how to draw barcodes on HBITMAP object
void HowToDrawBarcodeOnHBITMAP(const wchar_t* pathName);

//functions demonstrates how to recognize barcode from  GDI+ Bitmap
void HowToRecognize(const wchar_t* pathName);
