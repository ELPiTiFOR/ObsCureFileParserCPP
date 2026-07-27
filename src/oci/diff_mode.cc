#include "diff_mode.hh"

oci::DiffMode::DiffMode(bool hard, bool normal, bool easy, bool special)
{
    flags_ = 0;

    if (hard)
    {
        flags_ |= HARD_INDEX;
    }

    if (normal)
    {
        flags_ |= NORMAL_INDEX;
    }

    if (easy)
    {
        flags_ |= EASY_INDEX;
    }

    if (special)
    {
        flags_ |= SPECIAL_INDEX;
    }
}

oci::DiffMode::DiffMode(std::uint8_t flags)
{
    flags_ = flags;
}

std::uint8_t oci::DiffMode::getFlags() const
{
    return flags_;
}

bool oci::DiffMode::getHard() const
{
    return flags_ & HARD_INDEX;
}


bool oci::DiffMode::getNormal() const
{
    return flags_ & NORMAL_INDEX;
}

bool oci::DiffMode::getEasy() const
{
    return flags_ & EASY_INDEX;
}

bool oci::DiffMode::getSpecial() const
{
    return flags_ & SPECIAL_INDEX;
}

void oci::DiffMode::setFlags(std::uint8_t flags)
{
    flags_ = flags;
}

void oci::DiffMode::setHard(bool hard)
{
    if (hard)
    {
        flags_ |= HARD_INDEX;
        return;
    }

    flags_ &= (~HARD_INDEX);
}

void oci::DiffMode::setNormal(bool normal)
{
    if (normal)
    {
        flags_ |= NORMAL_INDEX;
        return;
    }

    flags_ &= (~NORMAL_INDEX);
}

void oci::DiffMode::setEasy(bool easy)
{
    if (easy)
    {
        flags_ |= EASY_INDEX;
        return;
    }

    flags_ &= (~EASY_INDEX);
}

void oci::DiffMode::setSpecial(bool special)
{
    if (special)
    {
        flags_ |= SPECIAL_INDEX;
        return;
    }

    flags_ &= (~SPECIAL_INDEX);
}


std::ostream& operator<<(std::ostream& os, const oci::DiffMode& diff_mode)
{
    int nb_printed = 0;
    os << "{";

    if (diff_mode.getHard())
    {
        if (nb_printed)
        {
            os << ", ";
        }
        os << "HARD";
        nb_printed++;
    }

    if (diff_mode.getNormal())
    {
        if (nb_printed)
        {
            os << ", ";
        }
        os << "NORMAL";
        nb_printed++;
    }

    if (diff_mode.getEasy())
    {
        if (nb_printed)
        {
            os << ", ";
        }
        os << "EASY";
        nb_printed++;
    }

    if (diff_mode.getSpecial())
    {
        if (nb_printed)
        {
            os << ", ";
        }
        os << "SPECIAL";
        nb_printed++;
    }

    os << "}";

    return os;
}

bool operator==(const oci::DiffMode& d1, const oci::DiffMode& d2)
{
    return d1.getFlags() == d2.getFlags();
}