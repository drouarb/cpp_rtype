
#include <chrono>
#include <thread>
#include <iostream>
#include "Explorer/FileExplorer.hh"
#include "Core.hh"

server::Core::Core(const std::string &path) {
    FolderExplorer fileExplorer(path);

    fileExplorer.loadFolder();
    const std::vector<IExplorer::File> &vector = fileExplorer.getFiles();
    for (auto f : vector) {
        if (f.name.find(".json") == std::string::npos) {
            continue;
        }
        try {
            this->levels.push_back(Level(path + f.name));
        } catch (std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
        catch (std::exception &e) {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
}


