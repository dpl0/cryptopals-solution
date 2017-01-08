#include <string>

#include "gmock/gmock.h"
#include "Utils.h"

using namespace testing;

class ByteTesting: public testing::Test {
public:
    std::string emptyString {""};
    ByteStream emptyByteStream {};

    std::string helloWorldAscii{"Hello, World!"};
    std::string helloWorldHex{"48656c6c6f2c20576f726c6421"};
    std::string helloWorldBase64{"SGVsbG8sIFdvcmxkIQ=="};
    ByteStream helloWorldByteStream{0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
                                    0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21};
};

TEST_F(ByteTesting, emptyStringsWork) {
    ASSERT_THAT(Utils::encodeAsAscii(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(Utils::encodeAsHex(emptyString), Eq(emptyByteStream));
    ASSERT_THAT(Utils::encodeAsBase64(emptyString), Eq(emptyByteStream));
}

TEST_F(ByteTesting, asciiToByteStream) {
    ASSERT_THAT(Utils::encodeAsAscii(helloWorldAscii),
                                            Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToAscii) {
    ASSERT_THAT(Utils::decodeAsAscii(helloWorldByteStream),
                                            Eq(helloWorldAscii));
}

TEST_F(ByteTesting, hexToByteStream) {
    ASSERT_THAT(Utils::encodeAsHex(helloWorldHex), Eq(helloWorldByteStream));
}

TEST_F(ByteTesting, byteStreamToHex) {
    ASSERT_THAT(Utils::decodeAsHex(helloWorldByteStream), Eq(helloWorldHex));
}

// TEST_F(ByteTesting, base64ToByteStream) {
//     ASSERT_THAT(Utils::encodeAsBase64(helloWorldBase64), Eq(helloWorldByteStream));
// }

// TEST_F(ByteTesting, byteStreamToBase64) {
//     ASSERT_THAT(Utils::decodeAsBase64(helloWorldByteStream), Eq(helloWorldBase64));
// }



int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
