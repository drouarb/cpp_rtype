#include "JsonArr.hpp"
#include "JsonObj.hpp"
#include "JsonStr.hpp"

JSON::JsonArr::JsonArr()
{ }

JSON::JsonArr::JsonArr(JsonArr const &other)
{
    for (std::list<IJson *>::const_iterator it = other.objs.begin();
         it != other.objs.end(); ++it)
        {
            objs.push_front((*it)->Clone());
        }
}

JSON::IJson &
JSON::JsonArr::operator[](int index)
{
    std::list<IJson *>::iterator it = objs.begin();
    for (int i = 0; i < index; i++)
        ++it;
    return (**it);
}

JSON::JsonArr::~JsonArr()
{
    for (std::list<IJson *>::iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            delete (*it);
        }
}

void
JSON::JsonArr::AddObj(IJson const &val)
{
    objs.push_front(val.Clone());
}

std::list<JSON::IJson *> const &
JSON::JsonArr::GetList() const
{
    return (objs);
}

std::list<JSON::IJson *> &
JSON::JsonArr::GetList()
{
    return (objs);
}

size_t
JSON::JsonArr::Size() const
{
    return (objs.size());
}

std::string const &
JSON::JsonArr::Serialize()
{
    return (Serialize(0));
}

std::string const &
JSON::JsonArr::Serialize(int level)
{
    serialized = chars('\t', level) + "[\n";
    for (std::list<IJson *>::iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            if (it != objs.begin())
                serialized += ",\n";
            serialized += (*it)->Serialize(level + 1);
        }
    serialized += "\n" + chars('\t', level) + "]";
    return (serialized);
}

int
JSON::JsonArr::ParseFrom(std::string const &text)
{
    int len;
    int idx;

    serialized = text;

    len = text.length();
    idx = txtAdv(text, "\n \t[", 0, len);
    while (idx < len && text[idx] != ']')
        {
            idx = txtAdv(text, ",\n \t", idx, len);
            if (idx < len && text[idx] == '{')
                AddObj(JsonObj());
            else if (idx < len && text[idx] == '[')
                AddObj(JsonArr());
            else
                AddObj(JsonStr());
            idx += objs.front()->ParseFrom(text.substr(idx, len - idx));
            idx = txtAdv(text, ",\n \t", idx, len);
        }
    idx = txtAdv(text, ",\n \t]", idx, len);

    return (idx);
}

void
JSON::JsonArr::Clear()
{
    for (std::list<IJson *>::iterator it = objs.begin();
         it != objs.end(); ++it)
        {
            delete (*it);
        }
    objs.clear();
}

bool
JSON::JsonArr::Newline() const
{
    return (true);
}

JSON::IJson *
JSON::JsonArr::Clone() const
{
    return (new JsonArr(*this));
}
