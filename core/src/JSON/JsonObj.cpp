#include <iostream>
#include "JsonObj.hpp"
#include "JsonStr.hpp"
#include "JsonArr.hpp"

JSON::JsonObj::JsonObj()
{ }

JSON::JsonObj::JsonObj(JsonObj const &other)
{
    for (std::map<std::string, IJson *>::const_iterator it = other.objs.begin();
         it != other.objs.end(); ++it)
        {
            objs.insert(std::pair<std::string, IJson *>(it->first, it->second->Clone()));
        }
}

JSON::JsonObj::~JsonObj()
{
    for (std::map<std::string, IJson *>::iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            delete (it->second);
        }
}

void
JSON::JsonObj::AddObj(std::string const &key, IJson const &val)
{
    objs.insert(std::pair<std::string, IJson *>(key, val.Clone()));
}

JSON::IJson const &
JSON::JsonObj::GetObj(std::string const &key) const
{
    for (std::map<std::string, IJson *>::const_iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            if (it->first == key)
                return (*it->second);
        }
    throw (std::invalid_argument("JsonObj::GetObj wrong key"));
}

JSON::IJson &
JSON::JsonObj::GetObj(std::string const &key)
{
    for (std::map<std::string, IJson *>::iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            if (it->first == key)
                return (*it->second);
        }
    throw (std::invalid_argument("JsonObj::GetObj wrong key"));
}

std::map<std::string, JSON::IJson *> const &
JSON::JsonObj::GetMap() const
{
    return (objs);
}

std::string const &
JSON::JsonObj::Serialize()
{
    return (Serialize(0));
}

std::string const &
JSON::JsonObj::Serialize(int level)
{
    serialized = chars('\t', level) + "{\n";
    for (std::map<std::string, IJson *>::iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            if (it != objs.begin())
                serialized += ",\n";
            serialized += chars('\t', level + 1) + it->first + ": ";
            if (it->second->Newline())
                serialized += "\n";
            serialized += it->second->Serialize(it->second->Newline() ? level + 1 : 0);
        }
    serialized += "\n" + chars('\t', level) + "}";
    return (serialized);
}

int
JSON::JsonObj::ParseFrom(std::string const &text)
{
    int len;
    int idx;
    int end;
    std::string key;

    serialized = text;

    len = text.length();
    idx = txtAdv(text, "\n \t{", 0, len);
    while (idx < len && text[idx] != '}')
        {
            idx = txtAdv(text, ",\n \t", idx, len);
            end = txtUpto(text, ':', idx, len);
            key = text.substr(idx, end - idx);
            idx = txtAdv(text, ": \t\n", end, len);
            if (idx < len && text[idx] == '{')
                AddObj(key, JsonObj());
            else if (idx < len && text[idx] == '[')
                AddObj(key, JsonArr());
            else
                AddObj(key, JsonStr());
            idx += GetObj(key).ParseFrom(text.substr(idx, len - idx));
            idx = txtAdv(text, ",\n \t", idx, len);
        }
    idx = txtAdv(text, ",\n \t}", idx, len);

    return (idx);
}

void
JSON::JsonObj::Clear()
{
    for (std::map<std::string, IJson *>::iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            delete (it->second);
        }
    objs.clear();
}

bool
JSON::JsonObj::Newline() const
{
    return (true);
}

JSON::IJson *
JSON::JsonObj::Clone() const
{
    return (new JsonObj(*this));
}
