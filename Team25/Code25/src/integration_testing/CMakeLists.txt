file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(integration_testing ${srcs}
"src/TestSpPkbIntegration.cpp"
"src/TestPkbQpsIntegration.cpp"
"src/TestFullSpaSystem.cpp"






)


target_link_libraries(integration_testing spa)
