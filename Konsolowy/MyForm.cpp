#include "MyForm.h"
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
		for (unsigned int i = 0; i < bih.Height; ++i)
		{
			fread(Pixels + i * bih.Width * 3, (size_t)1, (size_t)bih.Width * 3, f);
			fread(&pad, 1, padding, f);
		}
		cout << "Test: wczytano" << endl;
	}
	fclose(f);
}

int saveFileClass::saveFile(char* path)
{

	int i;
	unsigned char* ToSave = new unsigned char[bih.Height*bih.Width];
	int k = 0;
	int j = 0;
	unsigned char* ColorsToSave = new unsigned char[t * 3];
	//ofstream fout(path);
	//if (t < 10)
	//{
	//	//fout << "0" << t;
	//}
	//else
	//{
	//	fout << t;
	//}
	//ToSave[k++] = t;
	for (i = 0; i < t; i++)
	{
		//if (ColorTable[i].Red < 100)
		//{
		//	//fout << "0";
		//	/*if (ColorTable[i].Red < 10)
		//		fout << "0";*/
		//}

		//fout << ColorTable[i].Red;
		ColorsToSave[j++] = ColorTable[i].Red;
		/*if (ColorTable[i].Green < 100)
		{
		fout << "0";
		if (ColorTable[i].Green < 10)
		fout << "0";
		}*/
		ColorsToSave[j++] = ColorTable[i].Green;
		/*if (ColorTable[i].Blue < 100)
		{
		fout << "0";
		if (ColorTable[i].Blue < 10)
		fout << "0";
		}*/
		ColorsToSave[j++] = ColorTable[i].Blue;
	}
	for (i = 0; i < bih.Height*bih.Width * 3; i += 3)
	{
		//fout << (int)Pixels[i + 2] << (int)Pixels[i + 1] << (int)Pixels[i];
		for (int x = 0; x < t; x++)
		{
			if ((int)Pixels[i + 2] == ColorTable[x].Red &&
				(int)Pixels[i + 1] == ColorTable[x].Green &&
				(int)Pixels[i] == ColorTable[x].Blue)
			{
				ToSave[k++] = x;
				//fout << x;
				/*if (t < 10)
				{
				fout << x;
				}
				else
				{
				if (x < 10)
				{
				fout << "0";
				}
				fout << x;
				}*/
			}
		}
	}

	FILE* s;
	if (fopen_s(&s, path, "wb") != 0) return 0;/*
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
	fwrite(&bih.ColorsImportant, (size_t) sizeof(bih.ColorsImportant), (size_t)1, s);*/

	unsigned int padding = (4 - ((bih.Width * 3) % 4)) % 4;
	fseek(s, bih.OffBits, SEEK_SET);
	for (unsigned int cc = 0; cc < t * 3; cc++)
	{
		fwrite(ColorsToSave + cc, (size_t)bih.Width, (size_t)1, s);
	}
	fseek(s, bih.OffBits + t * 3, SEEK_SET);
	for (unsigned int a = 0; a < bih.Height; ++a)
	{
		fwrite(ToSave + a * bih.Width, (size_t)bih.Width, (size_t)1, s);
		fwrite("\0", 1, padding, s);
	}
	fclose(s);
	return 0;
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
	/*
	for (int i = 0; i < t; i++)
	{
	cout << i << ". " << ColorTable[i].Red << ":" << ColorTable[i].Green << ":" << ColorTable[i].Blue << endl;
	}*/
	return t;
}

int konwerterClass::konwerter(char* path)
{
	ReadBMP(path);

	for (int x = 0; x < bih.Height*bih.Width * 3; x += 3)
	{
		//cout << (int)Pixels[x + 2] << ":" << (int)Pixels[x + 1] << ":" << (int)Pixels[x] << " ";
	}
	int t = MakeColorTable();
	//SaveFile(t);

	//cout << endl;
	return 0;
}

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Konsolowy::MyForm form;
	Application::Run(%form);
}