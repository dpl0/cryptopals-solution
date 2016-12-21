#include <string>

#include "gmock/gmock.h"
#include "Utils.h"

using namespace testing;

class ByteTesting: public testing::Test {
public:
    std::string emptyString = "";
};

TEST_F(ByteTesting, returnsEmtpyString) {
    ASSERT_THAT(Utils::hexToBase64(emptyString), Eq(""));
}

// TEST_F(ByteTesting, EmptyWhenCreated) {
//     ASSERT_THAT(bytes.empty(), Eq(true));
// }

int main(int argc, char *argv[]) {
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
