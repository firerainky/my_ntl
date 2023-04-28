set(TEST_MAIN unittests)
set(TEST_SOURCES
  UBigIntTests.cc
  AddWithCarryTests.cc
  CeilIntTests.cc
)
set(TEST_INCLUDES ./)

add_executable(${TEST_MAIN} ${TEST_SOURCES})
target_include_directories(${TEST_MAIN} PUBLIC ${TEST_INCLUDES})
target_link_libraries(${TEST_MAIN} PRIVATE ${LIBRARY_NAME} GTest::GTest)
