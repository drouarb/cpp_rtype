//
// Created by greg on 07/12/2016.
//

#ifndef CPP_RTYPE_UNIXEXPLORER_HH
#define CPP_RTYPE_UNIXEXPLORER_HH

#include "IExplorer.hh"

class FolderExplorer : public IExplorer {
private:
    std::string path;
    std::vector<File> fileList;
public:
    FolderExplorer(const std::string &path);

    void loadFolder(const std::string &path) override;

    std::vector<File> getFiles() override;
};

#endif //CPP_RTYPE_UNIXEXPLORER_HH
