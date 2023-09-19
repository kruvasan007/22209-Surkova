#include "BitArray.h"
#include <vector>
#include <iostream>

BitArray::BitArray(size_t numBits, unsigned long value) {
    byteSize = calculateByteSize(numBits);
    bitSize = numBits;
    bArr = std::vector<int>(byteSize);
    size_t i = 0;
    while (value != 0) {
        set(i, value & 1);
        i++;
        value = value >> 1;
    }
}

BitArray::BitArray() {

}

BitArray::BitArray(const BitArray &b) {
    bArr = b.bArr;
    bitSize = b.bitSize;
    byteSize = b.byteSize;
}

BitArray::~BitArray() = default;

size_t BitArray::count() const {
    size_t count = 0;
    for (int i = 0; i < bitSize; ++i)
        count += (*this)[i];
    return count;
}

bool BitArray::operator[](size_t n) const {
    if (n >= bitSize) return false;
    size_t bytePosition = calculateBytePosition(n);
    int bitPosition = calculateBit(n, bytePosition);
    return bArr[bytePosition] & bitPosition;
}

BitArray &BitArray::set() {
    for (int i = 0; i < bitSize; ++i)
        set(i, true);
    return *this;
}

size_t BitArray::calculateBytePosition(const size_t n) {
    return n / (sizeof(int) * 8);
}

int BitArray::calculateBit(size_t n, size_t bytePosition) const {
    return 1 << (n - bytePosition * (sizeof(int) * 8));
}

BitArray &BitArray::set(size_t n, bool val) {
    if (bitSize < n) {
        std::cout << "Error: size is smaller than n" << std::endl;
        return *this;
    }
    size_t bytePosition = calculateBytePosition(n);
    int relativeChanges = calculateBit(n, bytePosition);
    bArr[bytePosition] = val ? bArr[bytePosition] | relativeChanges :
                         bArr[bytePosition] & ~(relativeChanges);
    return *this;
}

void BitArray::swap(BitArray &b) {
    std::swap(bArr, b.bArr);
    std::swap(bitSize, b.bitSize);
    std::swap(byteSize, b.byteSize);
}

BitArray &BitArray::BitArray::operator=(const BitArray &b) {
    bitSize = b.bitSize;
    bArr = b.bArr;
    byteSize = b.byteSize;
    byteSize = b.byteSize;
    return *this;
}

size_t BitArray::size() const {
    return bitSize;
}

size_t BitArray::calculateByteSize(size_t numBits) {
    return ceil((numBits * 1.0) / (sizeof(int) * 8));
}

void BitArray::resize(size_t numBits, bool value) {
    size_t newByteSize = calculateByteSize(numBits);
    if (byteSize < newByteSize)
        bArr.resize(newByteSize);
    size_t addBit = numBits - bitSize;
    for (int i = 0; i < bitSize; ++i)
        set(i, (*this)[i]);
    byteSize = newByteSize;
    bitSize = numBits;
    for (size_t i = numBits - addBit; i < numBits; ++i)
        set(i, value);
}

void BitArray::pushBack(bool bit) {
    bitSize++;
    size_t newByteSize = calculateByteSize(bitSize);
    if (byteSize < newByteSize) {
        bArr.resize(newByteSize);
        byteSize = newByteSize;
    }
    (*this) <<= 1;
    set(0, bit);
}

BitArray BitArray::operator~() const {
    BitArray newBitArray = BitArray(bitSize);
    for (size_t i = 0; i < byteSize; ++i) {
        newBitArray.bArr[i] = ~bArr[i];
    }
    return newBitArray;
}

std::string BitArray::toString() const {
    std::string strBitArray;
    strBitArray.reserve(bitSize);
    for (int i = bitSize - 1; i >= 0; --i)
        strBitArray += std::to_string((*this)[i]);
    return strBitArray;
}

void BitArray::clear() {
    bArr.clear();
    bitSize = 0;
    byteSize = 0;
}

BitArray &BitArray::reset() {
    for (int i = 0; i < byteSize; ++i)
        bArr[i] = 0;
    return *this;
}

BitArray &BitArray::reset(size_t n) {
    set(n, false);
    return *this;
}

bool BitArray::any() const {
    for (int i = 0; i < bitSize; ++i)
        if ((*this)[i] == 1) return true;
    return false;
}

bool BitArray::empty() const {
    return bitSize == 0;
}

bool BitArray::none() const {
    return !any();
}

bool BitArray::checkSize(const BitArray &b) const {
    return bitSize == b.bitSize;
}

BitArray &BitArray::operator&=(const BitArray &b) {
    if (!checkSize(b)) {
        std::cout << "ERROR: Different size" << std::endl;
        return *this;
    }
    for (int i = 0; i < bitSize; ++i) {
        set(i, (*this)[i] & b[i]);
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if (!checkSize(b)) {
        std::cout << "ERROR: Different size" << std::endl;
        return *this;
    }
    for (int i = 0; i < bitSize; ++i) {
        set(i, (*this)[i] ^ b[i]);
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if (!checkSize(b)) {
        std::cout << "ERROR: Different size" << std::endl;
        return *this;
    }
    for (int i = 0; i < bitSize; ++i) {
        set(i, (*this)[i] | b[i]);
    }
    return *this;
}

BitArray &BitArray::operator<<=(size_t n) {
    for (size_t i = bitSize; i >= n; --i)
        set(i, (*this)[i - n]);
    set(0, false);
    return *this;
}

BitArray &BitArray::operator>>=(size_t n) {
    for (size_t i = 0; i < bitSize - n - 1; ++i)
        set(i, (*this)[i + n]);
    set(bitSize - 1, false);
    return *this;
}

BitArray BitArray::operator<<(size_t n) const {
    BitArray newBitArr = *this;
    newBitArr <<= n;
    return newBitArr;
}

BitArray BitArray::operator>>(size_t n) const {
    BitArray newBitArr = *this;
    newBitArr >>= n;
    return newBitArr;
}

BitArray operator&(const BitArray &b1, const BitArray &b2) {
    BitArray newBitArr = b1;
    if (b1.size() != b2.size()) {
        std::cout << "ERROR: Different size" << std::endl;
        newBitArr.clear();
        return newBitArr;
    }
    newBitArr &= b2;
    return newBitArr;
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    BitArray newBitArr = b1;
    if (b1.size() != b2.size()) {
        std::cout << "ERROR: Different size" << std::endl;
        newBitArr.clear();
        return newBitArr;
    }
    newBitArr |= b2;
    return newBitArr;
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    BitArray newBitArr = b1;
    if (b1.size() != b2.size()) {
        std::cout << "ERROR: Different size" << std::endl;
        newBitArr.clear();
        return newBitArr;
    }
    newBitArr ^= b2;
    return newBitArr;
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.size() == b.size()) {
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(const BitArray &a, const BitArray &b) {
    return !(a == b);
}