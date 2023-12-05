#include <string_view>
#include <string>
#include <memory>
#include <memory>
#include <vector>
#include <fstream>

#include <cstdint>

struct Descriptor {
    uint32_t offset;
    uint32_t length;
    char name[8];
};

enum DescriptorType {
    DESC_CONTENT = 0,
    DESC_MAP,
    DESC_NS_START,
    DESC_NS_END,
    DESC_ROOT,
    DESC_NONE
};

class Wad
{
public:
    static Wad* loadWad(std::string_view _path);

    explicit Wad(std::string_view _filePath);
    ~Wad();

    std::string getMagic() const;
    bool isContent(std::string_view _path) const;
    bool isDirectory(std::string_view _path) const;
    int getSize(std::string_view _path) const;
    int getContents(std::string_view _path, char* _buff, int _length, int _offset = 0);
    int getDirectory(std::string_view _path, std::vector<std::string>* _contents) const;

    void createDirectory(std::string_view _path);
    void createFile(std::string_view _path);
    void writeToFile(std::string_view _path, const char* _buff, int length = 0, int offset = 0);

    void printDescriptors() const;

private:
    std::string filePath;
    std::ifstream file;

    char magic[4];
    uint32_t numDescriptors;
    uint32_t descListOffset;

    std::vector<Descriptor> descriptors;

    DescriptorType findDescriptor(std::string_view _path, int& _descIndex) const;
};