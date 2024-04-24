cmake_minimum_required(VERSION 3.7)
project(2048 C)

# 设置编译器标准为 C99
set(CMAKE_C_STANDARD 99)

# 添加源文件
set(SOURCES 
    source/2048game.c
    source/colorfulNumber.h
)

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/executable)

# 生成可执行文件
add_executable(2048 ${SOURCES})

# 测试
enable_testing()
add_test(NAME basic COMMAND 2048)

# 安装规则
install(TARGETS 2048 DESTINATION bin)
