#pragma once

#include "Text/TextTable.h"

// A pattern of forbidden words (0x20 bytes): up to 5 words, and how each matches
struct ForbiddenWordPattern
{
    // The file has offsets in its texts, which ResolvePattern() replaces
    const char* words_[5];
    signed char lengths_[5];
    // 0 to 3: the word is the whole word, somewhere in it, at its end or at its start; 4 to 7: the same with a
    // pattern (see ForbiddenWordChecker::Match)
    unsigned char types_[5];
    unsigned char count_;
    char unk_1f;
};

// The loaded file of the forbidden words
struct ForbiddenWordFile
{
    // The count of the patterns (12 bits), and the patterns were prepared (bit 31)
    unsigned int header_;
    // The patterns (0x20 bytes each) and their texts
    ForbiddenWordPattern* patterns_;
    char* texts_;
};

// A word of the checked text, in its codes
struct ForbiddenWordRange
{
    short start_;
    short length_;
    // The word ends its line, or a separator follows it
    unsigned char lineEnd_;
    unsigned char active_;
};

// What func_020425b4 returns for a character's code
struct CharacterInfo
{
    const char* text_;
    char unk_4;
    signed char length_ : 6;
    signed char unk_5_6 : 1;
    signed char uppercase_ : 1;
};

// The checker of the forbidden words of a text that the player writes (data_020f285c is its file). Overlay 12 (the
// profile's message) and overlay 9 (the character's name) each have a copy of its code
struct ForbiddenWordChecker
{
    // Overlay 9 loads data_020f2858 into it
    TextTable texts_;
    ForbiddenWordFile file_;
    void* unk_24;
    short unk_28;
    // The codes of the symbols that the patterns use (sSymbols)
    unsigned char symbols_[15];
    char unk_39[3];

    void Initialize();
    void LoadFile(void* data, int extra, int (*prepare)(ForbiddenWordFile* file, ForbiddenWordPattern* pattern));
    int Check(const char* text);
    void ToUpper(const char* text, char* output);
    int FindText(const char* word, const char* text, int length, int positions);
    int Match(const char* pattern, const char* text, int length, int positions);
    int Contains(const unsigned char* text, int length, unsigned char character);
};
