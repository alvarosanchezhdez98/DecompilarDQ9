// The window of the results of a battle: the experience that the party members earn, and the stats of a member that
// levels up
#include "Scene/Overlay_23/BattleResultWindow.h"
#include "GameState/GameState.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define REG_DISPCNT_SUB (*(volatile unsigned int*)0x04001000)
#define REG_BG0CNT_SUB (*(volatile unsigned short*)0x04001008)
#define REG_BG1CNT_SUB (*(volatile unsigned short*)0x0400100a)
#define REG_BG2CNT_SUB (*(volatile unsigned short*)0x0400100c)
#define REG_BG3CNT_SUB (*(volatile unsigned short*)0x0400100e)

#define SET_PRIORITY(reg, priority) ((reg) = ((reg) & ~3) | (priority))
#define SET_VISIBLE_PLANE(reg, planes) ((reg) = ((reg) & ~0x1f00) | ((planes) << 8))

// A name that the message system writes, as its argument
struct BattleResultName
{
    const char* unk_0;
    const char* unk_4;
    int unk_8;
};

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    void func_02041a28(char* text, int x);
    void func_02041a90(char* text, int x, int y);
    void func_02041b00(char* text, int);
    void func_02041fac(char* text, const char* line, int);
    void func_02042058(char* text, const char* append);
    int func_020420e8(const char* text, int large);
    MessageSystem* func_020421a0();
    int func_020426a4(int, int value);
    void func_02046380(MessageSystem* messages);
    void func_02046574(MessageSystem* messages, int index, const char* text);
    void func_020465c0(MessageSystem* messages, int, int);
    void func_020465d8(MessageSystem* messages, int, int);
    void func_020465f0(MessageSystem* messages, int, int);
    void func_02046608(MessageSystem* messages, int, const char* input, char* output, int, int, int);
    void func_0205cfd4(TextWindow* window);
    int func_0205d0e0(TextWindow* window, int);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d304(TextWindow* window, char* text, int, int, int, int, int, int);
    void func_0205d5d0(TextWindow* window, int item, char* text, int, int);
    int func_0205d67c(TextWindow* window);
    void func_0205d6a0(TextWindow* window, int);
    Canvas* func_0205d81c(TextWindow* window, int canvas);
    void func_02074b64(void*);
    void func_02074bf4(void*);
    // The base stats of a party member
    int func_02085fb4(void* data);
    int func_02086020(void* data);
    int func_0208608c(void* data);
    int func_020860f8(void* data);
    int func_02086164(void* data);
    int func_020861d0(void* data);
    int func_0208623c(void* data);
    int func_020862a8(void* data);
    int func_02086314(void* data);
    const char* func_020e0434(TextTable* texts, int id);
    void func_020e4bf4(BattleResultName* name, int member);
}

void BattleResultWindow::Initialize()
{
    unk_18 = 0;
    unk_19 = 0;
    func_02074b64(unk_8);
    planes_ = (REG_DISPCNT_SUB & 0x1f00) >> 8;
    texts_ = NULL;
    text_ = NULL;
    func_0205cfd4(&window_);
    for (int i = 0; i < 4; i++)
        values_[i] = 0;
    member_ = -1;
    memset(&before_, 0, sizeof(before_));
    memset(&after_, 0, sizeof(after_));
    lines_ = 0;
    count_ = 0;
    state_ = 0;
    loadStep_ = 0;
    step_ = 0;
    timer_ = 0;
    members_ = NULL;
    memberCount_ = 0;
}

void BattleResultWindow::Finish()
{
    if (func_0205d67c(&window_))
        func_0205d6a0(&window_, 1);
    texts_ = NULL;
    SET_VISIBLE_PLANE(REG_DISPCNT_SUB, planes_);
    func_02074bf4(unk_8);
    func_0205cfd4(&window_);
    state_ = 0;
    loadStep_ = 0;
    step_ = 0;
    texts_ = NULL;
    text_ = NULL;
}

void BattleResultWindow::Close()
{
    if (func_0205d67c(&window_))
        func_0205d6a0(&window_, 1);
    func_0205d1e0(&window_);
    func_0205d228(&window_);
    func_0205d274(&window_);
    func_0205d2bc(&window_);
}

int BattleResultWindow::Update()
{
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    if (loadStep_ == 0xff)
        func_0205d0e0(&window_, ticks);
    void (BattleResultWindow::*states[4])() = {&BattleResultWindow::State_Load, &BattleResultWindow::State_Experience,
                                               &BattleResultWindow::State_LevelUp, NULL};
    if (states[state_] == NULL)
        return 0;
    (this->*states[state_])();
    return 0;
}

void BattleResultWindow::Draw1()
{
    if (state_ != 0 && state_ != 3)
    {
        func_0205d1e0(&window_);
        func_0205d228(&window_);
        func_0205d274(&window_);
    }
}

void BattleResultWindow::Draw2()
{
    if (state_ != 0 && state_ != 3)
        func_0205d2bc(&window_);
}

void BattleResultWindow::SetSource(BattleResultWindowSource* source)
{
    if (source == NULL)
        return;
    TextWindow* window = &source->window_;
    window_.base_.frame_ = window->base_.frame_;
    window_.base_.cursor_ = window->base_.cursor_;
    window_.base_.unk_94 = window->base_.unk_94;
    window_.base_.unk_95 = window->base_.unk_95;
    window_.base_.unk_96 = window->base_.unk_96;
    window_.base_.unk_97 = window->base_.unk_97;
    window_.background_ = window->background_;
    window_.unk_9c = window->unk_9c;
    window_.width_ = window->width_;
    window_.height_ = window->height_;
    window_.unk_a4 = window->unk_a4;
    window_.unk_a6 = window->unk_a6;
    window_.unk_a8 = window->unk_a8;
    window_.unk_aa = window->unk_aa;
    window_.unk_ac = window->unk_ac;
    window_.unk_ae = window->unk_ae;
    window_.unk_b0 = window->unk_b0;
    window_.unk_b1 = window->unk_b1;
    window_.unk_b2 = window->unk_b2;
    window_.unk_b3 = window->unk_b3;
    window_.unk_b4 = window->unk_b4;
    window_.unk_b5 = window->unk_b5;
    window_.unk_b6 = window->unk_b6;
    window_.unk_b7 = window->unk_b7;
    window_.unk_b8 = window->unk_b8;
    window_.unk_b9 = window->unk_b9;
    window_.unk_ba = window->unk_ba;
    window_.unk_bb = window->unk_bb;
    texts_ = &source->texts_;
}

void BattleResultWindow::ShowExperience(const int* values)
{
    GameState::GetInstance();
    unsigned char* ids = ids_;
    unsigned char count = idCount_;
    memset(values_, 0, sizeof(values_));
    for (int i = 0; i < count; i++)
        values_[i] = values[ids[i]];
    if (func_0205d67c(&window_) == 0)
        step_ = 0;
    else
        step_ = 1;
    state_ = 1;
}

void BattleResultWindow::ShowLevelUp(int member, const BattleResultStats* before, const BattleResultStats* after)
{
    member_ = member;
    memcpy(&before_, before, sizeof(before_));
    memcpy(&after_, after, sizeof(after_));
    if (func_0205d67c(&window_) == 0)
        step_ = 0;
    else
        step_ = 1;
    state_ = 2;
}

void BattleResultWindow::State_Load()
{
    if (loadStep_ == 0xff)
        return;
    if (loadStep_ != 0)
        return;
    text_ = (char*)func_020421a0()->unk_5c;
    SET_PRIORITY(REG_BG0CNT_SUB, 1);
    SET_PRIORITY(REG_BG1CNT_SUB, 2);
    SET_PRIORITY(REG_BG2CNT_SUB, 0);
    SET_PRIORITY(REG_BG3CNT_SUB, 3);
    SET_VISIBLE_PLANE(REG_DISPCNT_SUB, 7);
    loadStep_ = 0xff;
}

void BattleResultWindow::State_Experience()
{
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    if (step_ == 0)
    {
        func_0205d6a0(&window_, 1);
        step_++;
        return;
    }
    if (step_ == 1)
    {
        lines_ = 1;
        timer_ = 5;
        count_ = 0;
        for (int i = 0; i < 4; i++)
        {
            if (values_[i] != 0)
                count_++;
        }
        short height = 12;
        switch (count_)
        {
        case 1:
            height = 5;
            break;
        case 2:
            height = 7;
            break;
        case 3:
            height = 10;
            break;
        case 4:
            height = 12;
            break;
        case 0:
            lines_ = 4;
            height = 5;
            break;
        }
        memset(text_, 0, 0x960);
        WriteExperience(text_, lines_);
        OpenWindow(text_, 0x18, height);
        step_++;
        return;
    }
    if (step_ == 2)
    {
        if (timer_ > 0)
        {
            timer_ -= (signed char)ticks;
            return;
        }
        timer_ = 5;
        lines_++;
        memset(text_, 0, 0x960);
        WriteExperience(text_, lines_);
        func_0205d5d0(&window_, 0, text_, 1, 0);
        if (lines_ == 4)
            step_++;
    }
}

void BattleResultWindow::State_LevelUp()
{
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    if (step_ == 0)
    {
        func_0205d6a0(&window_, 1);
        step_++;
        return;
    }
    if (step_ == 1)
    {
        lines_ = 0;
        timer_ = 5;
        memset(text_, 0, 0x960);
        WriteLevelUp(text_, lines_);
        OpenWindow(text_, 0x1a, 0x14);
        step_++;
        return;
    }
    if (step_ == 2)
    {
        if (timer_ > 0)
        {
            timer_ -= (signed char)ticks;
            return;
        }
        timer_ = 5;
        lines_++;
        memset(text_, 0, 0x960);
        WriteLevelUp(text_, lines_);
        Canvas* canvas = func_0205d81c(&window_, 0);
        if (canvas != NULL)
        {
            canvas->unk_d8 |= 4;
            func_0205d5d0(&window_, 0, text_, 1, 0);
            canvas->unk_d8 &= ~4;
        }
        if (lines_ == 9)
            step_++;
    }
}

void BattleResultWindow::OpenWindow(char* text, short width, short height)
{
    window_.SetSize(width, height);
    window_.unk_a4 = (0x20 - width) >> 1;
    window_.unk_a6 = (0x18 - height) >> 1;
    window_.SetUnkA8(0, 5);
    window_.SetUnkAc(10, 10);
    window_.unk_b1 = 0;
    window_.unk_b5 = 0;
    func_0205d304(&window_, text, 0, 0, 0, 1, 0, 0);
}

void BattleResultWindow::WriteExperience(char* text, unsigned char lines)
{
    if (text == NULL)
        return;
    GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    const char* title = func_020e0434(texts_, 0x75f8);
    func_02041a28(text, (0xc0 - func_020420e8(title, 0)) >> 1);
    func_02041b00(text, 1);
    func_02041fac(text, title, 0x10);
    unsigned char* ids = ids_;
    short height = window_.height_;
    unsigned char count = count_;
    unsigned char idCount = idCount_;
    int written = 0;
    signed char spacing = (height * 8 - (count * 10 + 0x1d)) / (count - 1);
    if (members_ == NULL)
        return;
    const char* format = func_020e0434(texts_, 0x75f9);
    for (int i = 0; i < idCount; i++)
    {
        if (values_[i] == 0 || lines == 0)
            continue;
        int id = ids[i];
        BattleResultMember* member = FindMember(id);
        if (member == NULL)
            continue;
        char output[0x100] = {0};
        char input[0x100] = {0};
        if (written)
        {
            func_02042058(text, func_020e0434(texts_, 0));
            func_02041b00(text, spacing);
        }
        func_02046380(messages);
        BattleResultName name;
        func_020e4bf4(&name, id);
        name.unk_0 = member->name_;
        name.unk_4 = member->name_;
        messages->unk_10 = &name;
        sprintf(input, format, 0x94 - func_020426a4(8, values_[i]));
        func_020465c0(messages, 1, values_[i]);
        func_02046608(messages, 10, input, output, 0x100, 0, 0);
        func_02042058(text, output);
        written = 1;
        lines--;
    }
    if (!written)
    {
        const char* none = func_020e0434(texts_, 0x75fa);
        int x = (0xc0 - func_020420e8(none, 0)) >> 1;
        func_02041a90(text, x, (height * 8 - 0x1a) / 2 + 0x10);
        func_02042058(text, none);
    }
}

void BattleResultWindow::WriteLevelUp(char* text, unsigned char lines)
{
    if (text == NULL || member_ == -1)
        return;
    GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    if (members_ == NULL)
        return;
    BattleResultMember* member = FindMember(member_);
    if (member == NULL)
        return;
    BattleResultStatWord* bonuses = member->bonuses_[member->vocation_];
    short stats[9][2];
    stats[0][0] = func_02085fb4(member->data_) + before_.stats_[0].first_ + bonuses[0].first_;
    stats[1][0] = func_02086020(member->data_) + before_.stats_[0].second_ + bonuses[0].second_;
    stats[2][0] = func_0208608c(member->data_) + before_.stats_[0].third_ + bonuses[0].third_;
    stats[3][0] = func_020860f8(member->data_) + before_.stats_[1].first_ + bonuses[1].first_;
    stats[4][0] = func_02086164(member->data_) + before_.stats_[1].second_ + bonuses[1].second_;
    stats[5][0] = func_020861d0(member->data_) + before_.stats_[1].third_ + bonuses[1].third_;
    stats[6][0] = func_0208623c(member->data_) + before_.stats_[2].first_ + bonuses[2].first_;
    stats[7][0] = func_020862a8(member->data_) + before_.stats_[2].second_ + bonuses[2].second_;
    stats[8][0] = func_02086314(member->data_) + before_.stats_[2].third_ + bonuses[2].third_;
    stats[0][1] = stats[0][0] + after_.stats_[0].first_;
    stats[1][1] = stats[1][0] + after_.stats_[0].second_;
    stats[2][1] = stats[2][0] + after_.stats_[0].third_;
    stats[3][1] = stats[3][0] + after_.stats_[1].first_;
    stats[4][1] = stats[4][0] + after_.stats_[1].second_;
    stats[5][1] = stats[5][0] + after_.stats_[1].third_;
    stats[6][1] = stats[6][0] + after_.stats_[2].first_;
    stats[7][1] = stats[7][0] + after_.stats_[2].second_;
    stats[8][1] = stats[8][0] + after_.stats_[2].third_;
    for (int i = 0; i < 9; i++)
    {
        if (i == 7)
        {
            if (stats[i][0] <= 0)
                stats[i][0] = 1;
            if (stats[i][1] <= 0)
                stats[i][1] = 1;
        }
        else
        {
            if (stats[i][0] < 0)
                stats[i][0] = 0;
            if (stats[i][1] < 0)
                stats[i][1] = 0;
        }
        if (stats[i][0] > 999)
            stats[i][0] = 999;
        if (stats[i][1] > 999)
            stats[i][1] = 999;
    }
    const char* title = func_020e0434(texts_, 0x7602);
    func_02041a90(text, (0xd0 - func_020420e8(title, 0)) >> 1, 1);
    func_02041fac(text, title, 0x10);
    int line;
    const char* format = func_020e0434(texts_, 0x7603);
    line = lines - 1;
    if (line < 0)
        return;
    func_02041a90(text, 10, line * 15 + 0x15);
    char output[0x100] = {0};
    char input[0x100] = {0};
    func_02046380(messages);
    func_02046574(messages, 0, func_020e0434(texts_, (short)(line + 0x760c)));
    short before = stats[line][0];
    func_020465c0(messages, 0, before);
    func_020465d8(messages, 0, 1);
    func_020465f0(messages, 0, 3);
    short after = stats[line][1];
    func_020465c0(messages, 1, after);
    func_020465d8(messages, 1, 1);
    func_020465f0(messages, 1, 3);
    int color = 15;
    if (after > before)
        color = 5;
    sprintf(input, format, color);
    func_02046608(messages, 12, input, output, 0xe3, 0, 1);
    func_02042058(text, output);
}

BattleResultMember* BattleResultWindow::FindMember(int id)
{
    BattleResultMember* member = members_;
    for (int i = 0; i < memberCount_; i++, member++)
    {
        if (member->id_ == id)
            return member;
    }
    return NULL;
}

void BattleResultWindow::SetMembers(const unsigned char* ids, unsigned char count)
{
    memcpy(ids_, ids, count);
    idCount_ = count;
}
