#pragma once
class ConvertToMMSS
{
public:
	int ReadAndPrepare(char* path);
	int saveFile(char* path);
};

class ConvertToBMP
{
public:
	int ReadAndPrepare(char* path);
	int saveFile(char* path);
};

struct infoAboutImage
{
	int width;
	int height;
	int colors;
};

class info
{
public:
	infoAboutImage GetInfo(char* path);
};