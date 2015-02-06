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

void GetPredictor::getPr(int num)
{
	predictorName = num;
}

void loadMMSSHeader()
{
	msih.MMSSType = (unsigned short)21325;
	msih.OffBits = (unsigned int)24;
	msih.HeaderSize = (unsigned int)18;
	msih.Width = bih.Width;
	msih.Height = bih.Height;
	msih.BitsPerPxl = (unsigned short)6;
	msih.ColorsUsed = (unsigned int)t;
	//msih.Compression = x; //typ kompresji czyli numer predyktora do dodania

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

		unsigned int mallocSize = msih.Height * msih.Width * 3;
		Pixels = (unsigned char *)malloc(mallocSize * sizeof(unsigned char));
		unsigned char pad[4] = { 0 };
		unsigned int padding = (4 - ((msih.Width * 3) % 4)) % 4;
		fseek(f, msih.OffBits, SEEK_SET);
		for (int i = 0; i < msih.Height; ++i)
		{
			fread(Pixels + i * msih.Width * 3, (size_t)1, (size_t)msih.Width * 3, f);
			fread(&pad, 1, padding, f);
		}
		//cout << "Test: wczytano" << endl;
	}
	fclose(f);
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
	}

	fclose(f);
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
			output[i] = colorsToProcess[i] - colorsToProcess[i-1]+64; //+64 zeby na wyjsciu byly tylko dodatnie wartosci, przy dekodowaniu trzeba odjac 64
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
			output[j] = colorsToProcess[j] - colorsToProcess[j - bih.Width] + 64; //jak wyzej
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
			output[j] = colorsToProcess[j] - Math::Floor((colorsToProcess[j - 1] + colorsToProcess[j - bih.Width]) / 2) + 64; //jak wyzej
		}
		//average
		break;
	case 4:
		for (int i = 0; i < bih.Width; ++i)
		{
			output[i] = colorsToProcess[i] + 64; //jak wyzej
		}
		for (int j = bih.Width; j < lengthOfColors; ++j)
		{
			output[j] = PaethPredictor(colorsToProcess[j],
									colorsToProcess[j-bih.Width],
									colorsToProcess[j - bih.Width - 1]) + 64; //jak wyzej
		}
		//paeth
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
	int lastColor = colors[0];
	int colorCount = 0;
	
	for (int q = 0; q < lengthOfColors; q++){
		if (colors[q] != lastColor)
		{

			//nowy kolor
			//Przy dekodowaniu braæ 1-colorCount
			ToSave[k++] = colorCount;
			ToSave[k++] = lastColor;
			colorCount = 0;
			lastColor = colors[q];
		}
		else
		{
			//stary kolor
			if (colorCount < 128)
			{
				colorCount++;
			}
			else
			{
				//Przy dekodowaniu braæ 1-colorCount
				ToSave[k++] = colorCount;
				ToSave[k++] = lastColor;
				colorCount = 0;
			}
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
	//fwrite(&msih.Compression, (size_t) sizeof(bih.Compression), (size_t)1, s); //od odkomentowania po dodaniu numeru predyktora
	fwrite(&msih.ColorsUsed, (size_t) sizeof(msih.ColorsUsed), (size_t)1, s); // 4 bytes
	
	
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

int ConvertToBMP::saveFile(char* path) //trzeba zedytowaæ, ¿eby dekodowa³o ByteRun
{
	/*
	int lastColor = -1;
	int colorCount = 0;
	int i;
	unsigned char* ToSave = new unsigned char[msih.Height*msih.Width];
	int k = 0;
	int j = 0;
	unsigned char* ColorsToSave = new unsigned char[msih.ColorsUsed * 3];*/

	/*
	for (i = 0; i < t; i++)
	{
		ColorsToSave[j++] = ColorTable[i].Red;
		ColorsToSave[j++] = ColorTable[i].Green;
		ColorsToSave[j++] = ColorTable[i].Blue;
	}

	for (i = 0; i < msih.Height*msih.Width * 3; i += 3)
	{
		for (int x = 0; x < t; x++)
		{
			if ((int)Pixels[i + 2] == ColorTable[x].Red && (int)Pixels[i + 1] == ColorTable[x].Green && (int)Pixels[i] == ColorTable[x].Blue)
			{

				if (lastColor == -1)
				{
					lastColor = x;
					colorCount = 0;
				}
				else
				{
					if (x != lastColor)
					{

						//nowy kolor
						//Przy dekodowaniu braæ 1-colorCount
						ToSave[k++] = colorCount;
						ToSave[k++] = lastColor;
						colorCount = 0;
						lastColor = x;
					}
					else
					{
						//stary kolor
						if (colorCount < 128)
						{
							colorCount++;
						}
						else
						{
							//Przy dekodowaniu braæ 1-colorCount
							ToSave[k++] = colorCount;
							ToSave[k++] = lastColor;
							colorCount = 0;
						}
					}
				}
			}
		}
	}
	*/

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
	fwrite(&bih.Compression, (size_t) sizeof(bih.Compression), (size_t)1, s); //od odkomentowania po dodaniu numeru predyktora
	fwrite(&bih.ImageSize, (size_t) sizeof(bih.ImageSize), (size_t)1, s);
	fwrite(&bih.XPixels, (size_t) sizeof(bih.XPixels), (size_t)1, s);
	fwrite(&bih.YPixels, (size_t) sizeof(bih.YPixels), (size_t)1, s);
	fwrite(&bih.ColorsUsed, (size_t) sizeof(bih.ColorsUsed), (size_t)1, s); // 4 bytes
	fwrite(&bih.ColorsImportant, (size_t) sizeof(bih.ColorsImportant), (size_t)1, s);


	unsigned int padding = (4 - ((bih.Width * 3) % 4)) % 4;
	/*
	fseek(s, bih.OffBits, SEEK_SET);
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