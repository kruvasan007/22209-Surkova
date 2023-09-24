#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"
#include "BitArray.h"

struct MyClassTest : public testing::Test {
    BitArray *bitArray;
    BitArray *toCompareBitArray;

    void SetUp() {
        bitArray = new BitArray(4, 0);
        toCompareBitArray = new BitArray(4, 1);
    }

    void TearDown() {
        delete bitArray;
        delete toCompareBitArray;
    }
};

TEST_F(MyClassTest, Subtest_toString) {
    EXPECT_EQ("0000", bitArray->toString());
}

TEST_F(MyClassTest, Subtest_constConstructor) {
    BitArray newBitArray = BitArray(*bitArray);
    EXPECT_EQ(bitArray->toString(), newBitArray.toString());
}

TEST_F(MyClassTest, Subtest_constructor) {
    BitArray newBitArray = BitArray();
    EXPECT_EQ("", newBitArray.toString());
    EXPECT_EQ(0, newBitArray.size());
}

TEST_F(MyClassTest, Subtest_operatorGet) {
    EXPECT_EQ(false, (*bitArray)[0]);
}

TEST_F(MyClassTest, Subtest_operatorEqualEqualFalse) {
    EXPECT_EQ(false, (*bitArray) == (*toCompareBitArray));
}

TEST_F(MyClassTest, Subtest_operatorEqualEqualFalse2) {
    toCompareBitArray->resize(6, false);
    EXPECT_EQ(false, (*bitArray) == (*toCompareBitArray));
}


TEST_F(MyClassTest, Subtest_operatorEqualEqualTrue) {
    EXPECT_EQ(true, (*bitArray) == (*bitArray));
}

TEST_F(MyClassTest, Subtest_operatorEqualNotEqueal) {
    EXPECT_EQ(true, (*bitArray) != (*toCompareBitArray));
}

TEST_F(MyClassTest, Subtest_swap) {
    toCompareBitArray->resize(35, true);
    BitArray oldArr = BitArray(*bitArray);
    toCompareBitArray->swap(*bitArray);
    EXPECT_EQ(oldArr.toString(), toCompareBitArray->toString());
    EXPECT_EQ(oldArr.size(), toCompareBitArray->size());
}

TEST_F(MyClassTest, Subtest_operatorAndEqual) {
    *toCompareBitArray &= *bitArray;
    EXPECT_EQ("0000", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorAndEqualFalling) {
    toCompareBitArray->resize(5);
    *toCompareBitArray &= *bitArray;
    EXPECT_EQ("00001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorOrEqualFalling) {
    toCompareBitArray->resize(5);
    *toCompareBitArray |= *bitArray;
    EXPECT_EQ("00001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorOrEqual) {
    bitArray->set(1, true);
    bitArray->set(2, true);
    *toCompareBitArray |= *bitArray;
    EXPECT_EQ("0111", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorXorEqual) {
    *toCompareBitArray ^= *bitArray;
    EXPECT_EQ("0001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorXorEqualException) {
    toCompareBitArray->resize(5, false);
    *toCompareBitArray ^= *bitArray;
    EXPECT_EQ("00001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatoAnd) {
    BitArray newBitArray = BitArray((*toCompareBitArray) & (*bitArray));
    EXPECT_EQ("0000", newBitArray.toString());
}

TEST_F(MyClassTest, Subtest_operatorAndExcept) {
    toCompareBitArray->resize(5, false);
    BitArray newBitArray = BitArray((*toCompareBitArray) & (*bitArray));
    EXPECT_EQ("", newBitArray.toString());
}

TEST_F(MyClassTest, Subtest_operatorOr) {
    BitArray newBitArray = BitArray((*toCompareBitArray) | (*bitArray));
    EXPECT_EQ("0001", newBitArray.toString());
}

TEST_F(MyClassTest, Subtest_operatorOrExcept) {
    toCompareBitArray->resize(5, false);
    BitArray newBitArray = BitArray((*toCompareBitArray) | (*bitArray));
    EXPECT_EQ("", newBitArray.toString());
}

TEST_F(MyClassTest, Subtest_operatorXor) {
    BitArray newBitArray = BitArray((*toCompareBitArray) ^ (*bitArray));
    EXPECT_EQ("0001", newBitArray.toString());
}

TEST_F(MyClassTest, Subtest_operatorXorExcept) {
    toCompareBitArray->resize(5, false);
    BitArray newBitArray = BitArray((*toCompareBitArray) ^ (*bitArray));
    EXPECT_EQ("", newBitArray.toString());
}

TEST_F(MyClassTest, Subtest_operatorLeftShiftEqual) {
    toCompareBitArray->set(1, true);
    *toCompareBitArray <<= 1;
    EXPECT_EQ("0110", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorRightShiftEqual) {
    toCompareBitArray->set(1, true);
    *toCompareBitArray >>= 1;
    EXPECT_EQ("0001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorRightShift) {
    toCompareBitArray->set(1, true);
    *toCompareBitArray = *toCompareBitArray >> 1;
    EXPECT_EQ("0001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_operatorLeftShift) {
    toCompareBitArray->set(1, true);
    *toCompareBitArray = *toCompareBitArray << 1;
    EXPECT_EQ("0110", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_PushBack) {
    toCompareBitArray->pushBack(false);
    EXPECT_EQ("00010", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_PushBackResize) {
    toCompareBitArray->clear();
    toCompareBitArray->pushBack(true);
    EXPECT_EQ("1", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_clear) {
    toCompareBitArray->clear();
    EXPECT_EQ("", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_setWithParam) {
    toCompareBitArray->set(2, true);
    EXPECT_EQ("0101", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_set) {
    toCompareBitArray->set();
    EXPECT_EQ("1111", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_setExcept) {
    toCompareBitArray->set(6, false);
    EXPECT_EQ("0001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_reset) {
    toCompareBitArray->reset();
    EXPECT_EQ("0000", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_resetWithParam) {
    toCompareBitArray->reset(0);
    EXPECT_EQ("0000", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_resize) {
    toCompareBitArray->resize(9, true);
    EXPECT_EQ("111110001", toCompareBitArray->toString());
}

TEST_F(MyClassTest, Subtest_resizeBig) {
    toCompareBitArray->resize(33, true);
    EXPECT_EQ(33, toCompareBitArray->size());
}


TEST_F(MyClassTest, Subtest_anyTrue) {
    EXPECT_EQ(true, toCompareBitArray->any());
}

TEST_F(MyClassTest, Subtest_anyFalse) {
    EXPECT_EQ(false, bitArray->any());
}

TEST_F(MyClassTest, Subtest_none) {
    EXPECT_EQ(true, bitArray->none());
}

TEST_F(MyClassTest, Subtest_size) {
    EXPECT_EQ(4, bitArray->size());
}

TEST_F(MyClassTest, Subtest_count) {
    EXPECT_EQ(0, bitArray->count());
}

TEST_F(MyClassTest, Subtest_emptyFalse) {
    EXPECT_EQ(false, bitArray->empty());
}

TEST_F(MyClassTest, Subtest_emptyTrue) {
    bitArray->clear();
    EXPECT_EQ(true, bitArray->empty());
}


TEST_F(MyClassTest, Subtest_operatorTilda) {
    BitArray bitArray1 = BitArray(4, 3);
    bitArray1 = ~bitArray1;
    EXPECT_EQ("1100", bitArray1.toString());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}