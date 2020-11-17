#include "memstr_convertor.h"

namespace ABGate
{
	
	//function saves byte array to file
	//is used for debugging
	//arr - is byte array
	//fileName - is a name of file on disk
	void SaveByteArrayToFile(ByteArray &arr, const wchar_t* fileName)
	{
		std::ofstream file(fileName, std::ios::out | std::ios::binary);
		file.write((char*)arr.data(), arr.size());
		file.close();
	}
	
	//function loads byte array from file
	//is used for debugging
	//fileName - is a name of file on disk
	//returns byte array
	ByteArray LoadByteArrayFromFile(const wchar_t* fileName)
	{
		std::ifstream file(fileName, std::ios::in | std::ios::binary);
		
		//get length of file
		file.seekg(0, std::ios::end);
		size_t length = file.tellg();
		file.seekg(0, std::ios::beg);
		
		ByteArray res(length);
		file.read((char*)res.data(), length);
		file.close();
		return res;
	}
	
	//function creates MemoryStream from memory buffer
	//buffer - is memory buffer
	//size - is a buffer size
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> MemoryStreamFromBuffer(void* buffer, int size)
	{
		//initialize memory stream capacity
		System::SharedPtr<System::IO::MemoryStream> memoryStream = System::MakeObject<System::IO::MemoryStream>();
		memoryStream->SetLength(size);
		System::ByteArrayPtr lMemAdr = memoryStream->GetBuffer();
		
		//copy data and set position to 0
		memcpy(lMemAdr->data_ptr(), buffer, size);
		memoryStream->set_Position(0);
		
		return memoryStream;
	}

	//function converts MemoryStream to std::string as data array
	//memoryStream - is a memory stream
	//returns data array as std::string
	std::string MemoryStreamToString(System::SharedPtr<System::IO::MemoryStream> memoryStream)
	{
		//initialize string capacity
		System::ByteArrayPtr lMemAdr = memoryStream->GetBuffer();
		std::string str(lMemAdr->Count(), '\0');
		
		//copy data
		memcpy((void*)str.data(), lMemAdr->data_ptr(), lMemAdr->Count());

		return str;
	}

	//function converts data array in std::string to memory stream
	//str - is data array as std::string
	//returns memory steam
	System::SharedPtr<System::IO::MemoryStream> StringToToMemoryStream(std::string &str)
	{
		//initialize memory stream capacity
		System::SharedPtr<System::IO::MemoryStream> memoryStream = System::MakeObject<System::IO::MemoryStream>();
		memoryStream->SetLength(str.size());
		System::ByteArrayPtr lMemAdr = memoryStream->GetBuffer();

		//copy data and set position to 0
		memcpy(lMemAdr->data_ptr(), str.data(), str.size());
		memoryStream->set_Position(0);

		return memoryStream;
	}

	//function converts memory stream to byte array
	//memoryStream - is a memory steam
	//returns byte array
	ByteArray MemoryStreamToByteArray(System::SharedPtr<System::IO::MemoryStream> memoryStream)
	{
		//initialize array capacity
		System::ByteArrayPtr lMemAdr = memoryStream->GetBuffer();
		ByteArray arr(lMemAdr->Count());

		//copy data
		memcpy(arr.data(), lMemAdr->data_ptr(), lMemAdr->Count());

		return arr;
	}

	//function converts byte array to memory stream
	//arr - is byte array
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> ByteArrayToMemoryStream(ByteArray &arr)
	{
		//intialize memory stream capacity
		System::SharedPtr<System::IO::MemoryStream> memoryStream = System::MakeObject<System::IO::MemoryStream>();
		memoryStream->SetLength(arr.size());
		System::ByteArrayPtr lMemAdr = memoryStream->GetBuffer();

		//copy data and set position to 0
		memcpy(lMemAdr->data_ptr(), arr.data(), arr.size());
		memoryStream->set_Position(0);

		return memoryStream;
	}

	//function converts byte array to COM IStream implementation
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//arr - is byte array
	//returns COM IStream implementation
	IStream* ByteArrayToIStream(ByteArray &arr)
	{
		return SHCreateMemStream(arr.data(), (UINT)arr.size());
	}

	//function coverts COM IStream implementation to byte array
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//istr - is COM IStream implementation
	//returns byte array
	ByteArray IStreamToByteArray(IStream *istr)
	{
		//set position to zero
		LARGE_INTEGER SeekPos;
		SeekPos.QuadPart = 0;
		ULARGE_INTEGER actualPos;
		ULARGE_INTEGER zeroPos;
		//remember position
		istr->Seek(SeekPos, STREAM_SEEK_CUR, &actualPos);
		//set to zero
		istr->Seek(SeekPos, STREAM_SEEK_SET, &zeroPos);

		//get size
		tagSTATSTG istat;
		istr->Stat(&istat, STATFLAG_NONAME);

		//read to buffer
		int size = istat.cbSize.LowPart;
		ULONG actualBytes = 0;
		ByteArray arr(size);
		istr->Read(arr.data(), size, &actualBytes);

		//return position
		SeekPos.QuadPart = actualPos.QuadPart;
		istr->Seek(SeekPos, STREAM_SEEK_CUR, &actualPos);

		return arr;
	}

	//function converts memory stream to COM IStream implementation
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//memoryStream - is a memory steam
	//returns COM IStream implementation
	IStream* MemoryStreamToIStream(System::SharedPtr<System::IO::MemoryStream> memoryStream)
	{
		ByteArray arr = MemoryStreamToByteArray(memoryStream);
		return ByteArrayToIStream(arr);
	}

	//function coverts COM IStream implementation to memory stream
	//https://docs.microsoft.com/en-us/windows/win32/api/objidl/nn-objidl-istream
	//istr - is COM IStream implementation
	//returns memory stream
	System::SharedPtr<System::IO::MemoryStream> IStreamToMemoryStream(IStream *istr)
	{
		ByteArray arr = IStreamToByteArray(istr);
		//convert to memoryStream
		return ByteArrayToMemoryStream(arr);
	}
}