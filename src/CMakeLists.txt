set(LIBRARY_SOURCES UBigInt.cc fft/my-fft.cc)
set(LIBRARY_INCLUDES "./" "fft/")

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})

add_subdirectory(fft)
