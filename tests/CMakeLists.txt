if (BUILD_TESTING)
    find_package (Boost COMPONENTS unit_test_framework REQUIRED)

    add_executable(bulk_test
            BulkReader.test.cpp
            ${SOURCE_PATH}/BulkReader.h
            ${SOURCE_PATH}/BulkReader.cpp
            )

    add_executable(subscribers_test
            Subscribers.test.cpp
            ${SOURCE_PATH}/Subscribers.h
            ${SOURCE_PATH}/Subscribers.cpp
            )

    set_target_properties(bulk_test subscribers_test PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
            INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIRS};${SOURCE_PATH}"
            LINK_LIBRARIES ${Boost_LIBRARIES}
            )

    add_test(BulkTest bulk_test)
    add_test(SubscribersTest subscribers_test)
endif()
