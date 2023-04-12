## Lua-Config

这个东西可以使用lua作为配置文件。相比较于其他静态的文本语言，lua是脚本语言，它本身可以被执行，所以可以允许更多的操作，例如变量赋值和修改，if-else分支等等。

另外可以对它扩展自定义函数，例如定义include函数，使得可以包含另一个lua文件，从而可以从其他文件拉取配置，并做自定义修改和补充等等。

例子1: 简单配置

```lua
return {
    name = "tom",
    age = 10,
    score = 99.9,
}
```

例子2: 复杂配置

```lua
include "relative_path/other.lua"  # 导入另一个table
other.name = "other_name"          # 修改内容
name_prefix = "prefix"             # 定义局部变量
myconfig = {
    info = other,                  # 整个table作为一个值
    name = name_prefix.."good"     # 字符串拼接
}
return myconfig
```

### lua的相关语法

lua用table表示一个表或数组，而且不要求数组元素类型一致。

每个lua语句后面不需要分号，但一个table里面的内容用逗号隔开，最后一项可以有逗号可以没有。

整个lua文件必须return一个table作为结果。

### build

需要安装：
```
build-essentials
cmake
liblua5.2-dev
gtest
glog
```

### demo
参考real_test.cc单元测试。

### todo

在lua里面能否省掉return语句？测试下面的可以，那么可以在读lua文件后自己前后加return{}括起来。

```
return {
    include "other.lua",
    hour = 10,
}
```
但这样的话include语句后面要加逗号。

当然如果肯出力气，在lua读文件后可以做很多字符串的处理，这样格式都可以自己控制。

增加INSTALL语句，使得安装h文件和库文件。

增加多级查询功能，例如GetInt("item1/age")这样的。