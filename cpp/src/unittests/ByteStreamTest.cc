#include <string>

#include "gmock/gmock.h"
#include "ByteStream.hpp"

using namespace testing;

class ByteTesting: public testing::Test {
public:
    // Encoding and decoding
    std::string emptyString {""};
    CB::ByteStream emptyData {};

    std::string helloWorldAscii{"Hello, World!"};
    std::string helloWorldHex{"48656c6c6f2c20576f726c6421"};
    std::string helloWorldBase64{"SGVsbG8sIFdvcmxkIQ=="};
    CB::ByteStream helloWorldData{0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
                              0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21};

    std::string text1GroupAscii{"Hel"};
    std::string text1GroupHex{"48656c"};
    std::string text1GroupBase64{"SGVs"};
    CB::ByteStream text1GroupData{0x48, 0x65, 0x6c};

    std::string text1Group1CharAscii{"Hell"};
    std::string text1Group1CharHex{"48656c6c"};
    std::string text1Group1CharBase64{"SGVsbA=="};
    CB::ByteStream text1Group1CharData{0x48, 0x65, 0x6c, 0x6c};

    std::string text1Group2CharsAscii{"Hello"};
    std::string text1Group2CharsHex{"48656c6c6f"};
    std::string text1Group2CharsBase64{"SGVsbG8="};
    CB::ByteStream text1Group2CharsData{0x48, 0x65, 0x6c, 0x6c, 0x6f};

    std::string text2GroupsAscii{"Hell"};
    std::string text2GroupsHex{"48656c6c"};
    std::string text2GroupsBase64{"SGVsbA=="};
    CB::ByteStream text2GroupsData{0x48, 0x65, 0x6c, 0x6c};
};

// Coding and decoding
// Simplest case
TEST_F(ByteTesting, emptyStringsWork) {
    ASSERT_THAT(CB::Utils::encodeAsAscii(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(CB::Utils::encodeAsHex(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(CB::Utils::encodeAsBase64(emptyString), Eq(emptyByteStream));
}

// ASCII
TEST_F(ByteTesting, asciiToByteStream) {
    ASSERT_THAT(CB::Utils::encodeAsAscii(helloWorldAscii),
                                            Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToAscii) {
    ASSERT_THAT(CB::Utils::decodeAsAscii(helloWorldByteStream),
                                            Eq(helloWorldAscii));
}

// Hexadecimal
TEST_F(ByteTesting, hexToByteStream) {
    ASSERT_THAT(CB::Utils::encodeAsHex(helloWorldHex), Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToHex) {
    ASSERT_THAT(CB::Utils::decodeAsHex(helloWorldByteStream), Eq(helloWorldHex));
}

// Base64
TEST_F(ByteTesting, base64ToByteStream) {
    // ASSERT_THAT((ByteStream)CB::Utils::encodeAsBase64(text1GroupBase64), Eq(text1GroupByteStream));
    // ASSERT_THAT(CB::Utils::encodeAsBase64(text2GroupsBase64), Eq(text2GroupsByteStream));
    // ASSERT_THAT(CB::Utils::encodeAsBase64(text1Group1CharBase64), Eq(text1Group1CharByteStream));
    // ASSERT_THAT(CB::Utils::encodeAsBase64(helloWorldBase64), Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToBase64) {
    ASSERT_THAT(CB::Utils::decodeAsBase64(text1GroupByteStream), Eq(text1GroupBase64));
    ASSERT_THAT(CB::Utils::decodeAsBase64(text2GroupsByteStream), Eq(text2GroupsBase64));
    ASSERT_THAT(CB::Utils::decodeAsBase64(text1Group1CharByteStream), Eq(text1Group1CharBase64));
    ASSERT_THAT(CB::Utils::decodeAsBase64(text1Group2CharsByteStream), Eq(text1Group2CharsBase64));
    ASSERT_THAT(CB::Utils::decodeAsBase64(helloWorldByteStream), Eq(helloWorldBase64));
}


int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}