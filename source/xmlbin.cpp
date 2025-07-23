// xmlbin.cpp
#include "xmlbin.h"
#include "log.h"

uint32_t XMLBin::readUInt32(std::ifstream& file) {
    uint32_t value = 0;
    if (!file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        Log::log(Log::Level::Error, "Failed to read uint32 from file");
        //throw std::runtime_error("Unexpected EOF");
    }
    return value;
}

std::string XMLBin::readString(std::ifstream& file) {
    uint32_t length = 0;
    try {
        length = readUInt32(file);
    } catch (const std::runtime_error&) {
        return "";
    }

    if (length == 0) return "";

    std::vector<char> buffer(length);
    if (!file.read(buffer.data(), length)) {
        Log::log(Log::Level::Error, "Failed to read string data from file");
        return "";
    }

    std::string str(buffer.data(), buffer.size());
    while (!str.empty() && str.back() == '\0') {
        str.pop_back();
    }
	
    return str;
}

bool XMLBin::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
		Log::log(Log::Level::Error, ("Failed to open bin file: " + filename).c_str());
        return false;
    }

    count = readUInt32(file);
    char fixedBuf[5] = {0};
    file.read(fixedBuf, 4);
    fixedStr = fixedBuf;

    strings.clear();
    for (uint32_t i = 0; i < count; ++i) {
        strings.push_back(readString(file));
    }

    return true;
}
