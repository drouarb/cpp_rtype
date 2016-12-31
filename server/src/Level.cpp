
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


    JSON::JsonArr &gamedata = static_cast<JSON::JsonArr &>(root.GetObj("gamedata"));
    std::list<JSON::IJson *> &gdlist = gamedata.GetList();

    for (JSON::IJson *s : gdlist) {
        JSON::JsonObj *obj = static_cast<JSON::JsonObj *>(s);

        std::pair<std::string, std::string> newData;
        newData.first = static_cast<JSON::JsonStr &>(obj->GetObj("background")).Get();
        newData.second = static_cast<JSON::JsonStr &>(obj->GetObj("music")).Get();
        auto time = static_cast<round_t >(std::stoi(static_cast<JSON::JsonStr &>(obj->GetObj("time")).Get()));

        this->gamedata[time] = newData;
    }

    end = 0;
    for (auto& entry : this->spawns)
    {
        if (entry.first > end)
            end = entry.first;
    }
}

server::Level::~Level() {}

const std::vector<server::Spawn> *server::Level::getNewSpawns(server::round_t tick) const {
    try
    {
        return &this->spawns.at(tick);
    }
    catch (std::out_of_range &e)
    {
        return nullptr;
    }
}

const std::pair<std::string, std::string> *server::Level::getNewData(server::round_t tick) const
{
    try
    {
        return &this->gamedata.at(tick);
    }
    catch (std::out_of_range &e)
    {
        return nullptr;
    }
}

bool server::Level::isOver(round_t tick) const
{
    return (tick > end);
}