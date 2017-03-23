#include <string>

#include "gmock/gmock.h"
#include "Utils.h"

using namespace testing;

class XorTesting: public testing::Test {
public:
    const ByteStream first {0b01010001, 0x00};
    const ByteStream second{0b10010100};
    const ByteStream result{0b11000101};
    const ByteStream error{0x00};
};

TEST_F(XorTesting, applyXor) {
    ASSERT_THAT(CB::Utils::XorByteStreams(first, second), Eq(result));
    ASSERT_THAT(CB::Utils::XorByteStreams(first, second, 1), Eq(result));
}

TEST_F(XorTesting, applySizedXor) {
    ASSERT_THAT(CB::Utils::XorByteStreams(first, second, 2), Eq(error));
}



int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
