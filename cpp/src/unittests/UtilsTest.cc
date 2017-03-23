#include <string>

#include "gmock/gmock.h"
#include "Utils.h"

using namespace testing;

// { Debug
class DebugTesting: public testing::Test {
public:
    Byte one{0x1};
    std::string oneString = "00000001";

    ByteStream twentyOneTwice{0x21, 0x21};
    std::string twentyOneString = "00100001|00100001";
};

// Simplest case
TEST_F(DebugTesting, byteToString) {
    ASSERT_THAT(CB::Debug::byteToBinaryString(one), Eq(oneString));
}

TEST_F(DebugTesting, byteStreamToString) {
    ASSERT_THAT(CB::Debug::byteStreamToBinaryString(twentyOneTwice), Eq(twentyOneString));
}
// } Debug


class ByteTesting: public testing::Test {
public:
    // Split in chunks
    std::vector<std::string> helloWorldAsciiBlocked1Char{{"H"}, {"e"}, {"l"},
        {"l"}, {"o"}, {","}, {" "}, {"W"}, {"o"}, {"r"}, {"l"}, {"d"}, {"!"}};
    std::vector<std::string> helloWorldAsciiBlocked2Char{{"He"}, {"ll"},
        {"o,"}, {" W"}, {"or"}, {"ld"}, {"!"}};
    std::vector<std::string> helloWorldAsciiBlocked3Char{{"Hel"}, {"lo,"},
                                                    {" Wo"}, {"rld"}, {"!"}};

    std::vector<ByteStream> helloWorldByteStreamBlocked1Byte{{0x48}, {0x65},
        {0x6c}, {0x6c}, {0x6f}, {0x2c}, {0x20}, {0x57}, {0x6f}, {0x72}, {0x6c},
        {0x64}, {0x21}};
    std::vector<ByteStream> helloWorldByteStreamBlocked2Byte{{0x48, 0x65},
        {0x6c, 0x6c}, {0x6f, 0x2c}, {0x20, 0x57}, {0x6f, 0x72}, {0x6c, 0x64},
        {0x21}};
    std::vector<ByteStream> helloWorldByteStreamBlocked3Byte{
        {0x48, 0x65, 0x6c}, {0x6c, 0x6f, 0x2c}, {0x20, 0x57, 0x6f},
        {0x72, 0x6c, 0x64}, {0x21}};


    std::string helloWorldAscii{"Hello, World!"};
    ByteStream helloWorldByteStream{0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
                                    0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21};
};

// Split in blocks
TEST_F(ByteTesting, splitInChunksString) {
    ASSERT_THAT(CB::Utils::splitInChunks(helloWorldAscii, 1), Eq(helloWorldAsciiBlocked1Char));
    ASSERT_THAT(CB::Utils::splitInChunks(helloWorldAscii, 2), Eq(helloWorldAsciiBlocked2Char));
    ASSERT_THAT(CB::Utils::splitInChunks(helloWorldAscii, 3), Eq(helloWorldAsciiBlocked3Char));
}

TEST_F(ByteTesting, splitInChunksByteStream) {
    ASSERT_THAT(CB::Utils::splitInChunks(helloWorldByteStream, 1), Eq(helloWorldByteStreamBlocked1Byte));
    ASSERT_THAT(CB::Utils::splitInChunks(helloWorldByteStream, 2), Eq(helloWorldByteStreamBlocked2Byte));
    ASSERT_THAT(CB::Utils::splitInChunks(helloWorldByteStream, 3), Eq(helloWorldByteStreamBlocked3Byte));
}




int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
