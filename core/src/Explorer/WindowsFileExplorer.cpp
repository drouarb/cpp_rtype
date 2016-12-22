//
// Created by greg on 21/12/2016.
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <stdexcept>

#pragma comment(lib, "User32.lib")
#include "Explorer/WindowsFileExplorer.hh"

void WindowsFileExplorer::loadFolder(const std::string &path) {
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;

    // If the directory is not specified as a command-line argument,
    // print usage.

    // Check that the input path plus 3 is not longer than MAX_PATH.
    // Three characters are for the "\*" plus NULL appended below.

    StringCchLength(path.c_str(), MAX_PATH, &length_of_arg);

    if (length_of_arg > (MAX_PATH - 3))
    {
        _tprintf(TEXT("\nDirectory path is too long.\n"));
    }

    // Prepare string for use with FindFile functions.  First, copy the
    // string to a buffer, then append '\*' to the directory name.

    StringCchCopy(szDir, MAX_PATH, path.c_str());
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    // Find the first file in the directory.

    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        throw std::runtime_error("Excepted value when opening directory " + path);
    }

    // List all the files in the directory with some info about them.


    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
        }
        else
        {
            File file;
            file.name = "/" + std::string(ffd.cFileName);
            this->fileList.push_back(file);
        }
    }
    while (FindNextFile(hFind, &ffd) != 0);

    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
    }

    FindClose(hFind);
}

std::vector<IExplorer::File> WindowsFileExplorer::getFiles() {
    return this->fileList;
}
