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
    ASSERT_THAT(Debug::byteToBinaryString(one), Eq(oneString));
    // ASSERT_THAT(Utils::encodeAsBase64(emptyString), Eq(emptyByteStream));
}

TEST_F(DebugTesting, byteStreamToString) {
    ASSERT_THAT(Debug::byteStreamToBinaryString(twentyOneTwice), Eq(twentyOneString));
    // ASSERT_THAT(Utils::encodeAsBase64(emptyString), Eq(emptyByteStream));
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
    std::vector<std::string> helloWorldAsciiBlocked4Char{{"Hell"}, {"o, W"},
                                                         {"orld"}, {"!"}};

    std::vector<ByteStream> helloWorldByteStreamBlocked1Byte{{0x48}, {0x65},
        {0x6c}, {0x6c}, {0x6f}, {0x2c}, {0x20}, {0x57}, {0x6f}, {0x72}, {0x6c},
        {0x64}, {0x21}};
    std::vector<ByteStream> helloWorldByteStreamBlocked2Byte{{0x48, 0x65},
        {0x6c, 0x6c}, {0x6f, 0x2c}, {0x20, 0x57}, {0x6f, 0x72}, {0x6c, 0x64},
        {0x21}};
    std::vector<ByteStream> helloWorldByteStreamBlocked3Byte{
        {0x48, 0x65, 0x6c}, {0x6c, 0x6f, 0x2c}, {0x20, 0x57, 0x6f},
        {0x72, 0x6c, 0x64}, {0x21}};
    std::vector<ByteStream> helloWorldByteStreamBlocked4Byte{{0x48, 0x65,
        0x6c, 0x6c}, {0x6f, 0x2c, 0x20, 0x57}, {0x6f, 0x72, 0x6c, 0x64},
        {0x21}};

    // Encoding and decoding
    std::string emptyString {""};
    ByteStream emptyByteStream {};

    std::string helloWorldAscii{"Hello, World!"};
    std::string helloWorldHex{"48656c6c6f2c20576f726c6421"};
    std::string helloWorldBase64{"SGVsbG8sIFdvcmxkIQ=="};
    ByteStream helloWorldByteStream{0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
                                    0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21};

    std::string text1GroupAscii{"Hel"};
    std::string text1GroupHex{"48656c"};
    std::string text1GroupBase64{"SGVs"};
    ByteStream text1GroupByteStream{0x48, 0x65, 0x6c};

    std::string text1Group1CharAscii{"Hell"};
    std::string text1Group1CharHex{"48656c6c"};
    std::string text1Group1CharBase64{"SGVsbA=="};
    ByteStream text1Group1CharByteStream{0x48, 0x65, 0x6c, 0x6c};

    std::string text1Group2CharsAscii{"Hello"};
    std::string text1Group2CharsHex{"48656c6c6f"};
    std::string text1Group2CharsBase64{"SGVsbG8="};
    ByteStream text1Group2CharsByteStream{0x48, 0x65, 0x6c, 0x6c, 0x6f};

    std::string text2GroupsAscii{"Hell"};
    std::string text2GroupsHex{"48656c6c"};
    std::string text2GroupsBase64{"SGVsbA=="};
    ByteStream text2GroupsByteStream{0x48, 0x65, 0x6c, 0x6c};
};

// Split in blocks
TEST_F(ByteTesting, splitInChunksString) {
    ASSERT_THAT(Utils::splitInChunks(helloWorldAscii, 1), Eq(helloWorldAsciiBlocked1Char));
    ASSERT_THAT(Utils::splitInChunks(helloWorldAscii, 2), Eq(helloWorldAsciiBlocked2Char));
    ASSERT_THAT(Utils::splitInChunks(helloWorldAscii, 3), Eq(helloWorldAsciiBlocked3Char));
    ASSERT_THAT(Utils::splitInChunks(helloWorldAscii, 4), Eq(helloWorldAsciiBlocked4Char));
}

TEST_F(ByteTesting, splitInChunksByteStream) {
    ASSERT_THAT(Utils::splitInChunks(helloWorldByteStream, 1), Eq(helloWorldByteStreamBlocked1Byte));
    ASSERT_THAT(Utils::splitInChunks(helloWorldByteStream, 2), Eq(helloWorldByteStreamBlocked2Byte));
    ASSERT_THAT(Utils::splitInChunks(helloWorldByteStream, 3), Eq(helloWorldByteStreamBlocked3Byte));
    ASSERT_THAT(Utils::splitInChunks(helloWorldByteStream, 4), Eq(helloWorldByteStreamBlocked4Byte));
}


// Coding and decoding
// Simplest case
TEST_F(ByteTesting, emptyStringsWork) {
    ASSERT_THAT(Utils::encodeAsAscii(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(Utils::encodeAsHex(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(Utils::encodeAsBase64(emptyString), Eq(emptyByteStream));
}

// ASCII
TEST_F(ByteTesting, asciiToByteStream) {
    ASSERT_THAT(Utils::encodeAsAscii(helloWorldAscii),
                                            Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToAscii) {
    ASSERT_THAT(Utils::decodeAsAscii(helloWorldByteStream),
                                            Eq(helloWorldAscii));
}

// Hexadecimal
TEST_F(ByteTesting, hexToByteStream) {
    ASSERT_THAT(Utils::encodeAsHex(helloWorldHex), Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToHex) {
    ASSERT_THAT(Utils::decodeAsHex(helloWorldByteStream), Eq(helloWorldHex));
}

// Base64
TEST_F(ByteTesting, base64ToByteStream) {
    // ASSERT_THAT((ByteStream)Utils::encodeAsBase64(text1GroupBase64), Eq(text1GroupByteStream));
    // ASSERT_THAT(Utils::encodeAsBase64(text2GroupsBase64), Eq(text2GroupsByteStream));
    // ASSERT_THAT(Utils::encodeAsBase64(text1Group1CharBase64), Eq(text1Group1CharByteStream));
    // ASSERT_THAT(Utils::encodeAsBase64(helloWorldBase64), Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToBase64) {
    ASSERT_THAT(Utils::decodeAsBase64(text1GroupByteStream), Eq(text1GroupBase64));
    ASSERT_THAT(Utils::decodeAsBase64(text2GroupsByteStream), Eq(text2GroupsBase64));
    ASSERT_THAT(Utils::decodeAsBase64(text1Group1CharByteStream), Eq(text1Group1CharBase64));
    ASSERT_THAT(Utils::decodeAsBase64(text1Group2CharsByteStream), Eq(text1Group2CharsBase64));
    ASSERT_THAT(Utils::decodeAsBase64(helloWorldByteStream), Eq(helloWorldBase64));
}



int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
