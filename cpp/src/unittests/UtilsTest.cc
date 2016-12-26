#include <string>

#include "gmock/gmock.h"
#include "Utils.h"

using namespace testing;
using namespace std;

class ByteTesting: public testing::Test {
public:
    string emptyString {""};
    ByteStream emptyByteStream {};

    string helloWorldAscii{"Hello, World!"};
    string helloWorldHex{"48656c6c6f2c20576f726c6421"};
    string helloWorldBase64{"SGVsbG8sIFdvcmxkIQ=="};
    ByteStream helloWorldByteStream{{0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20,
                                     0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21}};
};

TEST_F(ByteTesting, returnsEmtpyString) {
    ASSERT_THAT(Utils::hexToByteStream(emptyString), Eq(emptyByteStream));
}


int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
