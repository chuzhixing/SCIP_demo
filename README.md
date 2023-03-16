# SCIP_demo

# 仓库说明

本仓库，搭建了一个调用SCIP可执行库的c++的一个解决方案（solution）。  
SCIP版本：8.0.3。  
同时，它包含一些求解器SCIP的cpp API示中的例子。是我学习使用的，它们相比于官网的demo、例子更加简洁，更加方便上手cpp API的用法。  
关于“调用SCIP C++接口，viusal studio项目工程搭建”的步骤，可以参考下面bilibili视频教程：  
https://www.bilibili.com/video/BV1PX4y1Q77C/    
SCIP C++ API入门级教程合集B站观看入口：https://space.bilibili.com/412241271/channel/seriesdetail?sid=3100320  

# 代码

# 代码说明

1 SCIP_demo/hello_world.cpp
它是SCIP入门级的例子，非常简单。这个demo程序来源于如下的博客
demo程序地址：https://blog.csdn.net/zx_glave/article/details/128398062
目标函数说明：  

```shell
obj min (2*x + 3*y)
s.t. 2*x+3*y >= 7
```

2 SCIP_demo/quadratic_nonlinear_constraint_demo_01.cpp
它是一个约束项为二次非线性约束的简单例子。
目标函数说明：  

```shell
obj max (x + y)
s.t.
    x^2 + 2*x*y + y^2 <= 9
    0 =< x <= 10
    0 =< y <= 10
```

3 SCIP_demo/quadratic_nonlinear_constraint_demo_02.cpp
它是一个约束项为二次非线性约束的简单例子，当二次项只有一个时，不用额外定义数组的简单写法。
目标函数说明：  

```shell
obj max (x + y)
s.t.
    x*y <= 9
    0 =< x <= 10
    0 =< y <= 10
```

4 SCIP_demo/demo_cons_with_sqrt_and_sum.cpp
它是一个约束项中，带有根号函数的例子，演示约束项中带有函数的情况（比如根号函数、sin函数、绝对值函数）的SCIP C++ API的用法。目标函数说明如下：

```shell
obj min t
s.t. 
    t * [(1 - y_{i+1})^0.5 + (1 - y_{i})^0.5] >= 5
    0< t <+inf
    0 =< y_{i+1} <= 1
    0 =< y_{i} <= 1
```

5 SCIP_demo/cons_with_sqrt_and_sum_and_quadratic_nonlinear_demo
它是一个约束项中，带有根号函数的例子，演示约束项中带有函数的情况（比如根号函数、sin函数、绝对值函数）的SCIP C++ API的用法。目标函数说明如下：  
目标函数如下所示
```
obj min t_i 
s.t. t_i * [sqrt{(1 - y_{i+1})} + sqrt{(1 - y_{i})}] - sqrt{(x_{i+1} - x_{i})^2 + (y_{i+1} - y_{i})^2} >= 0 
	0 = < t_i  
	0 = < y_{ i + 1 } <= 1 
	0 = < y_{ i } <= 1  
	0 = < x_{ i + 1 } <= 1  
	0 = < x_{ i } <= 1  
```