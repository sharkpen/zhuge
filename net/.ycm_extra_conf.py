import os
import ycm_core

# 编译器标志
flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-std=c++17',
    '-I./include',      # 添加头文件搜索路径
    '-I./src',          # 添加源代码搜索路径
]

# 获取编译器标志的方法
def FlagsForFile(filename, **kwargs):
    return {
        'flags': flags,
        'do_cache': True
    }
