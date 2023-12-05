#include "Wad.h"

#include <iostream>
#include <regex>
#include <sstream>

#define DESC_IN_MAP 10

const std::regex NS_START_RX ("[A-Za-z][A-Za-z]_START");
const std::regex NS_END_RX ("[A-Za-z][A-Za-z]_END");
const std::regex MAP_DIR_RX ("E\\dM\\d");

std::vector<std::string> tokenizePath(std::string_view _path);

Wad* Wad::loadWad(std::string_view _path)
{
    return new Wad(_path);
}

Wad::Wad(std::string_view _filePath)
  : filePath(_filePath)
{
  file.open(filePath, std::ios::binary);

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open WAD file");
  }

  // Parse the header
  file.read(reinterpret_cast<char*>(&magic), 4);
  file.read(reinterpret_cast<char*>(&numDescriptors), 4);
  file.read(reinterpret_cast<char*>(&descListOffset), 4);

  // Parse descriptor list
  file.seekg(descListOffset, std::ios::beg);

  descriptors.resize(numDescriptors);

  for (int i = 0; i < numDescriptors; i++) {
    file.read(reinterpret_cast<char*>(&descriptors[i]), sizeof(Descriptor));
  }
}

std::string Wad::getMagic() const
{
  return {magic, 4};
}

bool Wad::isContent(std::string_view _path) const {
  int descIndex;
  DescriptorType type = findDescriptor(_path, descIndex);

  if (type == DESC_CONTENT) {
    return true;
  }

  return false;
}

bool Wad::isDirectory(std::string_view _path) const {
  int descIndex;
  DescriptorType type = findDescriptor(_path, descIndex);

  if (type == DESC_MAP || type == DESC_NS_START || type == DESC_ROOT) {
    return true;
  }

  return false;
}

int Wad::getSize(std::string_view _path) const {
  int descIndex;
  DescriptorType type = findDescriptor(_path, descIndex);

  if (type == DESC_CONTENT) {
    const Descriptor* d = &descriptors[descIndex];
    return static_cast<int>(d->length);
  }

  return -1;
}

int Wad::getContents(std::string_view _path, char *_buff, int _length, int _offset) {
  int descIndex;
  DescriptorType type = findDescriptor(_path, descIndex);

  if (type == DESC_CONTENT) {
    const Descriptor* d = &descriptors[descIndex];
    file.seekg(d->offset + _offset, std::ios::beg);
    file.read(_buff, _length);
    return _length;
  }

  return -1;
}

int Wad::getDirectory(std::string_view _path, std::vector<std::string> *_contents) const {
  int descIndex;
  DescriptorType type = findDescriptor(_path, descIndex);
  const Descriptor* dirDesc = &descriptors[descIndex];

  if (type == DESC_MAP) {
    for (int i = 1; i <= 10; i++) {
      const Descriptor* d = &descriptors[descIndex + i];
      // fix string
      size_t len = strlen(d->name);
      if (len > 8) {
        len = 8;
      }
      std::string name ( d->name, len );
      _contents->emplace_back(name);
    }
    return 10;
  }

  if (type == DESC_NS_START || type == DESC_ROOT) {
    std::vector<std::string> tokens = tokenizePath(_path);

    int mapCounter = 0;
    bool inChildNs = false;
    bool inMap = false;

    size_t i;
    std::string startingNs;
    if (type == DESC_NS_START) {
      i = descIndex + 1;
      startingNs = tokens.back();
    } else {
      i = descIndex;
    }

    for (; i < numDescriptors; i++) {
      const Descriptor* d = &descriptors[i];
      size_t len = strlen(d->name);
      if (len > 8) {
        len = 8;
      }
      std::string name ( d->name, len );

      if (inMap) {
        mapCounter++;
        if (mapCounter == DESC_IN_MAP) {
          inMap = false;
          mapCounter = 0;
        }
        continue;
      }

      if (std::regex_match(name, NS_END_RX)) {
        if ((startingNs == name.substr(0, 2)) && (type == DESC_NS_START)) {
          break;
        }
        inChildNs = false;
        continue;
      }

      if (inChildNs) {
        continue;
      }

      if (std::regex_match(name, MAP_DIR_RX)) {
        _contents->emplace_back(name);
        inMap = true;
        continue;
      }

      if (std::regex_match(name, NS_START_RX)) {
        _contents->emplace_back(name.substr(0, 2));
        inChildNs = true;
        continue;
      }

      _contents->emplace_back(name);
    }
    return static_cast<int>(_contents->size());
  }

  return -1;
}

void Wad::createDirectory(std::string_view _path) {

}

void Wad::createFile(std::string_view _path) {

}

void Wad::writeToFile(std::string_view _path, const char *_buff, int _length, int _offset) {

}

Wad::~Wad()
{
  file.close();
}

void Wad::printDescriptors() const {
  for (int i = 0; i < numDescriptors; i++) {
    Descriptor d = descriptors[i];
    size_t len = strlen(d.name);
    if (len > 8) {
      len = 8;
    }
    std::string name ( d.name, len );
    std::cout << name << " " << d.offset << " " << d.length << std::endl;
  }
}

DescriptorType Wad::findDescriptor(std::string_view _path, int& _descIndex) const {
  if (_path == "/") {
    _descIndex = 0;
    return DESC_ROOT;
  }

  std::vector<std::string> currentPath;
  std::vector<std::string> targetPath = tokenizePath(_path);

  bool inMap = false;
  int mapCounter = 0;

  size_t i = 0;
  for (const auto& d : descriptors) {
    size_t len = strlen(d.name);
    if (len > 8) {
      len = 8;
    }
    std::string name ( d.name, len );

    if (inMap) mapCounter++;

    if (std::regex_match(name, NS_START_RX)) {
      currentPath.push_back(name.substr(0, 2));

      if (currentPath == targetPath) {
        _descIndex = i;
        return DESC_NS_START;
      }

      i++;
      continue;
    }

    if (std::regex_match(name, NS_END_RX)) {
      currentPath.pop_back();
      i++;
      continue;
    }

    if (std::regex_match(name, MAP_DIR_RX)) {
      currentPath.push_back(name);
      if (currentPath == targetPath) {
        _descIndex = i;
        return DESC_MAP;
      }
      inMap = true;
      i++;
      continue;
    }

    currentPath.push_back(name);
    if (currentPath == targetPath) {
      _descIndex = i;
      return DESC_CONTENT;
    }
    currentPath.pop_back();

    if (inMap && (mapCounter == DESC_IN_MAP)) {
      currentPath.pop_back();
      inMap = false;
      mapCounter = 0;
    }
    i++;
  }

  _descIndex = -1;
  return DESC_NONE;
}

std::vector<std::string> tokenizePath(std::string_view _path) {
  std::string path ( _path );

  if (path.front() == '/') {
    path.erase(0, 1);
  }

  if (path.back() != '/') {
    path.push_back('/');
  }

  std::string token;
  std::vector<std::string> tokens;

  while (true) {
    size_t pos = path.find('/');
    if (pos == std::string::npos) {
      break;
    }
    token = path.substr(0, pos);
    tokens.push_back(token);
    path.erase(0, pos + 1);
  }

  return tokens;
}