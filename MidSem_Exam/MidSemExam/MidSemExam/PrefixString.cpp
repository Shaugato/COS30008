#include "PrefixString.h"

PrefixString::PrefixString(char aExtension) noexcept :
	// Constructor with one argument sets code and prefix to -1 and initializes the extension with the provided value.
	fCode(static_cast<uint16_t>(-1)),
	fPrefix(static_cast<uint16_t>(-1)),
	fExtension(aExtension)
{}

PrefixString::PrefixString(uint16_t aPrefix, char aExtension) noexcept :
	// Constructor with two arguments sets code to -1, initializes the prefix with the provided value, and initializes the extension with the provided value.
	fCode(static_cast<uint16_t>(-1)),
	fPrefix(aPrefix),
	fExtension(aExtension)
{
}

uint16_t PrefixString::getCode() const noexcept
{
	// Returns the code of the prefix string.
	return fCode;
}

void PrefixString::setCode(uint16_t aCode) noexcept
{
	// Sets the code of the prefix string to the provided value.
	fCode = aCode;
}

uint16_t PrefixString::w() const noexcept
{
	// Returns the prefix of the prefix string.
	return fPrefix;
}

char PrefixString::K() const noexcept
{
	// Returns the extension of the prefix string.
	return fExtension;
}

PrefixString PrefixString::operator+(char aExtension) const noexcept
{
	// Concatenates the prefix string's prefix with the provided extension and returns the resulting prefix string.
	PrefixString result;
	result.fPrefix = fCode;
	result.fExtension = aExtension;
	return result;
}

bool PrefixString::operator==(const PrefixString& aOther) const noexcept
{
	// Checks if two prefix strings are equal by comparing their prefixes and extensions.
	return (fPrefix == aOther.fPrefix && fExtension == aOther.fExtension);
}

std::ostream& operator<<(std::ostream& aOStream, const PrefixString& aObject)
{
	// Outputs the prefix string's code, prefix, and extension in a formatted string to the provided output stream.
	return aOStream << "(" << aObject.fCode << "," << aObject.fPrefix << "," << aObject.fExtension << ")";
}
