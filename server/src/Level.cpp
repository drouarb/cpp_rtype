
#include <fstream>
#include "Level.hh"
#include <JSON/JsonParser.hpp>
#include <JSON/JsonArr.hpp>

server::Level::Level(const std::string &filepath) {

    JSON::JsonObj root;

    std::ifstream ifs(filepath.c_str());

    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot find " + filepath);
    }

    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );


    root.ParseFrom(content);
    JSON::JsonStr &str = static_cast<JSON::JsonStr &>(root.GetObj("name"));
    this->name = str.Get();

    JSON::JsonArr &spawns = static_cast<JSON::JsonArr &>(root.GetObj("spawns"));
    std::list<JSON::IJson *> &list = spawns.GetList();

    for (JSON::IJson *s : list) {
        JSON::JsonObj *obj = static_cast<JSON::JsonObj *>(s);

        Spawn spawn;
        spawn.dlName = static_cast<JSON::JsonStr &>(obj->GetObj("dlName")).Get();
        spawn.time = static_cast<round_t >(std::stoi(static_cast<JSON::JsonStr &>(obj->GetObj("time")).Get()));
        spawn.posX = std::stoi(static_cast<JSON::JsonStr &>(obj->GetObj("posX")).Get());
        spawn.posY = std::stoi(static_cast<JSON::JsonStr &>(obj->GetObj("posY")).Get());

        this->spawns[spawn.time].push_back(spawn);
    }

    end = 0;
    for (auto& entry : this->spawns)
    {
        if (entry.first > end)
            end = entry.first;
    }

    JSON::JsonObj &jsonObj = static_cast<JSON::JsonObj &>(root.GetObj("boss"));
    
    Spawn spawn;
    spawn.dlName = static_cast<JSON::JsonStr &>(jsonObj.GetObj("dlName")).Get();
    spawn.time = static_cast<round_t >(std::stoi(static_cast<JSON::JsonStr &>(jsonObj.GetObj("time")).Get()));
    spawn.posX = std::stoi(static_cast<JSON::JsonStr &>(jsonObj.GetObj("posX")).Get());
    spawn.posY = std::stoi(static_cast<JSON::JsonStr &>(jsonObj.GetObj("posY")).Get());
    this->boss.first = spawn.time;
    this->boss.second = spawn;
}

server::Level::~Level() {}

const std::vector<server::Spawn> *server::Level::getNewSpawns(server::round_t tick) const {
    try {
        return &this->spawns.at(tick);
    } catch (std::out_of_range &e) {
        return nullptr;
    }
}

bool server::Level::isOver(round_t tick) const
{
    return (tick > end);
}

