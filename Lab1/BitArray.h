#pragma once

#include <vector>
#include <cmath>
#include <string>

class BitArray {
private:
    std::vector<int> bArr;
    size_t bitSize = 0;
    size_t byteSize = 0;

    bool checkSize(const BitArray &b) const;

    static size_t calculateBytePosition(size_t n);

    int calculateBit(size_t n, size_t bytePosition) const;

    size_t calculateByteSize(size_t numBits);

public:
    BitArray();

    ~BitArray();

    explicit BitArray(size_t numBits, unsigned long value = 0);

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

    friend bool operator==(const BitArray &a, const BitArray &b);
};

bool operator!=(const BitArray &a, const BitArray &b);

BitArray operator&(const BitArray &b1, const BitArray &b2);

BitArray operator|(const BitArray &b1, const BitArray &b2);

BitArray operator^(const BitArray &b1, const BitArray &b2);