#pragma once

#include <vector>
#include <cmath>
#include <string>

class BitArray {
private:
    std::vector<int> bArr;
    size_t bitSize;
    size_t byteSize;

    bool checkSize(const BitArray &b) const;

public:
    BitArray();

    ~BitArray();

    explicit BitArray(size_t numBits, unsigned long value = 0) {
        byteSize = ceil((numBits * 1.0) / (sizeof(int) * 8));
        bitSize = numBits;
        bArr = std::vector<int>(byteSize);
        size_t i = 0;
        while (value != 0) {
            set(i, value & 1);
            i++;
            value = value >> 1;
        }
    }

    BitArray(const BitArray &b);

    void swap(BitArray &b);

    BitArray &operator=(const BitArray &b);

    void resize(size_t num_bits, bool value = false);

    BitArray &set(size_t n, bool val = true);

    BitArray &set();

    void clear();

    void pushBack(bool bit);

    BitArray &operator&=(const BitArray &b);

    BitArray &operator|=(const BitArray &b);

    BitArray &operator^=(const BitArray &b);

    BitArray &operator<<=(size_t n);

    BitArray &operator>>=(size_t n);

    BitArray operator<<(size_t n) const;

    BitArray operator>>(size_t n) const;

    BitArray &reset(size_t n);

    BitArray &reset();

    bool any() const;

    bool none() const;

    size_t count() const;

    bool operator[](size_t n) const;

    BitArray operator~() const;

    size_t size() const;

    bool empty() const;

    std::string toString() const;
};

bool operator==(const BitArray &a, const BitArray &b);

bool operator!=(const BitArray &a, const BitArray &b);

BitArray operator&(const BitArray &b1, const BitArray &b2);

BitArray operator|(const BitArray &b1, const BitArray &b2);

BitArray operator^(const BitArray &b1, const BitArray &b2);