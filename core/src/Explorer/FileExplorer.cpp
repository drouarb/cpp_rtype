//
// Created by greg on 07/12/2016.
//

#include <dirent.h>
#include <stdexcept>
#include <iostream>
#include "Explorer/FileExplorer.hh"

FolderExplorer::FolderExplorer(const std::string &path) : path(path) {}

void FolderExplorer::loadFolder(const std::string &path) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            File file;
            file.name = ent->d_name;
            this->fileList.push_back(file);
        }
        closedir(dir);
    } else {
        throw std::runtime_error("Cannot open " + path);
    }
}

std::vector<IExplorer::File> FolderExplorer::getFiles() {
    return this->fileList;
}