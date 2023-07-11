#include "LZWTable.h"


LZWTable::LZWTable(uint16_t aInitialCharacters) : fIndex(aInitialCharacters), fInitialCharacters(std::min(aInitialCharacters,static_cast<uint16_t>(128)))
{
    initialize();
}

void LZWTable::initialize()
{
    for (uint16_t i = 0; i < fInitialCharacters; i++)
    {
        fEntries[i] = PrefixString(static_cast<char>(i));
        fEntries[i].setCode(i);
    }
    fIndex = fInitialCharacters;

}

const PrefixString& LZWTable::lookupStart(char aK) const noexcept
{
    uint16_t indx = static_cast<uint16_t>(aK);

    if (indx >= fIndex) {
        // Error: single-character prefix string not found in LZW table
        // You can throw an exception, log an error message, or return a default value
        // depending on design choice
        // Here, we choose to return a default-constructed PrefixString object
        return PrefixString();
    }

    return fEntries[indx];
}

bool LZWTable::contains(PrefixString& aWK) const noexcept
{
    // check for safety requirement
    if (aWK.w() == static_cast<uint16_t>(-1) ) {
        return false;
    }

    for (uint16_t i = fIndex - 1; i >= aWK.w(); i--)
    {
        if (fEntries[i] == aWK)
        {
            aWK = fEntries[i];
            return true;
        }
    }

    return false;
}

void LZWTable::add(PrefixString& aWK) noexcept
{
    if (aWK.w() ==static_cast<uint16_t>(- 1))
    {
        return;
    }
    if (fIndex < 1024)
    {
        aWK.setCode(fIndex);
        fEntries[fIndex++] = aWK;
    }

}
