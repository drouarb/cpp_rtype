
#include <chrono>
#include <thread>
#include <iostream>
#include "Explorer/FileExplorer.hh"
#include "Core.hh"
#include "Game.hh"

server::Core::Core(const std::string &path) {
    FolderExplorer fileExplorer(path);

    fileExplorer.loadFolder();
    this->networkManager = new NetworkManager(this);
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
    if (levels.empty()) {
        std::cerr << "No levels. Aborting." << std::endl;
        return;
    }
    run();
}

void server::Core::run() {
    Game game(1, levels[0]);

    Client client(1);
    game.newPlayer(&client);
    client.getController()->playMove(10, 1);

    for (round_t i = 0; i < 20; ++i)
    {
        std::cout << "- round " << std::to_string(i) << " - - - - - - - - - - - - - - - - - -" << std::endl;
        game.tick(i);
    }
}


