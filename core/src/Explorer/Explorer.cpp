//
// Created by greg on 21/12/2016.
//

#include <Explorer/IExplorer.hh>

#ifdef _WIN32
#include <Explorer/WindowsFileExplorer.hh>
#else
#include <Explorer/FileExplorer.hh>
#endif


IExplorer *IExplorer::getInstance() {
#ifdef _WIN32
    return new WindowsFileExplorer();
#else
    return new FolderExplorer("");
#endif
}
