#include "BitArray.h"
#include <vector>
#include <iostream>

BitArray::BitArray() {
    bArr = std::vector<int>(0);
    bitSize = 0;
    byteSize = 0;
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
    size_t bytePosition = n / (sizeof(int) * 8);
    int bitPosition = 1 << (n - bytePosition * (sizeof(int) * 8));
    return bArr[bytePosition] & bitPosition;
}

BitArray &BitArray::set() {
    for (int i = 0; i < bitSize; ++i)
        set(i, true);
    return *this;
}

BitArray &BitArray::set(size_t n, bool val) {
    if (bitSize < n) {
        std::cout << "Error: size is smaller than n" << std::endl;
        return *this;
    }
    size_t bytePosition = n / (sizeof(int) * 8);
    int relativeChanges = 1 << (n - bytePosition * (sizeof(int) * 8));
    bArr[bytePosition] = val ? bArr[bytePosition] | relativeChanges :
                         bArr[bytePosition] & ~(relativeChanges);
    return *this;
}

void BitArray::swap(BitArray &b) {
    BitArray tmp = b;
    b = *this;
    bArr = tmp.bArr;
    bitSize = tmp.bitSize;
    byteSize = tmp.byteSize;
}

BitArray &BitArray::operator=(const BitArray &b) {
    if (this == &b)
        return *this;
    bitSize = b.bitSize;
    bArr = b.bArr;
    byteSize = b.byteSize;
    return *this;
}

size_t BitArray::size() const {
    return bitSize;
}

void BitArray::resize(size_t numBits, bool value) {
    size_t newByteSize = ceil((numBits * 1.0) / (sizeof(int) * 8));
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
    size_t newByteSize = ceil((bitSize * 1.0) / (sizeof(int) * 8));
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
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = bitSize + j; i > 0; --i)
            set(i, (*this)[i - 1]);
        set(0, false);
    }
    return *this;
}

BitArray &BitArray::operator>>=(size_t n) {
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < bitSize - j - 1; ++i)
            set(i, (*this)[i + 1]);
        set(bitSize - 1, false);
    }
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
    BitArray newBitArr = BitArray(b1.size());
    if (b1.size() != b2.size()) {
        std::cout << "ERROR: Different size" << std::endl;
        newBitArr.clear();
        return newBitArr;
    }
    for (int i = 0; i < b1.size(); ++i) {
        newBitArr.set(i, b1[i] & b2[i]);
    }
    return newBitArr;
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    BitArray newBitArr = BitArray(b1.size());
    if (b1.size() != b2.size()) {
        std::cout << "ERROR: Different size" << std::endl;
        newBitArr.clear();
        return newBitArr;
    }
    for (int i = 0; i < b1.size(); ++i) {
        newBitArr.set(i, b1[i] | b2[i]);
    }
    return newBitArr;
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    BitArray newBitArr = BitArray(b1.size());
    if (b1.size() != b2.size()) {
        std::cout << "ERROR: Different size" << std::endl;
        newBitArr.clear();
        return newBitArr;
    }
    for (int i = 0; i < b1.size(); ++i)
        newBitArr.set(i, b1[i] | b2[i]);
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