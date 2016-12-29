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
};

TEST_F(ByteTesting, returnsEmtpyString) {
    ASSERT_THAT(Utils::hexToByteStream(emptyString), Eq(emptyByteStream));
}


int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
