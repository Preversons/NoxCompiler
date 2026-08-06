# NoxCompiler
一个适用于BrainF**k的编译器

## 0.免责声明

本软件（NoxCompiler）将 MinGW-w64 (v16.1.0) 作为辅助编译工具集成于安装包中。

1. 独立性声明：MinGW-w64 是一个独立的开源工具集。本软件作者仅对其进行分发，不参与该工具内部逻辑的开发与维护。
2. 质量保证：该工具按“现状”（AS IS）提供。我们不对该工具在特定硬件或软件环境下的兼容性、稳定性或性能作出任何形式的保证。
3. 责任限制：在任何情况下，本软件作者均不对因使用或无法使用该 MinGW 工具而导致的任何直接、间接或特殊损失负责，即使已被告知发生此类损害的可能性。
4. 知识产权：MinGW-w64 的知识产权属于其贡献者及自由软件基金会（FSF），与本软件作者无关。

源代码获取：
根据 GNU General Public License 的要求，您有权获取您收到的该 MinGW 二进制文件所对应的完整源代码。
您可以通过以下方式获取该部分源代码：
- 直接下载：https://mirror.msys2.org/mingw/sources/mingw-w64-gcc-16.1.0-5.src.tar.zst
- （或者：访问 https://repo.msys2.org/mingw/sources/ 寻找对应版本）

## 1.这是什么
这是一个能够编译BrainF__k源代码的编译器，将BrainF__k源码编译为.cpp文件，再通过其中集成的MinGW编译为.exe可执行文件，该最终生成.exe可执行文件不含有任何水印（即不含有非用户编写BrainF__k源代码产生的输出）。

## 2.它能做什么
他能够做到简单的BrainF__k源代码编译以及其他工作：
 - 本体代码能够将.bf源代码文件编译为.cpp文件
 - 做简单的优化工作
 - 接收编译参数

## 3.快速开始
### 克隆项目
```powershell
git clone https://github.com/Preversons/NoxCompiler.git
```

### 编译项目
```powershell
git clone https://github.com/Preversons/NoxCompiler.git
cd NoxCompiler
```
以下部分与`./build.bat`等价
```powershell
mkdir build
cd build
cmake ..
cmake --build .
```

### 使用项目
```powershell
cd build
mkdir configs
cd configs
echo [你的mingw64路径，如D:\mingw64\...的应为D:\] > install_path.txt
cd ..
nox -s [你的BrainF__k源文件] -o [输出的.exe文件] [其他参数...]
```

当然，可以下载NoxSetupWinX64.exe程序，更简便的安装

## 4.参数文档
对于NoxCompiler，我们增加了一些参数使它更有扩展性，而对于这些参数，我们自然需要说明：
| 参数名 | 说明 | 是否可选 |
| :--- | :--- | ---: |
| -s | 指定BrainF__k源代码文件，建议使用绝对路径；将有一个文件路径 | 必选 |
| -o | 指定输出的.exe文件，建议使用绝对路径；将有一个文件路径 | 必选 |
| -arg | 提供编译参数；将有参数名与参数值 | 可选 |
| -arg ascii | 是否开启字符输出；将有true或false | 可选 |
| -arg cardinal | 指定一个单元格的临界值，当一个单元格的值大于等于这个临界值时将会回滚为0；将有一个整数 | 可选 |
| -arg length | 指定BrainF__k运行时数组长度；将有一个整数 | 可选 |
| --debug | 输出调试信息 | 可选 |
| | | |
| --help | 输出帮助信息；与其他参数不兼容 |
| --version | 输出版本信息；与其他参数不兼容 |

## 5.关于分发
本项目采用Apache License 2.0，详情见LICENSE文件
