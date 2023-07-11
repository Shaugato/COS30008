// LZWCompressor.cpp

#include "LZWCompressor.h"

LZWCompressor::LZWCompressor(const std::string& aInput)
    : fTable(), fW(), fInput(aInput), fIndex(0), fK(-1), fCurrentCode(0)
{
    start(); // initialize the compressor
}

bool LZWCompressor::readK() noexcept
{
    if (fIndex < fInput.size()) // check if there are more characters to read
    {
        fK = fInput[fIndex++]; // read the next character
        return true; // return true to indicate that a character has been read
    }
    else // no more characters to read
    {
        fK = -1; // set fK to -1 to indicate end of input
        return false; // return false to indicate end of input
    }
}

void LZWCompressor::start()
{
    if (readK()) // if there are still characters to read
    {
        fW = fTable.lookupStart(fK); // initialize fW to the longest prefix string in the table that matches the first character of the input
        fCurrentCode = nextCode(); // get the next code for the compressor
    }
}

uint16_t LZWCompressor::nextCode()
{
    if (fK == -1) // check if end of input has been reached
    {
        return -1; // return -1 to indicate end of input
    }
    while (readK() && fK != -1) // while there are still characters to read
    {
        PrefixString lps = fW + fK; // concatenate fW and fK to form a new prefix string

        if (fTable.contains(lps)) // check if the new prefix string is already in the table
        {
            fW = lps; // if it is, update fW to the new prefix string
        }
        else // the new prefix string is not in the table
        {
            uint16_t n_prefix = lps.w(); // get the code for the new prefix string
            fTable.add(lps); // add the new prefix string to the table
            fW = fTable.lookupStart(lps.K()); // update fW to the longest prefix string in the table that matches the first character of the new prefix string
            return n_prefix; // return the code for the new prefix string
        }
    }

    return fW.getCode(); // return the code for the last prefix string found

}

const uint16_t& LZWCompressor::operator*() const noexcept
{
    return fCurrentCode; // return the current code for the compressor
}

LZWCompressor& LZWCompressor::operator++() noexcept {
    if (fK == -1 && fCurrentCode != -1) // check if end of input has been reached and if there are still codes to generate
    {
        fCurrentCode = -1; // set the current code to -1 to indicate end of input
    }
    else // there are still codes to generate
    {
        fCurrentCode = nextCode(); // get the next code for the compressor
    }
    return *this; // return the updated compressor
}

LZWCompressor LZWCompressor::operator++(int) noexcept {
    LZWCompressor old = *this; // create a copy of the compressor
    ++(*this); // increment the compressor
    return old; // return the copy
}

// Compares two compressors for equality
bool LZWCompressor::operator==(const LZWCompressor& aOther) const noexcept
{
    return fIndex == aOther.fIndex && fK == aOther.fK && fCurrentCode == aOther.fCurrentCode;
}

// Compares two compressors for inequality
bool LZWCompressor::operator!=(const LZWCompressor& aOther) const noexcept
{
    return !(*this == aOther);
}

// Returns a compressor object representing the beginning of the compressed output
LZWCompressor LZWCompressor::begin() const noexcept
{
    LZWCompressor copy = LZWCompressor(fInput);
    
    return copy;
}

LZWCompressor LZWCompressor::end() const noexcept
{
    LZWCompressor copy = *this;

    copy.fIndex = fInput.size();

    copy.fK = -1;

    copy.fCurrentCode = static_cast<uint16_t>(-1);



    return copy;
}