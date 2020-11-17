#include "example.h"
#include <Generation/EncodeTypes/SymbologyEncodeType.h>
#include <Generation/EncodeTypes/EncodeTypes.h>
#include <BarCode.Generation/BarcodeGenerator.h>
#include <BarCode.Generation/GenerationParameters/BaseGenerationParameters.h>
#include <BarCode.Generation/GenerationParameters/BarcodeParameters.h>
#include <BarCode.Generation/GenerationParameters/CodetextParameters.h>
#include <BarCode.Generation/GenerationParameters/Padding.h>
#include <BarCode.Generation/Helpers/Unit.h>
#include <Generation/BarCodeImageFormat.h>

#include <system/io/file_stream.h>
#include <drawing/bitmap.h>
#include <drawing/image.h>

//BarCodeReader
#include <BarCodeRecognition/Recognition/RecognitionSession/BarCodeReader.h>
#include <BarCodeRecognition/Recognition/RecognitionSession/DecodeTypes/DecodeType.h>
#include <BarCodeRecognition/Recognition/RecognitionSession/DecodeTypes/MultyDecodeType.h>
#include <BarCodeRecognition/Recognition/RecognitionSession/DecodeTypes/SingleDecodeType.h>

using namespace ABGate;

#pragma region HelperExamplesDefinition
//forward declarations for example functions

//functions creates initialized example barcode generator object
System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> CreateInitializedExampleGenerator();

//functions generates barcode and saves it to memory stream in selected format
System::SharedPtr<System::IO::MemoryStream> SaveGeneratorIntoMemoryStream(System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> generator,
	const Aspose::BarCode::BarCodeImageFormat &format = Aspose::BarCode::BarCodeImageFormat::Png);

//functions saves Aspose Bitmap to file
void SaveAsposeBitmapToFile(System::SharedPtr<System::Drawing::Bitmap> abitmap, const wchar_t* fileName);

//functions saves memory stream to file
void SaveMemoryStreamToFile(System::SharedPtr<System::IO::MemoryStream> memoryStream, const wchar_t* fileName);

//saves HBITMAP to file
void SaveHBITMAP(HBITMAP hbmp, const wchar_t* fileName);

//functions creates GDI+ Bitmap with predefined size
std::shared_ptr<Gdiplus::Bitmap> GetInitializedGdiPlusBitmap(const int &width = 2000, const int &height = 2000);

//functions creates HBITMAP object with predefined size
HBITMAP GetInitializedHBITMAP(const int &width = 2000, const int &height = 2000);

//functions combines folder name with file name
std::wstring PathCombine(const wchar_t* pathName, const wchar_t* fileName);
#pragma endregion


/**************************TEST AREA BEGIN*************************************/
//functions demonstrates how to recognize barcode from  GDI+ Bitmap
void HowToRecognize(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//get GDI+ bitmap
	std::shared_ptr<Gdiplus::Bitmap> gbmpMain = AsposeBitmapToGdiPlusBitmap(builder->GenerateBarCodeImage());
	
	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//write Gdi+ bitmap to stream
	System::SharedPtr<System::IO::MemoryStream> msmain = GdiPlusBitmapToMemoryStream(*gbmpMain);

	//recognize
	System::SharedPtr<Aspose::BarCode::BarCodeRecognition::BarCodeReader> reader =
		System::MakeObject<Aspose::BarCode::BarCodeRecognition::BarCodeReader>(msmain,
			Aspose::BarCode::BarCodeRecognition::DecodeType::Code128);

	while (reader->Read())
	{
		std::wstring result = L"Type:" + reader->GetCodeTypeName().ToWCS() + L" Codetext:" + reader->GetCodeText().ToWCS() + L"\n";
		std::wcout << result.data();
	}
}

//functions demonstrates how to draw barcodes on HBITMAP object
void HowToDrawBarcodeOnHBITMAP(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//get Aspose bitmap
	System::SharedPtr<System::Drawing::Bitmap> abmpmain = builder->GenerateBarCodeImage();
	//HBITMAP which we can obtain
	HBITMAP hbitmapCanvas = GetInitializedHBITMAP();

	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//or bitmap with barcdoe
	std::shared_ptr<Gdiplus::Bitmap> gbmpbarcode = AsposeBitmapToGdiPlusBitmap(abmpmain);
	
	//convert HBITMAP to Bitmap
	//we don't have device palette so set to NULL
	Gdiplus::Bitmap *bitmapCanvas = Gdiplus::Bitmap::FromHBITMAP(hbitmapCanvas, NULL);
	
	//now we can delete HBITMAP or use in other cases
	SaveHBITMAP(hbitmapCanvas, PathCombine(pathName, L"hbmpdraw_01.png").data());
	DeleteObject(hbitmapCanvas);

	//create graphic for drawing
	Gdiplus::Graphics *graph = Gdiplus::Graphics::FromImage(bitmapCanvas);
	//draw in coord 10, 15 width 400 height 136
	graph->DrawImage(gbmpbarcode.get(), 10, 15, 400, 136);
	//draw other image
	graph->DrawImage(gbmpbarcode.get(), 700, 300, 500, 236);
	delete graph;

	//extract new HBITMAP
	HBITMAP resultedHbmp;
	bitmapCanvas->GetHBITMAP(Gdiplus::Color::White, &resultedHbmp);
	//we can delete GDI+ bitmap canvas
	delete bitmapCanvas;

	//do what you want with resulted HBITMAP
	SaveHBITMAP(resultedHbmp, PathCombine(pathName, L"hbmpdraw_02.png").data());
	DeleteObject(resultedHbmp);
}

//functions demonstrates how to draw barcodes on GDI+ bitmap
void HowToDrawBarcodeOnBitmap(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//get Aspose bitmap
	System::SharedPtr<System::Drawing::Bitmap> abmpmain = builder->GenerateBarCodeImage();
	//bitmap which we will use as canvas, can be created or loaded
	std::shared_ptr<Gdiplus::Bitmap> bitmapCanvas = GetInitializedGdiPlusBitmap();

	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//or bitmap with barcdoe
	std::shared_ptr<Gdiplus::Bitmap> gbmpbarcode = AsposeBitmapToGdiPlusBitmap(abmpmain);
	
	//create graphic for drawing
	Gdiplus::Graphics *graph = Gdiplus::Graphics::FromImage(bitmapCanvas.get());
	//draw in coord 10, 15 width 400 height 136
	graph->DrawImage(gbmpbarcode.get(), 10, 15, 400, 136);
	//draw other image
	graph->DrawImage(gbmpbarcode.get(), 700, 300, 500, 236);
	delete graph;

	//save bitmap
	SaveGdiPlusBitmapToFile(*bitmapCanvas, PathCombine(pathName, L"gdraw_01.png").data());
}

//functions demonstrates how to load and save GDI+ bitmaps to memory stream
void HowToWorkWithGdiPlusAndMemoryStream(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//save barcode image into memory stream
	System::SharedPtr<System::IO::MemoryStream> msmain = SaveGeneratorIntoMemoryStream(builder);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	SaveMemoryStreamToFile(msmain, PathCombine(pathName, L"gmstr_01.png").data());

	//load to GDI+ Bitmap
	std::shared_ptr<Gdiplus::Bitmap> gbmpmain = GdiPlusBitmapFromMemoryStream(msmain);
	SaveGdiPlusBitmapToFile(*gbmpmain, PathCombine(pathName, L"gmstr_02.png").data());

	//gdi+ to memory stream
	System::SharedPtr<System::IO::MemoryStream> msgdip = GdiPlusBitmapToMemoryStream(*gbmpmain);
	SaveMemoryStreamToFile(msgdip, PathCombine(pathName, L"gmstr_03.png").data());

	//to aspose bitmap
	System::SharedPtr<System::Drawing::Bitmap> abmp = System::MakeObject<System::Drawing::Bitmap>(msgdip);
	SaveAsposeBitmapToFile(abmp, PathCombine(pathName, L"gmstr_04.png").data());
}

//functions demonstrates how to convert data between GDI+ and Aspose bitmap objects
void HowToWorkWithGdiPlusAndAsposeBitmapConversion(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//get Aspose bitmap
	System::SharedPtr<System::Drawing::Bitmap> abmpmain = builder->GenerateBarCodeImage();


	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//aspose bitmap to gdi+ bitmap
	std::shared_ptr<Gdiplus::Bitmap> gbmpmain = AsposeBitmapToGdiPlusBitmap(abmpmain);

	//save and load
	SaveGdiPlusBitmapToFile(*gbmpmain, PathCombine(pathName, L"agbmp_01.png").data());
	std::shared_ptr<Gdiplus::Bitmap> gbmploaded = LoadGdiPlusBitmapFromFile(PathCombine(pathName, L"agbmp_01.png").data());
	SaveGdiPlusBitmapToFile(*gbmpmain, PathCombine(pathName, L"agbmp_02.png").data());

	//gdi+ to aspose bitmap
	System::SharedPtr<System::Drawing::Bitmap> abmploaded = GdiPlusBitmapToAsposeBitmap(*gbmploaded);
	SaveAsposeBitmapToFile(abmploaded, PathCombine(pathName, L"agbmp_03.png").data());
}

//functions demonstrates how to extract from and to ARGB memory bitmap
void HowToWorkWithMemBmpARGB(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//get Aspose bitmap
	System::SharedPtr<System::Drawing::Bitmap> abmpmain = builder->GenerateBarCodeImage();


	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create memory bitmap
	MemBmpARGB mbmpmain = AsposeBitmapToMemBitmap(abmpmain);

	//save and load from file
	SaveMemBitmapToFile(mbmpmain, PathCombine(pathName, L"mbmp_01.png").data());
	MemBmpARGB mbmploaded = LoadMemBitmapFromFile(PathCombine(pathName, L"mbmp_01.png").data());

	//convert to aspose bitmap
	System::SharedPtr<System::Drawing::Bitmap> abmploaded = MemBitmapToAsposeBitmap(mbmploaded);
	SaveAsposeBitmapToFile(abmploaded, PathCombine(pathName, L"mbmp_02.png").data());

	//membmp to GDI+
	std::shared_ptr<Gdiplus::Bitmap> gbmpmain = MemBitmapToGdiPlusBitmap(mbmpmain);
	SaveGdiPlusBitmapToFile(*gbmpmain, PathCombine(pathName, L"mbmp_03.png").data());

	//gdi+to MemBmp
	MemBmpARGB gmembmp = GdiPlusBitmapToMemBitmap(*gbmpmain);
	SaveMemBitmapToFile(gmembmp, PathCombine(pathName, L"mbmp_04.png").data());
}

//functions demonstrates how to extract data from and to memory stream
//with special data types like memory buffer or std::string
void HowToConvertAndSaveMemoryStreamExt(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//save barcode image into memory stream
	System::SharedPtr<System::IO::MemoryStream> msmain = SaveGeneratorIntoMemoryStream(builder);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//convert memory stream into classic byte array
	ByteArray barrmain = MemoryStreamToByteArray(msmain);
	//save it
	SaveByteArrayToFile(barrmain, PathCombine(pathName, L"strarr_01.png").data());

	//create memory stream as buffer 
	System::SharedPtr<System::IO::MemoryStream> msbuffer = MemoryStreamFromBuffer(barrmain.data(), barrmain.size());
	//save memory stream
	SaveMemoryStreamToFile(msbuffer, PathCombine(pathName, L"strarr_02.png").data());

	//convert to string and from string
	std::string strbuff = MemoryStreamToString(msbuffer);
	System::SharedPtr<System::IO::MemoryStream> msstring = StringToToMemoryStream(strbuff);
	//save memory stream
	SaveMemoryStreamToFile(msstring, PathCombine(pathName, L"strarr_03.png").data());
}

//functions demonstrates how to extract data from and to memory stream
void HowToConvertAndSaveMemoryStream(const wchar_t* pathName)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!INITIALIZATION PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//create generator
	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> builder = CreateInitializedExampleGenerator();
	//save barcode image into memory stream
	System::SharedPtr<System::IO::MemoryStream> msmain = SaveGeneratorIntoMemoryStream(builder);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!EXAMPLE PART!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//convert memory stream into classic byte array
	ByteArray barrmain = MemoryStreamToByteArray(msmain);
	
	//save it and load
	SaveByteArrayToFile(barrmain, PathCombine(pathName, L"armt_01.png").data());
	ByteArray barrloaded = LoadByteArrayFromFile(PathCombine(pathName, L"armt_01.png").data());

	//convert loaded into memory stream and save
	System::SharedPtr<System::IO::MemoryStream> msconverted = ByteArrayToMemoryStream(barrloaded);
	SaveMemoryStreamToFile(msconverted, PathCombine(pathName, L"armt_02.png").data());
}
/**************************TEST AREA END***************************************/

#pragma region HelperExamplesDeclaration
//functions combines folder name with file name
std::wstring PathCombine(const wchar_t* pathName, const wchar_t* fileName)
{
	std::wstring path = pathName;
	wchar_t last = path[path.size() - 1];
	if (last != '/' || last != '\\')
		path += L"\\";
	path += fileName;
	return path;
}

//functions creates HBITMAP object with predefined size
HBITMAP GetInitializedHBITMAP(const int &width, const int &height)
{
	Gdiplus::Bitmap *bmp = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);

	Gdiplus::Graphics *graph = Gdiplus::Graphics::FromImage(bmp);
	graph->Clear(Gdiplus::Color::White);
	delete graph;

	//create hbitmap
	HBITMAP hbmp;
	//background color is white
	bmp->GetHBITMAP(Gdiplus::Color::White, &hbmp);
	delete bmp;

	return hbmp;
}

//functions creates GDI+ Bitmap with predefined size
std::shared_ptr<Gdiplus::Bitmap> GetInitializedGdiPlusBitmap(const int &width, const int &height)
{
	Gdiplus::Bitmap *bmp = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);
	
	Gdiplus::Graphics *graph = Gdiplus::Graphics::FromImage(bmp);
	graph->Clear(Gdiplus::Color::White);
	delete graph;

	return (std::shared_ptr<Gdiplus::Bitmap>)bmp;
}

//saves HBITMAP to file
void SaveHBITMAP(HBITMAP hbmp, const wchar_t* fileName)
{
	Gdiplus::Bitmap *bmp = Gdiplus::Bitmap::FromHBITMAP(hbmp, NULL);
	SaveGdiPlusBitmapToFile(*bmp, fileName);
	delete bmp;
}

//functions saves Aspose Bitmap to file
void SaveAsposeBitmapToFile(System::SharedPtr<System::Drawing::Bitmap> abitmap, const wchar_t* fileName)
{
	abitmap->Save(System::String::FromWCS(fileName));
}

//functions saves memory stream to file
void SaveMemoryStreamToFile(System::SharedPtr<System::IO::MemoryStream> memoryStream, const wchar_t* fileName)
{
	System::SharedPtr<System::IO::FileStream> fs = System::MakeObject<System::IO::FileStream>(System::String::FromWCS(fileName), System::IO::FileMode::Create);
	memoryStream->set_Position(0);
	memoryStream->WriteTo(fs);
	fs->Close();
}

//functions generates barcode and saves it to memory stream in selected format
System::SharedPtr<System::IO::MemoryStream> SaveGeneratorIntoMemoryStream(System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> generator,
	const Aspose::BarCode::BarCodeImageFormat &format)
{
	System::SharedPtr<System::IO::MemoryStream> ms = System::MakeObject<System::IO::MemoryStream>();
	generator->Save(ms, format);
	ms->set_Position(0);
	return ms;
}

//functions creates initialized example barcode generator object
System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> CreateInitializedExampleGenerator()
{
	const System::String codeText = u"ABCTZCS1234567890T4444T5678901234XYZ";

	System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> barcodeGenerator = System::MakeObject<Aspose::BarCode::Generation::BarcodeGenerator>(Aspose::BarCode::Generation::EncodeTypes::Code128, codeText);
	barcodeGenerator->get_Parameters()->get_Barcode()->get_CodeTextParameters()->set_Location(Aspose::BarCode::Generation::CodeLocation::None);
	barcodeGenerator->get_Parameters()->set_RotationAngle(0);
	barcodeGenerator->get_Parameters()->get_Barcode()->get_Padding()->get_Top()->set_Millimeters(2.f);

	return barcodeGenerator;
}
#pragma endregion