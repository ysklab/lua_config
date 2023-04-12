我们尝试分析。里面的东西可以参考test_lua这个项目。

lua相关的API操纵的是一个栈。用-1表示栈顶元素index。

#### 在构造函数的时候，有下面几个操作

```
lua_register 注册自定义函数，使得后续lua执行到相关语句时，会调用指定的函数
luaL_loadstring 加载一个lua脚本字符串到栈，作为栈的一个元素，但不执行
lua_pcall 执行栈内的某个函数元素，需要指定它的参数个数和返回值个数。个人理解，常规情况是函数对象入栈，然后各个参数入栈，然后执行后，把函数和各个参数弹出，把结果入栈。
```

所以构造函数做了：
- 注册自定义函数，使得它们后续被正确调用；
- 加载lua脚本作为一个函数对象到栈；
- 执行这个函数对象，不需要参数，返回一个对象。因为每个lua脚本都有return table的操作，这时候栈里面只有一个table元素。

#### 查询某个元素的操作
以GetDouble为例，它做了：

##### 检查key是否存在：CheckHasKeyAndReference

它执行了CheckHasKey然后做了计数统计。而CheckHasKey核心是HasKey，后者核心是HasKeyOfType，而它里面的核心操作是：
- PushValue函数push指定的key到栈，key是模板类型，猜测可以是string或整数，对应table的按名查找和按index查找。
- lua_rawget指定一个table元素，以栈顶作为key进行table的查找。清理key然后把结果入栈。如果查找失败则栈顶设为特殊值。
- lua_pop清理栈顶

##### 查询key放于栈顶：GetValueFromLuaTable

它执行了下面步骤，这和检查key的操作很多重合，可以参考那一节文档的内容。
- PushValue把push指定key到栈
- lua_rawget指定table去查找栈顶key，清理key并把结果入栈

##### 弹出栈顶元素：PopDouble
里面操作很简单：
- lua_tonumber解析栈顶元素成number类型（包括整数浮点）
- lua_pop弹出栈顶的N个元素

#### 查询并拷贝某个子Dictionary
它的操作是拷贝，而非yaml-cpp里面的引用。它会创建新的Dictionary对象，其内部的lua栈也会被拷贝。另外，一个Dic对象里面还有FileResolver对象，它的指针也被放在了内部lua栈内。