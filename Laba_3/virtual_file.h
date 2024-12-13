#ifndef VIRTUAL_FILE_H
#define VIRTUAL_FILE_H

#include <string>

class VirtualFile {
private:
    std::string name;
    std::string physical_path;

public:
    VirtualFile(const std::string& file_name, const std::string& phys_path)
        : name(file_name), physical_path(phys_path) {}

    std::string get_name() const { return name; }
    std::string get_physical_path() const { return physical_path; }
};

#endif // VIRTUAL_FILE_H