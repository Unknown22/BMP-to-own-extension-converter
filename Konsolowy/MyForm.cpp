#include "MyForm.h"
#include "MainHeader.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <msclr/marshal_cppstd.h>
#include <math.h>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;


#pragma pack(2)

struct RGBPixel
{
	int Red;
	int Green;
	int Blue;
};

struct BMPInfoHeader
{
	unsigned short BMPType;			// BM - 0x42 0x4d   19778
	unsigned int FileSize;			// Size of the file
	unsigned short Reserved1;		// Reserved
	unsigned short Reserved2;		// Reserved
	unsigned int OffBits;			// Offset to bitmap data
	unsigned int HeaderSize;		// Size of Header
	int Width;						// Width of image
	int Height;						// Height of image
	unsigned short Planes;			// Number of color planes
	unsigned short BitsPerPxl;		// Number of bits per pixel
	unsigned int Compression;		// Type of compression
	unsigned int ImageSize;			// Size of image
	int XPixels;					// Pixels per meter in x axis
	int YPixels;					// Pixels per meter in y axis
	unsigned int ColorsUsed;		// Number of colors used
	unsigned int ColorsImportant;	// Number of important colors
};

struct MMSSInfoHeader
{
	unsigned short MMSSType;		// MS - 0x4d 0x53   21325
	unsigned int OffBits;			// Offset to bitmap data
	unsigned int HeaderSize;		// Size of Header
	int Width;						// Width of image
	int Height;						// Height of image
	unsigned short BitsPerPxl;		// Number of bits per pixel
	unsigned int Compression;		// Type of compression
	unsigned int ColorsUsed;		// Number of colors used
	unsigned short ColorIndicator;	// Color or Gray Scale Indicator
};
#pragma pack()

FILE* f;
unsigned char* Pixels;
BMPInfoHeader bih;
MMSSInfoHeader msih;
RGBPixel ColorTable[64];
int t = 0; //indeks w tabeli kolorów
int k = 0; //licznik d³ugoœci skompresowanych danych
int lengthOfColors = 0;//licznik d³ugoœci nieskompresowanych kolorów
int predictorName = 0;
unsigned char* Pixels2;
int colorIndicator = 0; //0 obraz kolorowy, 1 obraz w skali szarosci

void GetPredictor::getPr(int num)
{
	predictorName = num;
}

void loadMMSSHeader()
{
	msih.MMSSType = (unsigned short)21325;
	msih.OffBits = (unsigned int)30;
	msih.HeaderSize = (unsigned int)24;
	msih.Width = bih.Width;
	msih.Height = bih.Height;
	msih.BitsPerPxl = (unsigned short)6;
	msih.ColorsUsed = (unsigned int)t;
	msih.Compression = (unsigned int)predictorName; //typ kompresji czyli numer predyktora
	msih.ColorIndicator = (unsigned short)colorIndicator;
}

void loadBMPHeader()
{
	bih.BMPType = (unsigned short)19778;			// BM - 0x42 0x4d   19778
	bih.FileSize = (unsigned int)0;					// Size of the file     do dodania funkcja, która obliczy rozmiar
	bih.Reserved1 = (unsigned short)0;				// Reserved
	bih.Reserved2 = (unsigned short)0;				// Reserved
	bih.OffBits = (unsigned int)54;					// Offset to bitmap data
	bih.HeaderSize = (unsigned int)40;				// Size of Header
	bih.Width = msih.Width;							// Width of image
	bih.Height = msih.Height;						// Height of image
	bih.Planes = (unsigned short)1;					// Number of color planes
	bih.BitsPerPxl = (unsigned short)24;			// Number of bits per pixel
	bih.Compression = (unsigned int)0;				// Type of compression
	bih.ImageSize = (unsigned int)0;				// Size of image     FileSize - OffBits po dodaniu funkcji obliczaj¹cej FileSize mo¿na dodaæ
	bih.XPixels = (int)0;							// Pixels per meter in x axis
	bih.YPixels = (int)0;							// Pixels per meter in y axis
	bih.ColorsUsed = (unsigned int)0;				// Number of colors used
	bih.ColorsImportant = (unsigned int)0;			// Number of important colors
}

int GetFileSize()
{
	fseek(f, 0, SEEK_END);
	return ftell(f);
}

int MakeColorTable()
{
	t = 0;
	RGBPixel CheckColor;
	int m = 0; //okresla czy kolor byl juz w tablicy, 0 - nie byl, 1 - byl
	for (int i = 0; i < bih.Height*bih.Width * 3; i += 3)
	{
		m = 0;
		CheckColor.Red = (int)Pixels[i + 2];
		CheckColor.Green = (int)Pixels[i + 1];
		CheckColor.Blue = (int)Pixels[i];
		for (int x = 0; x < t; x++)
		{
			if (ColorTable[x].Red == CheckColor.Red &&
				ColorTable[x].Green == CheckColor.Green &&
				ColorTable[x].Blue == CheckColor.Blue)
			{
				m = 1;
			}
		}
		if (m != 1)
		{
			ColorTable[t].Red = CheckColor.Red;
			ColorTable[t].Green = CheckColor.Green;
			ColorTable[t].Blue = CheckColor.Blue;
			t++;
		}
	}
	return t;
}

void changeColorsToGreyScale()
{
	for (int x = 0; x < t; x++)
	{
		ColorTable[x].Red = (unsigned char)(0.299*ColorTable[x].Red + 0.587*ColorTable[x].Green + 0.114*ColorTable[x].Blue + 0.5);
		ColorTable[x].Green = (unsigned char)(0.299*ColorTable[x].Red + 0.587*ColorTable[x].Green + 0.114*ColorTable[x].Blue + 0.5);
		ColorTable[x].Blue = (unsigned char)(0.299*ColorTable[x].Red + 0.587*ColorTable[x].Green + 0.114*ColorTable[x].Blue + 0.5);
	}
}

void GetColorIndicator::getCi(int i)
{
	colorIndicator = i;
}

void ReadBMP(char* path)
{
	f = fopen(path, "rb");
	if (f != NULL)
	{
		fread(&bih, sizeof(BMPInfoHeader), 1, f);
		if (bih.BMPType != 19778)
		{
			fclose(f);
			return;
		}

		unsigned int mallocSize = bih.Height * bih.Width * 3;
		Pixels = (unsigned char *)malloc(mallocSize * sizeof(unsigned char));
		unsigned char pad[4] = { 0 };
		unsigned int padding = (4 - ((bih.Width * 3) % 4)) % 4;
		fseek(f, bih.OffBits, SEEK_SET);
		for (int i = 0; i < bih.Height; ++i)
		{
			fread(Pixels + i * bih.Width * 3, (size_t)1, (size_t)bih.Width * 3, f);
			fread(&pad, 1, padding, f);
		}
		//cout << "Test: wczytano" << endl;
		int size = GetFileSize();
		MessageBox::Show(size.ToString());
	}

	fclose(f);
}

void ReadMMSS(char* path)
{
	f = fopen(path, "rb");
	if (f != NULL)
	{
		fread(&msih, sizeof(MMSSInfoHeader), 1, f);
		if (msih.MMSSType != 21325)
		{
			fclose(f);
			return;
		}

		int filesize = GetFileSize();

		int rozmiar = filesize - msih.OffBits - (msih.ColorsUsed * 3);

		fseek(f, msih.OffBits, SEEK_SET);
		unsigned char* tempColors = new unsigned char[msih.ColorsUsed * 3];

		for (int i = 0; i < msih.ColorsUsed * 3; i++)
		{
			fread(tempColors + i, (size_t)sizeof(Byte), 1, f);
		}

		int counter = 0;

		for (int i = 0; i < msih.ColorsUsed * 3; i += 3)
		{
			ColorTable[counter].Red = (int)tempColors[i];
			ColorTable[counter].Green = (int)tempColors[i + 1];
			ColorTable[counter].Blue = (int)tempColors[i + 2];
			counter++;
		}

		unsigned int mallocSize2 = msih.Height * msih.Width * 3;
		Pixels2 = (unsigned char *)malloc(mallocSize2 * sizeof(unsigned char));
		unsigned char pad[4] = { 0 };
		unsigned int padding = (4 - ((msih.Width * 3) % 4)) % 4;
		fseek(f, bih.OffBits + (msih.ColorsUsed * 3), SEEK_SET);
		for (int i = 0; i < msih.Height; ++i)
		{
			fread(Pixels2 + i * msih.Width * 3, (size_t)1, (size_t)msih.Width * 3, f);
			fread(&pad, 1, padding, f);
		}
		/*
		fseek(f, msih.OffBits + (msih.ColorsUsed * 3), SEEK_SET);
		compressedIMG = new int[padding];
		for (int i = 0; i < padding; ++i)
		{
		fread(compressedIMG + i, (size_t)sizeof(Byte), 1, f);
		}*/
	}
	fclose(f);
}

unsigned char* decompress()
{
	int q = 0;
	unsigned char* decompressedIMG = new unsigned char[msih.Width*msih.Height];
	


	int length = sizeof(Pixels2) / sizeof(*Pixels2);

	for (int w = 0; w < length; w += 2)
	{
		Pixels2[w] -= 128;
	}

	int i = 0;

	//dopoki wszystkie bajty nie sa zdekompresowane
	while (i < length)
	{
		//kod pusty
		if (Pixels2[i] == -128)
		{
			i++;
		}
		//sekwencja powtarzajacych sie bajtow
		else if (Pixels2[i] < 0)
		{
			for (int j = 0; j<-(Pixels2[i] - 1); j++)
			{
				Pixels2[q++] = (int)Pixels2[i + 1];
			}
			i += 2;
		}
		//sekwencja roznych bajtow
		else
		{
			for (int j = 0; j<(Pixels2[i] + 1); j++)
			{
				Pixels2[q++] = (int)Pixels2[i + 1 + j];
			}
			i += Pixels2[i] + 2;
		}
	}
	return decompressedIMG;
}

int ConvertToMMSS::ReadAndPrepare(char* path)
{
	try
	{
		ReadBMP(path);
		t = MakeColorTable();
		loadMMSSHeader();
		return 0;
	}
	catch (exception ex)
	{
		System::String^ error = gcnew String(ex.what());
		MessageBox::Show(error);
		return -1;
	}
}

int* rawToColors(unsigned char* PixelsTable)//zamienia surowe piksele na tablice kolorów z numerami z color table
{
	int counter = 0;
	int* colors = new int[bih.Height*bih.Width];
	for (int i = 0; i < bih.Height*bih.Width * 3; i += 3)
	{
		for (int x = 0; x < t; x++)
		{
			if ((int)Pixels[i + 2] == ColorTable[x].Red && (int)Pixels[i + 1] == ColorTable[x].Green && (int)Pixels[i] == ColorTable[x].Blue)
			{
				colors[counter++] = x;
			}
		}
	}
	lengthOfColors = counter;
	return colors;
}

int PaethPredictor(int a, int b, int c)
{
	int p = a + b - c;
	int pa = Math::Abs(p - a);
	int pb = Math::Abs(p - b);
	int pc = Math::Abs(p - c);
	if (pa <= pb && pa <= pc)
	{
		return a;
	}
	else if (pb <= pc)
	{
		return b;
	}
	else
		return c;
}

int* getPredictor(int* colorsToProcess)
{
	int* output = new int[lengthOfColors];
	switch (predictorName)
	{
	case 0:
		output = colorsToProcess;
		break;
	case 1:
		output[0] = colorsToProcess[0];
		for (int i = 1; i < lengthOfColors; i++)
		{
			output[i] = colorsToProcess[i] - colorsToProcess[i - 1];
		}
		//sub
		break;
	case 2:
		for (int i = 0; i < bih.Width; i++)
		{
			output[i] = colorsToProcess[i];
		}
		for (int j = bih.Width; j < lengthOfColors; j++)
		{
			output[j] = colorsToProcess[j] - colorsToProcess[j - bih.Width];
		}
		//up
		break;
	case 3:
		for (int i = 0; i < bih.Width; i++)
		{
			output[i] = colorsToProcess[i];
		}
		for (int j = bih.Width; j < lengthOfColors; j++)
		{
			output[j] = colorsToProcess[j] - Math::Floor((colorsToProcess[j - 1] + colorsToProcess[j - bih.Width]) / 2);
		}
		//average
		break;
	case 4:
		for (int i = 0; i < bih.Width; ++i)
		{
			output[i] = colorsToProcess[i];
		}
		for (int j = bih.Width; j < lengthOfColors; ++j)
		{
			output[j] = output[j] - PaethPredictor(colorsToProcess[j],
				colorsToProcess[j - bih.Width],
				colorsToProcess[j - bih.Width - 1]);
		}
		//paeth
		break;
	}
	return output;
}

unsigned char* DecodePredictor(unsigned char* colorsToProcess)
{
	int outputSize = sizeof(colorsToProcess) / sizeof(*colorsToProcess);
	unsigned char* output = new unsigned char[outputSize];
	switch (msih.Compression)
	{
	case 0:
		output = colorsToProcess;
		break;
		//sub
	case 1:
		output[0] = colorsToProcess[0];
		for (int i = 1; i < outputSize; ++i)
		{
			output[i] = colorsToProcess[i] + colorsToProcess[i + 1];
		}
		break;
		//up
	case 2:
		for (int i = 0; i < msih.Width; ++i)
		{
			output[i] = colorsToProcess[i];
		}
		for (int j = msih.Width; j < outputSize; ++j)
		{
			output[j] = colorsToProcess[j] + colorsToProcess[j - msih.Width];
		}
		break;
		//average
	case 3:
		for (int i = 0; i < msih.Width; ++i)
		{
			output[i] = colorsToProcess[i];
		}
		for (int j = msih.Width; j < outputSize; ++j)
		{
			output[j] = colorsToProcess[j] + Math::Floor((colorsToProcess[j - 1] + colorsToProcess[j - msih.Width]) / 2);
		}
		break;
		//paeth
	case 4:
		for (int i = 0; i < msih.Width; ++i)
		{
			output[i] = colorsToProcess[i];
		}
		for (int j = msih.Width; j < outputSize; ++j)
		{
			output[j] = output[j] + PaethPredictor(colorsToProcess[j],
				colorsToProcess[j - bih.Width],
				colorsToProcess[j - bih.Width - 1]);
		}
		break;
	}
	return output;
}

unsigned char* compress()
{
	k = 0;
	unsigned char* ToSave = new unsigned char[bih.Height*bih.Width*2];
	int* colorsTemp = rawToColors(Pixels);
	int* colors = getPredictor(colorsTemp);
	int i = 0;

	//dopoki wszystkie bajty nie sa skompresowane
	while (i < lengthOfColors)
	{
		//sekwencja powtarzajacych sie bajtow
		if ((i < lengthOfColors - 1) &&
			(colors[i] == colors[i + 1]))
		{
			//zmierz dlugosc sekwencji
			int j = 0;
			while ((i + j < lengthOfColors - 1) &&
				(colors[i + j] == colors[i + j + 1]) &&
				(j < 127))
			{
				j++;
			}
			//wypisz spakowana sekwencje
			ToSave[k++] = -j + 128;
			ToSave[k++] = (int)colors[i + j];

			//przesun wskaznik o dlugosc sekwencji
			i += (j + 1);
		}
		//sekwencja roznych bajtow
		else
		{
			//zmierz dlugosc sekwencji
			int j = 0;
			while ((i + j < lengthOfColors - 1) &&
				(colors[i + j] != colors[j + i + 1]) &&
				(j < 128))
			{
				j++;
			}
			//dodaj jeszcze koncowke
			if ((i + j == lengthOfColors - 1) &&
				(j < 128))
			{
				j++;
			}
			//wypisz spakowana sekwencje
			ToSave[k++] = (j-1) + 128;
			for (int k = 0; k<j; k++)
			{
				ToSave[k++] = (int)colors[i + k];
			}
			//przesun wskaznik o dlugosc sekwencji
			i += j;
		}
	}				
	return ToSave;
}

int ConvertToMMSS::saveFile(char* path)
{
	unsigned char* ToSave = new unsigned char[bih.Height*bih.Width];
	
	int j = 0;
	unsigned char* ColorsToSave = new unsigned char[t * 3];

	for (int i = 0; i < t; i++)
	{
		ColorsToSave[j++] = ColorTable[i].Red;
		ColorsToSave[j++] = ColorTable[i].Green;
		ColorsToSave[j++] = ColorTable[i].Blue;
	}

	ToSave = compress();
	
	FILE* s;
	if (fopen_s(&s, path, "wb") != 0) return 0;
	fwrite(&msih.MMSSType, (size_t) sizeof(msih.MMSSType), (size_t)1, s); // 2 bytes

	fwrite(&msih.OffBits, (size_t) sizeof(msih.OffBits), (size_t)1, s);  // 4 bytes
	fwrite(&msih.HeaderSize, (size_t) sizeof(msih.HeaderSize), (size_t)1, s); // 4 bytes
	fwrite(&msih.Width, (size_t) sizeof(msih.Width), (size_t)1, s); // 4 bytes
	fwrite(&msih.Height, (size_t) sizeof(msih.Height), (size_t)1, s); // 4 bytes

	fwrite(&msih.BitsPerPxl, (size_t) sizeof(msih.BitsPerPxl), (size_t)1, s); // 2 bytes
	fwrite(&msih.Compression, (size_t) sizeof(bih.Compression), (size_t)1, s); // 4 bytes
	fwrite(&msih.ColorsUsed, (size_t) sizeof(msih.ColorsUsed), (size_t)1, s); // 4 bytes
	fwrite(&msih.ColorIndicator, (size_t) sizeof(msih.BitsPerPxl), (size_t)1, s); // 2 bytes
	
	
	unsigned int padding = (4 - ((bih.Width * 3) % 4)) % 4;
	fseek(s, msih.OffBits, SEEK_SET);
	for (int cc = 0; cc < j; cc++)
	{
		fwrite(ColorsToSave + cc, (size_t)sizeof(Byte), (size_t)1, s);
	}
	fseek(s, msih.OffBits + j, SEEK_SET);
	for (int q = 0; q < k; q++)
	{
		fwrite(ToSave + q, (size_t)sizeof(Byte), (size_t)1, s);
	}
	
	//fwrite("\0", 1, padding, s); NIE WIEM CO Z TYM ZROBIC, ZOSTAWIAM
	fclose(s);
	return 0;
}

int ConvertToBMP::ReadAndPrepare(char* path)
{
	try
	{
		ReadMMSS(path);
		loadBMPHeader();
		return 0;
	}
	catch (exception exbmp)
	{
		System::String^ error = gcnew String(exbmp.what());
		MessageBox::Show(error);
		return -1;
	}
}

int ConvertToBMP::saveFile(char* path)
{
	int colorCount = 0;
	int i;
	unsigned char* ToRead = new unsigned char[msih.Height*msih.Width];
	int k = 0;
	int j = 0;
	unsigned char* ColorsToRead = new unsigned char[msih.ColorsUsed * 3];
	unsigned char* IMG = new unsigned char[msih.Width*msih.Height];
	IMG = decompress();
	unsigned char* decodedPredictors = DecodePredictor(IMG);

	FILE* s;
	if (fopen_s(&s, path, "wb") != 0) return 0;
	fwrite(&bih.BMPType, (size_t) sizeof(bih.BMPType), (size_t)1, s); // 2 bytes
	fwrite(&bih.FileSize, (size_t) sizeof(bih.FileSize), (size_t)1, s);
	fwrite(&bih.Reserved1, (size_t) sizeof(bih.Reserved1), (size_t)1, s);
	fwrite(&bih.Reserved2, (size_t) sizeof(bih.Reserved2), (size_t)1, s);
	fwrite(&bih.OffBits, (size_t) sizeof(bih.OffBits), (size_t)1, s);  // 4 bytes
	fwrite(&bih.HeaderSize, (size_t) sizeof(bih.HeaderSize), (size_t)1, s); // 4 bytes
	fwrite(&bih.Width, (size_t) sizeof(bih.Width), (size_t)1, s); // 4 bytes
	fwrite(&bih.Height, (size_t) sizeof(bih.Height), (size_t)1, s); // 4 bytes
	fwrite(&bih.Planes, (size_t) sizeof(bih.Planes), (size_t)1, s);
	fwrite(&bih.BitsPerPxl, (size_t) sizeof(bih.BitsPerPxl), (size_t)1, s); // 2 bytes
	fwrite(&bih.Compression, (size_t) sizeof(bih.Compression), (size_t)1, s); 
	fwrite(&bih.ImageSize, (size_t) sizeof(bih.ImageSize), (size_t)1, s);
	fwrite(&bih.XPixels, (size_t) sizeof(bih.XPixels), (size_t)1, s);
	fwrite(&bih.YPixels, (size_t) sizeof(bih.YPixels), (size_t)1, s);
	fwrite(&bih.ColorsUsed, (size_t) sizeof(bih.ColorsUsed), (size_t)1, s); // 4 bytes
	fwrite(&bih.ColorsImportant, (size_t) sizeof(bih.ColorsImportant), (size_t)1, s);


	unsigned int padding = (4 - ((msih.Width * 3) % 4)) % 4;

	fseek(s, bih.OffBits, SEEK_SET);

	for (k = 0; k < msih.Height*msih.Width; k++)
	{
		unsigned char* test = new unsigned char[3];
		test[0] = ColorTable[decodedPredictors[k]].Red;
		test[1] = ColorTable[decodedPredictors[k]].Green;
		test[2] = ColorTable[decodedPredictors[k]].Blue;
		fwrite(&test, (size_t)sizeof(test), (size_t)1, s);
		/*fwrite(&ColorTable[decodedPredictors[k]].Red, (size_t)sizeof(Byte), (size_t)1, s);
		fwrite(&ColorTable[decodedPredictors[k]].Green, (size_t)sizeof(Byte), (size_t)1, s);
		fwrite(&ColorTable[decodedPredictors[k]].Blue, (size_t)sizeof(Byte), (size_t)1, s);*/
		if (k % msih.Width == 0)
			fwrite("\0", 1, padding, s);
	}
	
		/*
	for (int cc = 0; cc < j; cc++)
	{
		fwrite(ColorsToSave + cc, (size_t)sizeof(Byte), (size_t)1, s);
	}
	fseek(s, msih.OffBits + j, SEEK_SET);
	for (int q = 0; q < k; q++)
	{
		fwrite(ToSave + q, (size_t)sizeof(Byte), (size_t)1, s);
	}*/

	//fwrite("\0", 1, padding, s); NIE WIEM CO Z TYM ZROBIC, ZOSTAWIAM
	fclose(s);
	return 0;
}

infoAboutImage info::GetInfo(char* path)
{
	infoAboutImage x;
	x.width = bih.Width;
	x.height = bih.Height;
	x.colors = t;
	return x;
}

[STAThread]
void main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Konsolowy::MyForm form;
	Application::Run(%form);
}