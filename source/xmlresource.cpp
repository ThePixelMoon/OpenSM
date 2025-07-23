// xmlresource.cpp
#include "xmlresource.h"
#include "log.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::string Resource::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return "";
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::string Resource::getAttribute(const std::string& tag, const std::string& attr) {
    std::string search = attr + "=";
    size_t pos = tag.find(search);
    if (pos == std::string::npos) return "";

    pos += search.length();
    if (pos >= tag.size()) return "";

    char quote = tag[pos];
    if (quote != '"' && quote != '\'') return "";

    size_t start = pos + 1;
    size_t end = tag.find(quote, start);
    if (end == std::string::npos) return "";

    return tag.substr(start, end - start);
}

bool Resource::loadFromXML(const std::string& filename) {
    std::string data = readFile(filename);
    if (data.empty()) {
        Log::log(Log::Level::Error, ("Failed to read XML file: " + filename).c_str());
        return false;
    }

    size_t atlasStart = data.find("<TextureAtlas");
    if (atlasStart == std::string::npos) {
        Log::log(Log::Level::Error, "No <TextureAtlas> tag found.");
        return false;
    }
    size_t atlasEnd = data.find('>', atlasStart);
    if (atlasEnd == std::string::npos) {
        Log::log(Log::Level::Error, "Malformed <TextureAtlas> tag.");
        return false;
    }

    std::string atlasTag = data.substr(atlasStart, atlasEnd - atlasStart + 1);
    imagePath = getAttribute(atlasTag, "imagePath");

    size_t pos = atlasEnd;
    while (true) {
        size_t spriteStart = data.find("<sprite", pos);
        if (spriteStart == std::string::npos) break;

        size_t spriteEnd = data.find("/>", spriteStart);
        if (spriteEnd == std::string::npos) break;

        std::string spriteTag = data.substr(spriteStart, spriteEnd - spriteStart + 2);

        SpriteInfo info;

        info.name = getAttribute(spriteTag, "n");
        if (info.name.empty()) {
            pos = spriteEnd + 2;
            continue; // no name? skip
        }

        auto toInt = [](const std::string& s) -> int {
            try { return std::stoi(s); } catch (...) { return 0; }
        };
        auto toFloat = [](const std::string& s) -> float {
            try { return std::stof(s); } catch (...) { return 0.f; }
        };

        info.x = toInt(getAttribute(spriteTag, "x"));
        info.y = toInt(getAttribute(spriteTag, "y"));
        info.w = toInt(getAttribute(spriteTag, "w"));
        info.h = toInt(getAttribute(spriteTag, "h"));
        std::string pX = getAttribute(spriteTag, "pX");
        std::string pY = getAttribute(spriteTag, "pY");
        info.pivotX = pX.empty() ? 0.5f : toFloat(pX);
        info.pivotY = pY.empty() ? 0.5f : toFloat(pY);

        info.offsetX = toInt(getAttribute(spriteTag, "oX"));
        info.offsetY = toInt(getAttribute(spriteTag, "oY"));
        info.originalW = toInt(getAttribute(spriteTag, "oW"));
        info.originalH = toInt(getAttribute(spriteTag, "oH"));

        std::string r = getAttribute(spriteTag, "r");
        info.rotated = (r == "y");

        sprites[info.name] = info;
        pos = spriteEnd + 2;
    }

    Log::log(Log::Level::Info, ("Loaded sprites from: " + filename).c_str());
    return true;
}

const SpriteInfo* Resource::getSprite(const std::string& name) const {
    auto it = sprites.find(name);
    if (it != sprites.end()) {
        return &it->second;
    }
    return nullptr;
}

std::string Resource::getImagePath() const {
    return imagePath;
}