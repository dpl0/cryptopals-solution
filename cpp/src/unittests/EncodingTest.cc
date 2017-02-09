#include <string>

#include "gmock/gmock.h"
#include "Encoding.h"

using namespace testing;

class ByteTesting: public testing::Test {
public:
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

// Coding and decoding
// Simplest case
TEST_F(ByteTesting, emptyStringsWork) {
    ASSERT_THAT(Encoding::encodeAsAscii(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(Encoding::encodeAsHex(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(Encoding::encodeAsBase64(emptyString), Eq(emptyByteStream));
}

// ASCII
TEST_F(ByteTesting, asciiToByteStream) {
    ASSERT_THAT(Encoding::encodeAsAscii(helloWorldAscii),
                                            Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToAscii) {
    ASSERT_THAT(Encoding::decodeAsAscii(helloWorldByteStream),
                                            Eq(helloWorldAscii));
}

// Hexadecimal
TEST_F(ByteTesting, hexToByteStream) {
    ASSERT_THAT(Encoding::encodeAsHex(helloWorldHex), Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToHex) {
    ASSERT_THAT(Encoding::decodeAsHex(helloWorldByteStream), Eq(helloWorldHex));
}

// Base64
TEST_F(ByteTesting, base64ToByteStream) {
    // ASSERT_THAT((ByteStream)Encoding::encodeAsBase64(text1GroupBase64), Eq(text1GroupByteStream));
    // ASSERT_THAT(Encoding::encodeAsBase64(text2GroupsBase64), Eq(text2GroupsByteStream));
    // ASSERT_THAT(Encoding::encodeAsBase64(text1Group1CharBase64), Eq(text1Group1CharByteStream));
    // ASSERT_THAT(Encoding::encodeAsBase64(helloWorldBase64), Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToBase64) {
    ASSERT_THAT(Encoding::decodeAsBase64(text1GroupByteStream), Eq(text1GroupBase64));
    ASSERT_THAT(Encoding::decodeAsBase64(text2GroupsByteStream), Eq(text2GroupsBase64));
    ASSERT_THAT(Encoding::decodeAsBase64(text1Group1CharByteStream), Eq(text1Group1CharBase64));
    ASSERT_THAT(Encoding::decodeAsBase64(text1Group2CharsByteStream), Eq(text1Group2CharsBase64));
    ASSERT_THAT(Encoding::decodeAsBase64(helloWorldByteStream), Eq(helloWorldBase64));
}


int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
