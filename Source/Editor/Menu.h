#pragma once

struct MenuItem
{
    std::string Name;
    bool* Selected = nullptr;
    std::function<void()> Callback = nullptr;
    bool Enabled = true;
};