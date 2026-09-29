#pragma once

#include "Graphics/Background.h"
#include "Graphics/Vector.h"
#include "Text/TextTable.h"

class MenuScript;
struct MenuObjectList;

// Overlay 23's objects that the menus' scripts create (overlay 11's commands): each class is in its own file, and
// MenuObjects.cpp has what they have in common. The script commands construct them on the stack and copy them to a
// heap. The virtual functions that nothing names yet are named by their offset in the vtable
class MenuObjectClass
{
public:
    // 0 for MenuObjectClass0, 0xffff when initialized
    unsigned short type_;
    unsigned short id_;
    // The IDs of the MenuHeap and the MenuVRAMState that the object loads its file in
    unsigned short heap_;
    unsigned short vramState_;
    // Flags that the scripts set and clear, such as 1 and 4 (8: hidden?)
    unsigned char flags_;
    char unk_d[3];
    // Under data/
    const char* file_;
    MenuObjectClass* prev_;
    MenuObjectClass* next_;
    // 2 when loaded
    int state_;

    virtual void Update(MenuScript* script) = 0;
    virtual void Draw1() {}
    virtual void Draw2() {}
    virtual void V0c(MenuScript* script) {}
    virtual void V10(MenuScript* script) {}
    virtual void Draw3() {}
    virtual void Finish(MenuObjectList* list) = 0;
    virtual void SetPosition(Vector3fix* position) = 0;
    virtual Vector3fix GetPosition() = 0;
    virtual void V24(int) {}
    virtual int V28()
    {
        return 0;
    }
    virtual void V2c(int) {}
    virtual int V30()
    {
        return 0;
    }
    virtual void V34(int) {}
    virtual int V38()
    {
        return 0;
    }
    virtual void V3c(short) {}
    virtual unsigned short V40()
    {
        return 0;
    }
    virtual void V44(short) {}
    virtual unsigned short V48()
    {
        return 0;
    }
    virtual void V4c(int) {}
    virtual int V50()
    {
        return 0;
    }
    virtual void V54(int) {}
    virtual int V58()
    {
        return 0;
    }
    virtual void V5c(int) {}
    virtual int V60()
    {
        return 0;
    }
    virtual void V64(int) {}
    virtual int V68()
    {
        return 0;
    }
    virtual void V6c(int) {}
    virtual int V70()
    {
        return 0;
    }
    virtual void V74(int) {}
    virtual int V78()
    {
        return 0;
    }
    virtual void V7c(int) {}
    virtual int V80()
    {
        return 0;
    }
    virtual void V84(int) {}
    virtual int V88()
    {
        return 0;
    }
    virtual void V8c(int) {}
    virtual int V90()
    {
        return 0;
    }
    virtual void V94(int) {}
    virtual int V98()
    {
        return 0;
    }
    virtual void V9c(int) {}
    virtual int Va0()
    {
        return 0;
    }
    virtual void Va4(int) {}
    // The callback that touching the object runs
    virtual int GetTouchCallback()
    {
        return 0;
    }
    virtual void Vac(int, int, int) {}
    virtual void Vb0(int) {}
    virtual int Vb4()
    {
        return 0;
    }
    // Whether the touched point is on the object
    virtual int IsTouched()
    {
        return 0;
    }
    virtual int Vbc()
    {
        return 0;
    }
    virtual int Vc0()
    {
        return 0;
    }
    // Sets the object's color
    virtual void SetColor(unsigned char red, unsigned char green, unsigned char blue) {}
    virtual void Vc8(int) {}
    virtual Vector3fix Vcc()
    {
        Vector3fix zero = {0};
        return zero;
    }
    virtual void Vd0() {}
    virtual void Vd4() {}
    virtual void Vd8(unsigned char) {}
    // The color of the object's text
    virtual unsigned char GetColor()
    {
        return 15;
    }
    virtual void SetValue(int) {}
    virtual int GetValue()
    {
        return 0;
    }
    virtual int Ve8()
    {
        return 0;
    }
    virtual int Vec()
    {
        return 0;
    }
    virtual void Vf0(int) {}
    virtual void Vf4(int) {}
    // Whether the touched point is on the object, for the groups (see MenuObjectGroup)
    virtual int ContainsTouch()
    {
        return 0;
    }

    void Initialize();
    unsigned short GetId();
    unsigned short GetType();
    MenuObjectClass* GetNext();
};

// A group of objects: when none of them is busy, the list starts an entry of the script and runs a callback
struct MenuObjectGroup
{
    unsigned char count_;
    char unk_1;
    unsigned short ids_[8];
    short entry_;
    short callback_;

    void Clear();
};

// A range of addresses in the sorted list of MenuObjectList
struct MenuObjectRange
{
    unsigned int start_;
    unsigned int end_;
    MenuObjectRange* prev_;
    MenuObjectRange* next_;
};

// The objects of a MenuScript (0x74 bytes)
struct MenuObjectList
{
    MenuObjectClass* first_;
    // The BackgroundLoader task of the file that an object loads, or -1
    int task_;
    // Bits of 2 sets of 0x80 slots
    unsigned int slots_[2][4];
    MenuObjectRange* ranges_;
    // Bits of 2 sets of 16
    unsigned short masks_[2];
    MenuObjectGroup groups_[3];
    char unk_72[2];

    void Initialize();
    void Add(MenuObjectClass* object);
    void Remove(MenuObjectClass* object);
    void RemoveHeap(int heap);
    MenuObjectClass* Find(int id);
    MenuObjectClass* GetAt(int index);
    void Update(MenuScript* script);
    void Draw1();
    void Draw2();
    void Draw3();
    void CheckTouch(MenuScript* script);
    int CheckGroups(MenuScript* script);
    void SetTask(int task);
    int GetTask();
    int IsLoading();
    void SetSlots(int set, unsigned int start, unsigned int count);
    void ClearSlots(int set, unsigned int start, unsigned int count);
    int FindSlots(int set, unsigned int count);
    void AddRange(MenuObjectRange* range);
    void RemoveRange(MenuObjectRange* range);
    unsigned int FindRange(unsigned int size);
    void SetMask(int set, unsigned int bit);
    void ClearMask(int set, unsigned int bit);
    int FindMask(int set);
    void SetGroup(int index, const MenuObjectGroup* group);
    void ClearGroup(int index);
};

// The objects of type 0, which load a file under data/ (0xac bytes)
class MenuObjectClass0 : public MenuObjectClass
{
public:
    // func_0204719c initializes it and func_02047230 destroys it
    char model_[0x14];
    // Which func_02048080 clears (see MenuObjectBuffer)
    char unk_34[8];
    Vector3fix position_;
    char unk_48[0xa8 - 0x48];
    unsigned short unk_a8;
    unsigned short unk_aa;

    int Initialize(MenuScript* script, int id, int heap, int vramState, const char* file);
    virtual void Finish(MenuObjectList* list);
    virtual void Update(MenuScript* script);
    int State_Load(MenuScript* script);
    int State_Wait(MenuScript* script);
    int State_Loaded(MenuScript* script);
    virtual void Draw1();
    virtual void Draw2();
    virtual void SetPosition(Vector3fix* position);
    virtual Vector3fix GetPosition();
    virtual void V3c(short value);
    virtual unsigned short V40();
    virtual void V44(short value);
    virtual unsigned short V48();
    void Load(MenuScript* script);
    void LoadFile(MenuScript* script, void* file, unsigned int size);
    void* GetModel();
    void SetLoaded();
};

// The objects of type 4, which show a text of a table
class MenuObjectClass4 : public MenuObjectClass
{
public:
    TextTable* GetTexts();
};

// The objects of type 2, a background whose cells (.bnsc) are in an archive under data/ (0x54 bytes)
class MenuObjectClass2 : public MenuObjectClass
{
public:
    MenuScript* script_;
    // The GP2 archive of the file under data/, or NULL
    const char* archive_;
    BackgroundGraphics background_;
    // SetColor() was called
    int colored_;
    unsigned char red_;
    unsigned char green_;
    unsigned char blue_;
    // In tiles
    short x_;
    short y_;

    int Initialize(MenuScript* script, int id, int heap, const char* archive, const char* file, int screen, int layer,
                   int priority);
    virtual void Update(MenuScript* script);
    int State_Load(MenuScript* script);
    int State_Wait(MenuScript* script);
    int State_Loaded(MenuScript* script);
    virtual void V0c(MenuScript* script);
    virtual void V10(MenuScript* script);
    virtual void Draw3();
    virtual void Finish(MenuObjectList* list);
    BackgroundGraphics* GetBackground();
    void SetFile(const char* file);
    void Load(MenuScript* script);
    void LoadFiles(MenuScript* script, void* archive, unsigned int size);
    void LoadCells(MenuScript* script, int add, void* archive, unsigned int size);
    virtual void SetColor(unsigned char red, unsigned char green, unsigned char blue);
    void LoadData(MenuScript* script);
    virtual void SetPosition(Vector3fix* position);
    virtual Vector3fix GetPosition();
};

// The objects of type 6, a canvas on a MenuObjectClass2's background that the objects of types 8, 15 and 19 draw
// their texts, numbers and boxes on (0x110 bytes)
class MenuObjectClass6 : public MenuObjectClass
{
public:
    // Its background is a MenuObjectClass2's
    Canvas canvas_;
    // In pixels
    unsigned short x_;
    unsigned short y_;
    // The page and the pages, drawn as "<page + 1>/<pages>" when flags_ has 4
    short page_;
    short pages_;
    // The MenuObjectClass2 whose background has the frame
    unsigned char frame_;
    char unk_109;
    unsigned char color_;
    char unk_10b;
    unsigned short unk_10c;
    unsigned short unk_10e;

    int Initialize(MenuScript* script, int id, int heap, int background, int width, int height, int frame,
                   int parent);
    void Setup(MenuScript* script, int, short x, short y, short width, int height, unsigned char,
               unsigned char, bool);
    void Refresh(MenuScript* script);
    void Clear();
    virtual void Finish(MenuObjectList* list);
    virtual void Update(MenuScript* script);
    virtual void Draw1();
    virtual void Draw2();
    virtual void SetPosition(Vector3fix* position);
    virtual Vector3fix GetPosition();
    void DrawObjects(MenuScript* script);
    void DrawFrame(MenuScript* script);
    void Select(MenuScript* script, int id);
    void SetUnkC2(MenuScript* script, unsigned char value, int refresh);
    void SetUnk10c(short a, short b);
    virtual int ContainsTouch();
};

// The objects of type 7, a list with a selection
class MenuObjectClass7 : public MenuObjectClass
{
public:
    char unk_20[0x5c - 0x20];
    short unk_5c;
    short unk_5e;

    int GetSelection(int, int);
    int GetUnk9bb0();
    int GetUnk9bc0();
};

// The objects of type 8, a text on a MenuObjectClass6
class MenuObjectClass8 : public MenuObjectClass
{
public:
    // The text, or NULL for the text textId_ of the MenuObjectClass4 texts_
    const char* text_;
    char unk_24[0x34 - 0x24];
    // The ID of the MenuObjectClass6
    unsigned short canvas_;
    unsigned short texts_;
    short textId_;
    char unk_3a[0x44 - 0x3a];
    unsigned char font_ : 4;
    unsigned char color_ : 4;
    unsigned char selected_ : 1;
    // 1: left, 2: right, 3: centered
    unsigned char alignment_ : 6;
    // The text has codes that the message system formats
    unsigned char formatted_ : 1;

    virtual void Vd8(unsigned char value)
    {
        color_ = value;
    }
    virtual unsigned char GetColor()
    {
        return selected_ ? 5 : color_;
    }
    void SetWidth(unsigned short width);
    void SetHeight(unsigned short height);
};

// The objects of type 0xf, a number on a MenuObjectClass6
class MenuObjectClassF : public MenuObjectClass
{
public:
    char unk_20[0x2c - 0x20];
    int value_;
    // The ID of the MenuObjectClass6
    unsigned short canvas_;
    char unk_32[0x3a - 0x32];
    unsigned char font_ : 4;
    unsigned char color_ : 4;
    unsigned char unk_3b;
    unsigned char unk_3c;
    unsigned char unk_3d;

    virtual void Vd8(unsigned char value)
    {
        color_ = value;
    }
    virtual void SetValue(int value)
    {
        value_ = value;
    }
    virtual int GetValue()
    {
        return value_;
    }
    virtual unsigned char GetColor()
    {
        return color_;
    }
    void SetWidth(unsigned short width);
    void SetHeight(unsigned short height);
};

// The objects of type 0x13, a box on a MenuObjectClass6
class MenuObjectClass13 : public MenuObjectClass
{
public:
    char unk_20[4];
    // The ID of the MenuObjectClass6
    unsigned short canvas_;
    char unk_26[0x2e - 0x26];
    unsigned char color_;

    virtual unsigned char GetColor()
    {
        return color_;
    }
    unsigned short GetWidth();
    unsigned short GetHeight();
};
