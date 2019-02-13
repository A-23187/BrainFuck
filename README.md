# BrainFuck

整体设计  
![整体设计](pic/01.png)  
并不是很标准的UML类图，就大概看看吧。*捂脸）*   

`BFuck`

字段/函数|作用
--|--
`std::vector<uint8_t> cells`|模拟纸带，即单元格数组
`int pos`|当前[伪]指针
`uint8_t get() const`|返回当前单元格的值，called in `operator<<(...)`
`void set(uint8_t)`|设置当前单元格的值，called in `operator>>(...)`
`void prev()`|指针往前（左）移动
`void next()`|指针往后（右）移动
`BFuck& operator++()`/`BFuck& operator++(int)`|当前单元格的值自增
`BFuck& operator--()`/`BFuck& operator--(int)`|当前单元格的值自减
`operator bool() const`|判断当前单元格的值是否不为0
`clear()`|将目前所有单元格的值清零，并使指针指向第一个单元格

`FuckerTemplate`

字段/函数|作用
--|--
`string stmt`|待解释的BF代码
`bfuck`|`BFuck`类型的对象
`int which`|指向当前在处理的符号
`void action()`|处理`stmt`中的每个符号，执行相应的动作
`void loop()`|当读到`[`时，对应的动作便是调用此函数
`void fuck()`|处理的入口
`bool dead() const`|当`stmt`为`exit`/`quit`/`bye`时，表示关闭解释器。该函数用于判断`stmt`是否属于上面的情况
`operator bool() const`|判断`stmt`中的左右括号（`[`、`]`）是否匹配
`operator>>(...)`|从`stdin`中获取代码，或者从文件流中读取


在Sublime Text 中为BrainFuck添加语法高亮支持  
1. [BrainFuck.sublime-syntax](https://github.com/A-23187/BrainFuck/blob/master/others/BrainFuck.sublime-syntax)  
2. [BrainFuck.tmTheme](https://github.com/A-23187/BrainFuck/blob/master/others/BrainFuck.tmTheme)  

更多介绍  
[BrainFuck之旅 - 知乎](https://zhuanlan.zhihu.com/p/56566363)  

TODO  
- [ ] 实现可视化功能
- [ ] 基于LLVM实现为编译器
- [ ] JIT