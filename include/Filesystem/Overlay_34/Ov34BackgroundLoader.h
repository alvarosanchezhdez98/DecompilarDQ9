#pragma once

#include "../BackgroundLoader.h"

// The same loader as overlay 33's, loaded at the same address, but with a random memory leak added (see Process())
struct Ov34BackgroundLoader : public BackgroundLoader
{
    Ov34BackgroundLoader();
    virtual int Process();
};

void PopulateOv34BackgroundLoader(void* fileLoadSpace, unsigned int capacity, int relativePrio);
