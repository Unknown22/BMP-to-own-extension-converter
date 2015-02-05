#include "MyForm.h"
#include "MainHeader.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <msclr/marshal_cppstd.h>

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
	unsigned short BMPType;			// 0x42D2
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
#pragma pack()

FILE* f;
unsigned char* Pixels;
BMPInfoHeader bih;
RGBPixel ColorTable[64];
int t = 0; //indeks w tabeli kolorów


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
		cout << "Test: wczytano" << endl;
	}
	fclose(f);
}

int MakeColorTable()
{
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

int ConvertToMMSS::saveFile(char* path)
{
	int lastColor = -1;
	int colorCount = 0;
	int i;
	unsigned char* ToSave = new unsigned char[bih.Height*bih.Width];
	int k = 0;
	int j = 0;
	unsigned char* ColorsToSave = new unsigned char[t * 3];

	for (i = 0; i < t; i++)
	{
		ColorsToSave[j++] = ColorTable[i].Red;
		ColorsToSave[j++] = ColorTable[i].Green;
		ColorsToSave[j++] = ColorTable[i].Blue;
	}

	for (i = 0; i < bih.Height*bih.Width * 3; i += 3)
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

	FILE* s;
	if (fopen_s(&s, path, "wb") != 0) return 0;
	fwrite(&bih.BMPType, (size_t) sizeof(bih.BMPType), (size_t)1, s);
	fwrite(&bih.FileSize, (size_t) sizeof(bih.FileSize), (size_t)1, s);
	fwrite(&bih.Reserved1, (size_t) sizeof(bih.Reserved1), (size_t)1, s);
	fwrite(&bih.Reserved2, (size_t) sizeof(bih.Reserved2), (size_t)1, s);
	fwrite(&bih.OffBits, (size_t) sizeof(bih.OffBits), (size_t)1, s);
	fwrite(&bih.HeaderSize, (size_t) sizeof(bih.HeaderSize), (size_t)1, s);
	fwrite(&bih.Width, (size_t) sizeof(bih.Width), (size_t)1, s);
	fwrite(&bih.Height, (size_t) sizeof(bih.Height), (size_t)1, s);
	fwrite(&bih.Planes, (size_t) sizeof(bih.Planes), (size_t)1, s);
	fwrite(&bih.BitsPerPxl, (size_t) sizeof(bih.BitsPerPxl), (size_t)1, s);
	fwrite(&bih.Compression, (size_t) sizeof(bih.Compression), (size_t)1, s);
	fwrite(&bih.ImageSize, (size_t) sizeof(bih.ImageSize), (size_t)1, s);
	fwrite(&bih.XPixels, (size_t) sizeof(bih.XPixels), (size_t)1, s);
	fwrite(&bih.YPixels, (size_t) sizeof(bih.YPixels), (size_t)1, s);
	fwrite(&bih.ColorsUsed, (size_t) sizeof(bih.ColorsUsed), (size_t)1, s);
	fwrite(&bih.ColorsImportant, (size_t) sizeof(bih.ColorsImportant), (size_t)1, s);
	
	
	unsigned int padding = (4 - ((bih.Width * 3) % 4)) % 4;
	fseek(s, bih.OffBits, SEEK_SET);
	for (int cc = 0; cc < j; cc++)
	{
		fwrite(ColorsToSave + cc, (size_t)sizeof(Byte), (size_t)1, s);
	}
	fseek(s, bih.OffBits + j, SEEK_SET);
	for (int q = 0; q < k; q++)
	{
		fwrite(ToSave + q, (size_t)sizeof(Byte), (size_t)1, s);
	}
	
		//fwrite("\0", 1, padding, s); NIE WIEM CO Z TYM ZROBIC, ZOSTAWIAM
	fclose(s);
	return 0;
}

int ConvertToMMSS::ReadAndPrepare(char* path)
{
	try
	{
		ReadBMP(path);
		t = MakeColorTable();
		return 0;
	}
	catch(exception ex)
	{
		System::String^ error = gcnew String(ex.what());
		MessageBox::Show(error);
		return -1;
	}
}

int ConvertToBMP::ReadAndPrepare(char* path)
{
	MessageBox::Show("KK1");
	return 0;
}

int ConvertToBMP::saveFile(char* path)
{
	MessageBox::Show("KK2");
	return 0;
}

[STAThread]
void main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Konsolowy::MyForm form;
	Application::Run(%form);
}