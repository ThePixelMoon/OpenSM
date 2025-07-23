// xmlresource.h

#ifndef XMLRESOURCE_H
#define XMLRESOURCE_H

#include <string>
#include <unordered_map>

struct SpriteInfo {
    std::string name;
    int x = 0, y = 0, w = 0, h = 0;
    float pivotX = 0.5f, pivotY = 0.5f;
    int offsetX = 0, offsetY = 0, originalW = 0, originalH = 0;
    bool rotated = false;
};

class Resource {
public:
    bool loadFromXML(const std::string& filename);
    const SpriteInfo* getSprite(const std::string& name) const;
    std::string getImagePath() const;

private:
    std::unordered_map<std::string, SpriteInfo> sprites;
    std::string imagePath;

    std::string getAttribute(const std::string& tag, const std::string& attr);
    static std::string readFile(const std::string& filename);
};

#endif // XMLRESOURCE_H