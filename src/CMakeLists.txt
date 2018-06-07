# make executable file for application
add_executable(bulk
        main.cpp
        BulkReader.h
        BulkReader.cpp
        Subscribers.h
        Subscribers.cpp
        )

set_target_properties(bulk PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

install(TARGETS bulk RUNTIME DESTINATION bin)
