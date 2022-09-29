# 功能

只需要复制 leetcode 中的测试用例到本地 testcases.txt 文件，复制 Solution() 类到本地 main.cpp 文件，main.cpp 文件能够逐行解析输入变量，从而实现在本地调试的功能。

[项目路径](https://github.com/aiyolo/leetcode-debug)

# 演示

[link](https://p1.meituan.net/dpplatform/18253d49b9e0d1323868e34697f5f4248365722.gif)

![](https://p1.meituan.net/dpplatform/18253d49b9e0d1323868e34697f5f4248365722.gif)

# 使用方法

1. 复制 Solution 类到 main.cpp
2. 复制测试用例数据到 testcase.txt
3. 定义类成员参数，调用 parse(cin, …) 解析变量
4. 默认使用 cmake 编译，c++ 标准要求 c++17 及以上

# 原理

大部分处理输入数据的函数来自 leetcode, 目前支持处理如下的数据类型，这些类型应对大部分测试用例都是可以的。

- `int`
- `string`
- `vector<int>`
- `vector<vector<int>>`
- `vector<string>`
- `ListNode*`
- `TreeNode*`
