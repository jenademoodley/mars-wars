#include "PlayFile.h"
#include <windows.h>
#include <mmsystem.h>
 #include <string>

PlayFile::PlayFile(std::string name)
{
    const char * c = name.c_str();
    PlaySound(TEXT(c), NULL, SND_ASYNC);//SND_ASYNC
}

PlayFile::~PlayFile()
{
    //dtor
}
