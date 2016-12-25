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
    string helloWorldHex{"Hello, World!"};
    string helloWorldBase64{"Hello, World!"};
    // ByteStream helloWorldByteStream{"Hello, World!"}
};

TEST_F(ByteTesting, returnsEmtpyString) {
    ASSERT_THAT(Utils::hexToByteStream(emptyString), Eq(emptyByteStream));
}

TEST_F(ByteTesting, asciiToHexWorks) {
    ASSERT_THAT(Utils::asciiToByteStream(emptyString), Eq(emptyByteStream));
}


int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
