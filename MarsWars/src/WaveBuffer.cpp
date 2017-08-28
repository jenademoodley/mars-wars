#include "WaveBuffer.h"
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

WaveBuffer::WaveBuffer(char * filename)
{
    ok = false;
    buffer = 0;
    HInstance = GetModuleHandle(0);

    ifstream infile(filename, ios::binary);

    if (!infile)
    {
         std::cout << "Can't Find File: "<< filename << std::endl;
        return;
    }

    infile.seekg (0, ios::end);//File Length
    int length = infile.tellg();
    buffer = new char[length];//Allocate Memory
    infile.seekg (0, ios::beg);//Position of File
    infile.read (buffer,length);//Read File

    infile.close();
    ok = true;
}

WaveBuffer::~WaveBuffer()
{
    PlaySound(NULL, 0, 0);//Stop Currently Playing Sound
    delete [] buffer;//Delete Buffer
}

void WaveBuffer::play(bool async)
{
        PlaySound(buffer, HInstance, SND_MEMORY | SND_ASYNC);
}

bool WaveBuffer::isok()
{
    return ok;
}
