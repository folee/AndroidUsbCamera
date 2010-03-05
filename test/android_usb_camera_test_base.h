#ifndef ANDROID_USB_CAMERA_TEST_BASE_H
#define ANDROID_USB_CAMERA_TEST_BASE_H

#include <QTest>
#include <gmock/gmock.h>

#define GQTEST_MAIN(TestObject) \
int main(int argc, char *argv[]) \
{ \
    QCoreApplication app(argc, argv); \
    TestObject tc; \
    testing::InitGoogleMock(&argc, argv); \
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners(); \
    listeners.Append(new MockReport); \
    return QTest::qExec(&tc, argc, argv); \
}

using namespace testing;


class MockReport : public EmptyTestEventListener {
  virtual void OnTestPartResult(const TestPartResult& test_part_result) {
    if(test_part_result.failed() || test_part_result.fatally_failed() ) {
      QTest::qFail(test_part_result.message(), test_part_result.file_name() , test_part_result.line_number());
    }
  }
};

#endif
