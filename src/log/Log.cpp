//
// Created by robcholz on 10/8/23.
//
#include "Log.hpp"


const char* GetFileNameFromPath(const char* filePath) {
    const char* lastSlash = nullptr;
    for (const char* p = filePath; *p != '\0'; ++p) {
        if (*p == '/' || *p == '\\') {
            lastSlash = p;
        }
    }
    return lastSlash ? lastSlash + 1 : filePath;
}
