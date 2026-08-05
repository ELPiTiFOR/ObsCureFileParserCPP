cmake_minimum_required(VERSION 3.15)

project(ObsCureFileParserCPP CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
file(GLOB_RECURSE OCFP_LOGIC "src/*/*.cc" "src/commands.cc")
file(GLOB_RECURSE OCFP_TESTS "test/*/*.cc")
file(GLOB_RECURSE OCFP_GUI "src/gui/*.cc")
list(FILTER OCFP_LOGIC EXCLUDE REGEX "/src/gui/")

# Logic library
add_library(ocfp_logic ${OCFP_LOGIC})
target_include_directories(ocfp_logic PRIVATE src/)
target_compile_options(ocfp_logic PRIVATE -g)

# GUI library
add_library(ocfp_gui ${OCFP_GUI})
set_target_properties(ocfp_gui PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(ocfp_gui PRIVATE
    src/
    deps/raylib/include
    deps/raygui/include
)
# TODO: use `-g` only when we want to debug
target_compile_options(ocfp_gui PRIVATE -g)

# Test library
add_library(ocfp_tests ${OCFP_TESTS})
target_include_directories(ocfp_tests PRIVATE src/ test/)
target_compile_options(ocfp_tests PRIVATE -g)

# CLI
add_executable(ObsCureFileParser src/main.cc)
target_include_directories(ObsCureFileParser PRIVATE src/)
target_link_libraries(ObsCureFileParser PRIVATE ocfp_logic)

# GUI
add_executable(ObsCureFileParserGUI src/main_gui.cc)
target_include_directories(ObsCureFileParserGUI PRIVATE
    src/
    deps/raylib/include
    deps/raygui/include
)
find_library(RAYLIB_BIN
    NAMES raylib
    PATHS "${CMAKE_SOURCE_DIR}/deps/raylib/lib"
    NO_DEFAULT_PATH
    REQUIRED
)
target_link_libraries(ObsCureFileParserGUI PRIVATE
    ocfp_logic
    ocfp_gui
    ${RAYLIB_BIN}
    winmm
    opengl32
    gdi32
)

# Tests
add_executable(OCFPTest "test/test.cc")
target_include_directories(OCFPTest PRIVATE src/ test/)
target_link_libraries(OCFPTest PRIVATE
    ocfp_tests
    ocfp_logic
)
target_compile_options(OCFPTest PRIVATE
    -g
)

target_compile_options(ObsCureFileParser PRIVATE
    -Wall
    -Wextra
    -Wold-style-cast
    -Werror
    -pedantic
    -g
)

target_compile_options(ObsCureFileParserGUI PRIVATE
    -Wall
    -Wextra
    -Wold-style-cast
    -Werror
    -pedantic
    -g
    -Wl,--subsystem,windows
)

if(WIN32)
    set_target_properties(ObsCureFileParserGUI PROPERTIES WIN32_EXECUTABLE TRUE)
endif()