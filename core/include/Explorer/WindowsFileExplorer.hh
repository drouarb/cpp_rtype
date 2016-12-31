//
// Created by greg on 21/12/2016.
//

#ifndef CPP_RTYPE_WINDOWSFILEEXPLORER_HH
#define CPP_RTYPE_WINDOWSFILEEXPLORER_HH


#include "IExplorer.hh"

class WindowsFileExplorer : public IExplorer {
private:
    std::vector<File> fileList;

public:
    void loadFolder(const std::string &path) override;

    std::vector<File> getFiles() override;
};


#endif //CPP_RTYPE_WINDOWSFILEEXPLORER_HH
