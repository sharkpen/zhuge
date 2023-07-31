/*
 File Name: channel.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-07-29
 Last Modified: 2023-07-29
*/
#pragma once
#include <stdint.h>
namespace croot {
namespace lltg {
class Channel {
  public:
    // Channel 是否是活的 返回值为0 
    int32_t IsActive();
    // 读取长度为len的内存，本身为零拷贝，如果数据包可以提供长度为len的数据返回指针，校验由Channel完成，对其的使用比较危险不能越界超过len
    // 如果数据没有准备好 返回null
    char* ReadBlock(int32_t len);
    // 返回值为 0表示没有新增数据 -1 表示网络故障 （这个要自己使用心跳包实现）-2 表示对方主动断开（要使用操作系统协议栈）
    int32_t Read(int32_t len, char* dst);
};
}  // namespace lltg
}  // namespace croot

