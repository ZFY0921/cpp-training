# 1. 收集当前 src 目录下的所有源文件
# 如果你只有 hello.cpp，这样写没问题。
# 如果你后面还会添加 Executor.cpp 等新文件，可以直接把它们加在下面，或者用 file(GLOB ...) 自动扫描。
set(SRC_FILES
    ExecutorImpl.cpp
    # Executor.cpp  <-- 如果你有其他源文件，像这样加进来即可
)

# 2. 创建一个名为 training_lib 的静态库 (STATIC)
# 这样可以把你的核心代码打包，方便 tests 目录下的测试代码调用
add_library(training_lib STATIC ${SRC_FILES})

# 3. 配置头文件搜索路径
# 因为你的源文件可能通过 #include "hello.h" 引用了 include 目录下的文件，
# 所以需要把 include 目录暴露出去。
# PUBLIC 关键字的作用是：不仅 src 自己能用，之后链接了 training_lib 的 tests 也能自动找到这些头文件
target_include_directories(training_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)