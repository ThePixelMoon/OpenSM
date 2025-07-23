// xmlbin.h

#ifndef XMLBIN_H
#define XMLBIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

class XMLBin {
public:
    bool load(const std::string& filename);

	uint32_t getCount() const { return count; }
	const std::string& getFixedStr() const { return fixedStr; }
	const std::vector<std::string>& getStrings() const { return strings; }

private:
    uint32_t readUInt32(std::ifstream& file);
    std::string readString(std::ifstream& file);

    uint32_t count = 0;
    std::string fixedStr;
    std::vector<std::string> strings;
};

#endif // XMLBIN_H