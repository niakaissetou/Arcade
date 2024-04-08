/*
** EPITECH PROJECT, 2024
** main_cpp
** File description:
** arcade
*/
#include "../Interface.hpp"
#include <iostream>
#include <dlfcn.h>

typedef void (*CreateWindowFunc)();

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <library_path>" << std::endl;
        return 1;
    }
    void *handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
        return 1;
    }
    CreateWindowFunc createWindow = (CreateWindowFunc)dlsym(handle, "createWindow");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Failed to load symbol: " << dlsym_error << std::endl;
        dlclose(handle);
        return 1;
    }
    createWindow();
    dlclose(handle);

    return 0;
}
