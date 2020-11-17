#include "bitmap_convertor.h"
#include <algorithm>


namespace ABGate
{
	//function saves ARGB memory bitmap to file
	//memBitmap - is ARGB memory bitmap
	//fileName - is file name
	//imageFormat - is image format (bmp, png, jpg...)
	void SaveMemBitmapToFile(MemBmpARGB &memBitmap, const wchar_t* fileName, const System::Drawing::Imaging::ImageFormatPtr &imageFormat)
	{
		System::SharedPtr<System::Drawing::Bitmap> bitmap = MemBitmapToAsposeBitmap(memBitmap);
		bitmap->Save(System::String::FromWCS(fileName), imageFormat);
		bitmap->Dispose();
	}

	//function loads ARGB memory bitmap from file
	//fileName - is file name
	//returns ARGB memory bitmap
	MemBmpARGB LoadMemBitmapFromFile(const wchar_t* fileName)
	{
		System::SharedPtr<System::Drawing::Bitmap> bitmap =
			System::MakeObject<System::Drawing::Bitmap>(System::String::FromWCS(fileName));
		MemBmpARGB memBitmap = AsposeBitmapToMemBitmap(bitmap);
		bitmap->Dispose();
		return memBitmap;
	}

	//function converts Aspose Bitmap to ARGB memory bitmap
	//bitmap - is Aspose Bitmap
	//returns ARGB memory bitmap
	MemBmpARGB AsposeBitmapToMemBitmap(System::SharedPtr<System::Drawing::Bitmap> bitmap)
	{
		MemBmpARGB memBitmap(bitmap->get_Width(), bitmap->get_Height());

		//lock and extract bitmap data
		System::Drawing::Rectangle rect(0, 0, bitmap->get_Width(), bitmap->get_Height());
		System::SharedPtr<System::Drawing::Imaging::BitmapData> lBmpData =
			bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadOnly, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
		int lBuffSize = std::min(lBmpData->get_Stride() * lBmpData->get_Height(), (int)memBitmap.Data.size());
		
		//copy data
		memcpy(memBitmap.Data.data(), (void*)lBmpData->get_Scan0(), lBuffSize);
		bitmap->UnlockBits(lBmpData);

		return memBitmap;
	}

	//function converts ARGB memory bitmap to Aspose Bitmap
	//memBitmap - is ARGB memory bitmap
	//returns Aspose Bitmap
	System::SharedPtr<System::Drawing::Bitmap> MemBitmapToAsposeBitmap(MemBmpARGB &memBitmap)
	{
		System::SharedPtr<System::Drawing::Bitmap> bitmap = 
			System::MakeObject<System::Drawing::Bitmap>(memBitmap.Width, memBitmap.Height, System::Drawing::Imaging::PixelFormat::Format32bppArgb);

		//lock and extract bitmap data
		System::Drawing::Rectangle rect(0, 0, memBitmap.Width, memBitmap.Height);
		System::SharedPtr<System::Drawing::Imaging::BitmapData> lBmpData =
			bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::WriteOnly, System::Drawing::Imaging::PixelFormat::Format32bppArgb);

		int lBuffSize = std::min(lBmpData->get_Stride() * lBmpData->get_Height(), (int)memBitmap.Data.size());

		//copy data
		memcpy((void*)lBmpData->get_Scan0(), memBitmap.Data.data(), lBuffSize);
		bitmap->UnlockBits(lBmpData);

		return bitmap;
	}

	//function converts GDI+ Bitmap to ARGB memory bitmap
	//bitmap - is GDI+ Bitmap
	//returns ARGB memory bitmap
	MemBmpARGB GdiPlusBitmapToMemBitmap(Gdiplus::Bitmap &bitmap)
	{
		MemBmpARGB memBitmap(bitmap.GetWidth(), bitmap.GetHeight());

		//lock and extract bitmap data
		Gdiplus::BitmapData bitmapData;
		Gdiplus::Rect rect(0, 0, bitmap.GetWidth(), bitmap.GetHeight());
		bitmap.LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
		int lBuffSize = std::min((int)(bitmapData.Stride * bitmapData.Height), (int)memBitmap.Data.size());

		//copy data
		memcpy(memBitmap.Data.data(), bitmapData.Scan0, lBuffSize);
		bitmap.UnlockBits(&bitmapData);

		return memBitmap;
	}

	//function converts ARGB memory bitmap to GDI+ Bitmap
	//memBitmap - is ARGB memory bitmap
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> MemBitmapToGdiPlusBitmap(MemBmpARGB &memBitmap)
	{
		std::shared_ptr<Gdiplus::Bitmap> bitmap = std::make_shared <Gdiplus::Bitmap>(memBitmap.Width, memBitmap.Height, PixelFormat32bppARGB);

		//lock and extract bitmap data
		Gdiplus::BitmapData bitmapData;
		Gdiplus::Rect rect(0, 0, memBitmap.Width, memBitmap.Height);
		bitmap->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bitmapData);
		int lBuffSize = std::min((int)(bitmapData.Stride * bitmapData.Height), (int)memBitmap.Data.size());

		//copy data
		memcpy(bitmapData.Scan0, memBitmap.Data.data(), lBuffSize);
		bitmap->UnlockBits(&bitmapData);

		return bitmap;
	}

	//function converts Aspose Bitmap to GDI+ Bitmap
	//abitmap - is Aspose Bitmap
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> AsposeBitmapToGdiPlusBitmap(System::SharedPtr<System::Drawing::Bitmap> abitmap)
	{
		std::shared_ptr<Gdiplus::Bitmap> gbitmap = std::make_shared<Gdiplus::Bitmap>(abitmap->get_Width(), abitmap->get_Height(), PixelFormat32bppARGB);

		//lock gbitmap
		Gdiplus::BitmapData gbitmapData;
		Gdiplus::Rect grect(0, 0, abitmap->get_Width(), abitmap->get_Height());
		gbitmap->LockBits(&grect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &gbitmapData);

		//lock abitmap
		System::Drawing::Rectangle arect(0, 0, abitmap->get_Width(), abitmap->get_Height());
		System::SharedPtr<System::Drawing::Imaging::BitmapData> abitmapData =
			abitmap->LockBits(arect, System::Drawing::Imaging::ImageLockMode::ReadOnly, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
		
		//copy
		int lBuffSize = std::min((int)(gbitmapData.Stride * gbitmapData.Height), abitmapData->get_Stride() * abitmapData->get_Height());
		memcpy(gbitmapData.Scan0, (void*)abitmapData->get_Scan0(), lBuffSize);

		//unlock
		abitmap->UnlockBits(abitmapData);
		gbitmap->UnlockBits(&gbitmapData);

		return gbitmap;
	}

	//function converts GDI+ Bitmap to Aspose Bitmap
	//gbitmap - is GDI+ Bitmap
	//returns Aspose Bitmap
	System::SharedPtr<System::Drawing::Bitmap> GdiPlusBitmapToAsposeBitmap(Gdiplus::Bitmap &gbitmap)
	{
		System::SharedPtr<System::Drawing::Bitmap> abitmap =
			System::MakeObject<System::Drawing::Bitmap>(gbitmap.GetWidth(), gbitmap.GetHeight(), System::Drawing::Imaging::PixelFormat::Format32bppArgb);

		//lock abitmap
		System::Drawing::Rectangle arect(0, 0, abitmap->get_Width(), abitmap->get_Height());
		System::SharedPtr<System::Drawing::Imaging::BitmapData> abitmapData =
			abitmap->LockBits(arect, System::Drawing::Imaging::ImageLockMode::WriteOnly, System::Drawing::Imaging::PixelFormat::Format32bppArgb);

		//lock gbitmap
		Gdiplus::BitmapData gbitmapData;
		Gdiplus::Rect grect(0, 0, abitmap->get_Width(), abitmap->get_Height());
		gbitmap.LockBits(&grect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &gbitmapData);

		//copy
		int lBuffSize = std::min((int)(gbitmapData.Stride * gbitmapData.Height), abitmapData->get_Stride() * abitmapData->get_Height());
		memcpy((void*)abitmapData->get_Scan0(), gbitmapData.Scan0, lBuffSize);

		//unlock
		abitmap->UnlockBits(abitmapData);
		gbitmap.UnlockBits(&gbitmapData);

		return abitmap;
	}

	//function load GDI+ Bitmap from memory stream
	//memoryStream - is memory stream
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> GdiPlusBitmapFromMemoryStream(System::SharedPtr<System::IO::MemoryStream> memoryStream)
	{
		IStream* istr = MemoryStreamToIStream(memoryStream);
		std::shared_ptr<Gdiplus::Bitmap> bmp(Gdiplus::Bitmap::FromStream(istr));
		istr->Release();
		return bmp;
	}

	//function saves GDI+ Bitmap to memory stream
	//gbitmap - is GDI+ Bitmap
	//imageFormat - is image format (bmp, png, jpg...)
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> GdiPlusBitmapToMemoryStream(Gdiplus::Bitmap &gbitmap, const GUID &imageFormat)
	{
		//create zero memory stream
		IStream* istr = SHCreateMemStream(NULL, 0);

		CLSID codec = FindCodecByFormat(imageFormat);
		gbitmap.Save(istr, &codec);
		System::SharedPtr<System::IO::MemoryStream> memoryStream = IStreamToMemoryStream(istr);
		istr->Release();

		return memoryStream;
	}

	//function saves GDI+ Bitmap to file
	//gbitmap - is GDI+ Bitmap
	//fileName - is file name
	//imageFormat - is image format (bmp, png, jpg...)
	void SaveGdiPlusBitmapToFile(Gdiplus::Bitmap &gbitmap, const wchar_t* fileName, const GUID &imageFormat)
	{
		CLSID codec = FindCodecByFormat(imageFormat);
		Gdiplus::Status lstat = gbitmap.Save(fileName, &codec);
	}
	
	//function loads GDI+ Bitmap from file
	//fileName - is file name
	//returns GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> LoadGdiPlusBitmapFromFile(const wchar_t* fileName)
	{
		return std::shared_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(fileName));
	}

	//function searches image encoders/decoder for GDI+
	//imageFormat - is image format (bmp, png, jpg...)
	//isEncoder - is is we are searching Encoders(true) or decoders(false)
	//returns encoder/decoders ID
	CLSID FindCodecByFormat(const GUID &imageFormat, bool isEncoder)
	{
		//get buffer size
		UINT  num, size;
		Gdiplus::Status stat = Gdiplus::Status::Ok;
		if (isEncoder)
			stat = Gdiplus::GetImageEncodersSize(&num, &size);
		else
			stat = Gdiplus::GetImageDecodersSize(&num, &size);
		
		if ((Gdiplus::Status::Ok!= stat) || (0 == size))
			return CLSID_NULL;

		//get encoders/decoders
		Gdiplus::ImageCodecInfo* pArray = (Gdiplus::ImageCodecInfo*)(malloc(size));
		if (isEncoder)
			Gdiplus::GetImageEncoders(num, size, pArray);
		else
			Gdiplus::GetImageDecoders(num, size, pArray);

		CLSID codec = CLSID_NULL;
		for (UINT j = 0; j < num; ++j)
			if (imageFormat == pArray[j].FormatID)
			{
				codec = pArray[j].Clsid;
				break;
			}

		free(pArray);
		return codec;
	}
}
