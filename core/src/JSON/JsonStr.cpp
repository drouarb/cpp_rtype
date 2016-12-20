#include "JsonStr.hpp"

JSON::JsonStr::JsonStr()
{
    val = "";
}

JSON::JsonStr::JsonStr(std::string const &str)
{
    val = str;
}

JSON::JsonStr::~JsonStr()
{ }

void
JSON::JsonStr::Set(std::string const &newval)
{
    val = newval;
}

std::string const &
JSON::JsonStr::Get() const
{
    return (val);
}

std::string const &
JSON::JsonStr::Serialize()
{
    return (Serialize(0));
}

std::string const &
JSON::JsonStr::Serialize(int level)
{
    (void) level;
    serialized = chars('\t', level) + "\"" + replaceAll(val, "\"", "\\\"") + "\"";
    return (serialized);
}

int
JSON::JsonStr::ParseFrom(std::string const &text)
{
    int idx;
    int end;
    int len;

    len = text.length();
    if (text[0] == '"' && text.length() > 0)
        idx = 1;
    end = txtUpto(text, '"', idx, len);
    val += replaceAll(text.substr(idx, end - idx), "\\\"", "\"");
    return (txtAdv(text, "\"", end, len));
}

void
JSON::JsonStr::Clear()
{
    val = "";
}

bool
JSON::JsonStr::Newline() const
{
    return (false);
}

JSON::IJson *
JSON::JsonStr::Clone() const
{
    return (new JsonStr(val));
}


