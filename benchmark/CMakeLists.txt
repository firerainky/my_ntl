set(BENCHMARK_MAIN FHEBenchmark)
set(BENCHMARK_SOURCES 
  UBigIntBenchmarks.cc
)
set(BENCHMARK_INCLUDES ./)

add_executable(${BENCHMARK_MAIN} ${BENCHMARK_SOURCES})
target_include_directories(${BENCHMARK_MAIN} PUBLIC ${BENCHMARK_INCLUDES})
target_link_libraries(${BENCHMARK_MAIN} PRIVATE ${LIBRARY_NAME} benchmark::benchmark)