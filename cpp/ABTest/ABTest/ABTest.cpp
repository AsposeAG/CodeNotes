//#if (_MSC_VER >= 1915)
//#define no_init_all deprecated
//#endif

#include <windows.h>
#include <Licensing\License.h>
#include <Generation/EncodeTypes/SymbologyEncodeType.h>
#include <Generation/EncodeTypes/EncodeTypes.h>
#include <BarCode.Generation/BarcodeGenerator.h>
#include <BarCode.Generation/GenerationParameters/BaseGenerationParameters.h>
#include <BarCode.Generation/GenerationParameters/BarcodeParameters.h>
#include <BarCode.Generation/GenerationParameters/CodetextParameters.h>
#include <BarCode.Generation/Helpers/Unit.h>
#include <Generation/BarCodeImageFormat.h>

//BarCodeReader
#include <BarCodeRecognition/Recognition/RecognitionSession/BarCodeReader.h>
#include <BarCodeRecognition/Recognition/RecognitionSession/DecodeTypes/DecodeType.h>
#include <BarCodeRecognition/Recognition/RecognitionSession/DecodeTypes/MultyDecodeType.h>
#include <BarCodeRecognition/Recognition/RecognitionSession/DecodeTypes/SingleDecodeType.h>

//forward declarations
void RecognizeBarcodeToConsole(std::wstring& folder);
void GenerateBarcode(std::wstring& folder);

int main()
{
    std::wstring lExampleFolder = L"d:\\save\\rec\\cpp\\";

    //set license
    //System::SharedPtr<Aspose::BarCode::License> license = System::MakeObject<Aspose::BarCode::License>();
    //license->SetLicense(System::String::FromWCS(lExampleFolder + L"LicenseName.lic"));
    
    GenerateBarcode(lExampleFolder);
    RecognizeBarcodeToConsole(lExampleFolder);

    std::wcout << L"Complete!\n";
}

void RecognizeBarcodeToConsole(std::wstring& folder)
{
    //PLEASE USE RELEASE MODE IT IS FASTER IN 20-60 TIMES THEN DEBUG MODE
    //create barcode reader with Code128 symbology
    System::SharedPtr<Aspose::BarCode::BarCodeRecognition::BarCodeReader> reader =
        System::MakeObject<Aspose::BarCode::BarCodeRecognition::BarCodeReader>(System::String::FromWCS(folder + L"code128.png"),
            Aspose::BarCode::BarCodeRecognition::DecodeType::Code128);
    
    //read recognized values and write to the console
    while (reader->Read())
    {
        std::wstring result = L"Type:" + reader->GetCodeTypeName().ToWCS() + L" Codetext:" + reader->GetCodeText().ToWCS() + L"\n";
        std::wcout << result.data();
    }
    std::wcout << L"Barcode recognized!\n";
}

void GenerateBarcode(std::wstring &folder)
{
    //initialize out codetext
    const System::String codeText = u"ABCTZCS1234567890T4444T5678901234XYZ";

    //create barcode generator with Code128 symbology
    System::SharedPtr<Aspose::BarCode::Generation::BarcodeGenerator> barcodeGenerator = System::MakeObject<Aspose::BarCode::Generation::BarcodeGenerator>(Aspose::BarCode::Generation::EncodeTypes::Code128, codeText);
    //set barcode parameters as no codetext
    barcodeGenerator->get_Parameters()->get_Barcode()->get_CodeTextParameters()->set_Location(Aspose::BarCode::Generation::CodeLocation::None);
    //and bar unit size 5 pixels
    barcodeGenerator->get_Parameters()->get_Barcode()->get_XDimension()->set_Pixels(5);

    //save our barcode in png format
    barcodeGenerator->Save(System::String::FromWCS(folder + L"code128.png"), Aspose::BarCode::BarCodeImageFormat::Png);
    std::wcout << L"Barcode generated!\n";
}