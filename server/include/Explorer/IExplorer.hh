//
// Created by greg on 07/12/2016.
//

#ifndef CPP_RTYPE_IEXPLORER_HH
#define CPP_RTYPE_IEXPLORER_HH

#include <vector>
#include <string>

class IExplorer {
public:
    struct File {
        std::string name;
    };

public:
    virtual void loadFolder()= 0;

    virtual std::vector<File> getFiles()= 0;
};

#endif //CPP_RTYPE_IEXPLORER_HH
