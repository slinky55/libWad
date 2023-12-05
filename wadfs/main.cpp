#include <iostream>
#include <fuse.h>
#include <string>
#include <cstring>
#include <vector>
#include "../libWad/Wad.h"
using namespace std;

Wad* myWad = nullptr; // Pointer to a Wad object

// Callback function to get attributes of a file or directory
static int getattr_callback(const char* path, struct stat* stbuf) {
    // Initialize the stat buffer to 0
    memset(stbuf, 0, sizeof(struct stat));

    // Convert path to a string
    string realPath(path);

    // Remove trailing slash from path
    if (!realPath.empty() && realPath.back() == '/') {
        realPath.pop_back();
    }

    // Check if path is a directory
    if (myWad->isDirectory(realPath)) {
        stbuf->st_mode = S_IFDIR | 0555; // Set directory mode and permissions
        stbuf->st_nlink = 2; // Set number of links
        return 0;
    }

    // Check if path is a file
    if (myWad->isContent(realPath)) {
        stbuf->st_mode = S_IFREG | 0444; // Set file mode and permissions
        stbuf->st_nlink = 1; // Set number of links
        stbuf->st_size = myWad->getSize(realPath); // Set file size
        return 0;
    }

    // Return error if path does not exist
    return -ENOENT;
}

// Callback function to read directory contents
static int readdir_callback(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi) {
    // Unused parameters
    (void) offset;
    (void) fi;

    // Add current directory and parent directory entries
    filler(buf, ".", nullptr, 0);
    filler(buf, "..", nullptr, 0);

    // Vector to store directory entries
    vector<string> entries;

    // Convert path to a string
    string realPath(path);

    // Add trailing slash to path if needed
    if (!realPath.empty() && realPath.back() != '/') {
        realPath += '/';
    }

    // If path is empty, set it to the root directory
    if (realPath.empty()) {
        realPath = "/";
    }

    // Get directory entries
    myWad->getDirectory(realPath, &entries);

    // Add each entry to the directory
    for (const string& entry : entries) {
        filler(buf, entry.c_str(), nullptr, 0);
    }

    return 0;
}

// Callback function to open a file
static int open_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

// Callback function to open a directory
static int opendir_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

// Callback function to release a file
static int release_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

// Callback function to release a directory
static int releasedir_callback(const char *path, struct fuse_file_info *fi) {
    return 0;
}

// Callback function to read file contents
static int read_callback(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    if (myWad->isContent(path)) {
        return myWad->getContents(path, buf, size, offset);
    }
    return -ENOENT;
}

static struct fuse_operations myFuse;

// main function that sets up the fuse_operations structure with the appropriate callback functions
int main(int argc, char *argv[]) {
    myFuse.getattr = getattr_callback;
    myFuse.open = open_callback;
    myFuse.read = read_callback;
    myFuse.readdir = readdir_callback;
    myFuse.opendir = opendir_callback;
    myFuse.release = release_callback;
    myFuse.releasedir = releasedir_callback;
    // load the WAD file
    myWad = Wad::loadWad(argv[1]);

    // shift the command line arguments over by one to ignore the WAD file path
    argv[1] = argv[2];
    argv[2] = NULL;

    // run the FUSE main loop with the specified arguments and fuse_operations structure
    return fuse_main(--argc, argv, &myFuse, NULL);
}