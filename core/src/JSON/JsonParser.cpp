#include "JsonParser.hpp"

JSON::JsonParser::JsonParser()
{ }

JSON::JsonParser::~JsonParser()
{ }

int
JSON::JsonParser::txtAdv(std::string const &text, const char *chars,
                         int idx, int len)
{
    bool ok;
    int nbchars;

    nbchars = 0;
    while (chars[nbchars])
        nbchars++;

    ok = true;
    while (idx < len && ok)
        {
            ok = false;
            for (int i = 0; i < nbchars && !ok; ++i)
                if (text[idx] == chars[i])
                    ok = true;
            if (ok)
                idx++;
        }
    return (idx);
}

int
JSON::JsonParser::txtUpto(std::string const &text, char c, int idx, int len)
{
    while (idx < len && ((c != '"' && (text[idx] != c)) ||
                         (c == '"' && (text[idx] != c ||
                                       (text[idx] == c &&
                                        (idx == 0 || (idx > 0 && text[idx - 1] == '\\')))))))
        idx++;
    return (idx);
}

std::string
JSON::JsonParser::replaceAll(std::string src,
                             std::string const &to_replace,
                             std::string const &replace_by)
{
    size_t start_pos;

    start_pos = 0;
    while ((start_pos = src.find(to_replace, start_pos)) != std::string::npos)
        {
            src.replace(start_pos, to_replace.length(), replace_by);
            start_pos += replace_by.length();
        }
    return (src);
}

std::string
JSON::JsonParser::chars(char c, int nb)
{
    char *cstr;
    std::string str;
    int i;

    cstr = new char[nb + 1];
    for (i = 0; i < nb; ++i)
        cstr[i] = c;
    cstr[i] = '\0';
    str = std::string(cstr);
    delete[] cstr;
    return (str);
}
