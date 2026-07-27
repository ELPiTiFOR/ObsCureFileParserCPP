#pragma once

#include <cstdint>
#include <iostream>

#define HARD_INDEX 0x4
#define NORMAL_INDEX 0x2
#define EASY_INDEX 0x1
#define SPECIAL_INDEX 0x8


namespace oci
{
    class DiffMode
    {
    private:
        std::uint8_t flags_;
    public:
        DiffMode(bool hard, bool normal, bool easy, bool special);
        DiffMode(std::uint8_t flags);
        std::uint8_t getFlags() const;
        bool getHard() const;
        bool getNormal() const;
        bool getEasy() const;
        bool getSpecial() const;
        void setFlags(std::uint8_t flags);
        void setHard(bool hard);
        void setNormal(bool normal);
        void setEasy(bool easy);
        void setSpecial(bool special);
    };
} // namespace oci

std::ostream& operator<<(std::ostream& os, const oci::DiffMode& diff_mode);
bool operator==(const oci::DiffMode& d1, const oci::DiffMode& d2);