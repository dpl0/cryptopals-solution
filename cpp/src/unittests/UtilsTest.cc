#include <string>

#include "gmock/gmock.h"
#include "Utils.h"

using namespace testing;
using namespace std;

class ByteTesting: public testing::Test {
public:
    string emptyString {""};
    ByteStream emptyByteStream {""};
};

TEST_F(ByteTesting, returnsEmtpyString) {
    ASSERT_THAT(Utils::hexToByteStream(emptyString), Eq(emptyString));
}

int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
