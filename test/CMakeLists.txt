##############################################
# Test Source
##############################################
SET(TEST_SRC
    test_main.cpp
    test_url_encoder.cpp
)

SET(TEST_LIBS
    url_encoder
)

set(COMPILER_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Wconversion
    -Wsign-conversion
    -Wformat=2
    -g
    -O2
)

##############################################
# Unit Test Executable (Catch2)
##############################################
add_executable(url_encoder_test ${TEST_SRC})
target_link_libraries(url_encoder_test PUBLIC url_encoder)
target_compile_options(url_encoder_test PUBLIC ${COMPILER_FLAGS})
add_test(NAME url_encoder_test COMMAND $<TARGET_FILE:url_encoder_test>)


##############################################
# Curl comparison test
# Only enabled if libcurl is available
##############################################
find_package(CURL QUIET)

if(CURL_FOUND)
    add_library(CURL UNKNOWN IMPORTED)
    target_sources(url_encoder_test PRIVATE test_curl_compare.cpp)
    target_link_libraries(url_encoder_test PRIVATE curl)
else(CURL_FOUND)
    message(WARNING "Curl not found. Unable to do curl compare.")
endif(CURL_FOUND)

##############################################
# Generate code coverage
##############################################
if(CODE_COVERAGE)
    target_compile_options(url_encoder_test PUBLIC -O0 --coverage)
    target_link_libraries(url_encoder_test PUBLIC gcov --coverage)
endif(CODE_COVERAGE)
