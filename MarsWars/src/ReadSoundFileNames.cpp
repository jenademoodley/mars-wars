#include "ReadSoundFileNames.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

ReadSoundFileNames::ReadSoundFileNames(string folder)
{
    char search_path[200];
    sprintf(search_path, "%s/*.*", folder.c_str());
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path, &fd);
    if(hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
            {
                names.push_back(fd.cFileName);
            }
        } while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
}

ReadSoundFileNames::~ReadSoundFileNames()
{
    //dtor
}

void ReadSoundFileNames::shuffleNames()
{
    random_shuffle (names.begin(), names.end());
}

vector<string> ReadSoundFileNames::getNames()
{
    return names;
}
