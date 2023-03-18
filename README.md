# SCIP_demo

## 仓库说明

本仓库，搭建了一个调用SCIP可执行库的c++的一个解决方案（solution）。  
SCIP版本：8.0.3。  
同时，它包含一些求解器SCIP的cpp API示中的例子。是我学习使用的，它们相比于官网的demo、例子更加简洁，更加方便上手cpp API的用法。  
关于“调用SCIP C++接口，viusal studio项目工程搭建”的步骤，可以参考下面bilibili视频教程：  
https://www.bilibili.com/video/BV1PX4y1Q77C/    
SCIP C++ API入门级教程合集B站观看入口：https://space.bilibili.com/412241271/channel/seriesdetail?sid=3100320  

## 代码说明

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

# 调用SCIP C++接口，viusal studio项目工程搭建（For新手）

## 搭建步骤

1 下载与安装SCIP官网编译好的包，得到inluce、bin、lib、dll文件。
面用到的include、bin、lib、dll都来自于SCIP的在windows下的安装目录内容。如果是32位的电脑，则安装，则安装32位的版本。如果是64位的电脑。则安装64位的包。

2 新建一个vs console app工程。

3 对main.cpp中的内容，替换成scip的例子。这个例子来自于下面的网页。
https://blog.csdn.net/zx_glave/article/details/128398062 (在C++中使用SCIP求解器-CSDN博客)

4 按照下面网页，总结的步骤，分别配置头文件、lib目录、放置dll。
https://segmentfault.com/a/1190000043500985 (c++ - Visual studio配置第三方库的步骤总结 - Java与大数据技术 - SegmentFault 思否)

配置lib依赖时，需要用到的lib包名。

```
bliss.lib
libpapilo-core.lib
libscip.lib
libsoplex-pic.lib
libsoplex.lib
libsoplexshared.lib
zimpl-pic.lib
zimpl.lib
```

5 运行测试。

注意事项：SCIP预编译包的位数，要与我们的vs工程属性配置中的platform，界面中的platform保持一致。



本博客配套视频：
https://www.bilibili.com/video/BV1PX4y1Q77C/?spm_id_from=333.337.search-card.all.click&vd_source=5e593ed8281413edf2f57fabda736741 (调用SCIP C++接口，viusal studio项目工程搭建（For新手）_哔哩哔哩_bilibili)

## 参考文献

https://blog.csdn.net/clever101/article/details/108945216 (在windows平台上编译SCIP_scip 配置 windows_clever101的博客-CSDN博客)

https://www.youtube.com/watch?v=QpfIkVDKxY8 (How to compile and include CBC from Coin-or using Windows and Visual Studio (for Beginners))

> 参考了其中，如何在自己的vs项目中，如何加入include与lib目录。

http://zhaoxuhui.top/blog/2020/12/27/visual-studio-cpp-dll.html (利用Visual Studio2010打包C++代码成动态链接库DLL文件)

> 参考了dll文件放到生成exe所在的目录，否则还是会报依赖找不到的错误。

https://blog.csdn.net/zx_glave/article/details/128398062 (在C++中使用SCIP求解器_zx_glave的博客-CSDN博客)

> 有一个SCIP入门级的demo程序。

https://blog.csdn.net/clever101/article/details/108945216 (在windows平台上编译SCIP_scip 配置 windows_clever101的博客-CSDN博客)

https://www.cnblogs.com/dengfaheng/p/10041488.html (SCIP | 数学规划求解器SCIP超详细的使用教程 - 短短的路走走停停 - 博客园)

优秀的例子：
https://github.com/CGudapati/SCIP_CPP_examples (CGudapati/SCIP_CPP_examples: A collection of SCIP Optimization Software modeling examples in C++)
https://www.cgudapati.com/integer-programming/2019/12/15/Getting-Started-With-SCIP-Optimization-Suite.html (Getting Started with SCIP optimization in C++: A toy example)
https://blog.csdn.net/weixin_29215391/article/details/112117377 (c++ 非线性规划_SCIP混合整数规划框架简介_Eleny君君的博客-CSDN博客)