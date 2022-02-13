# Major Update Notice

From BDS 1.18.11, the LiteXLoader project **has been merged into** LiteLoaderBDS project  
LXL becomes a sub-component of LL, and we will name the whole project as **LiteLoaderBDS** (**LL**)

Thereafter, LiteLoaderBDS will continue to be updated as a generic & strong BDS plugin loader for C++, Go, Js, Lua
and other languages   
All previous LXL plugins will continue to function normally under this new LiteLoaderBDS, and all existing APIs will remain unchanged

Starting with the merged version, LXL will **no longer need to be installed separately**. LL will carry a complete LXL engine when it is released

### 👉[click to LiteLoaderBDS project](https://www.minebbs.com/liteloader/) 👈

<br>

# 重大更新提示

从BDS 1.18.11开始，LiteXLoader加载器项目 **合并至** LiteLoaderBDS 项目之中  
LXL成为LL的一个子组件，我们将项目统称为 **LiteLoaderBDS** 加载器（**LL**）

此后，LL加载器将作为C++、Go、Js、Lua
等语言的通用加载器继续更新  
所有先前的LXL插件在新版LL下继续正常运行，现有所有API不变

从合并版本开始，LXL将 **不再需要单独安装**。LL发行时将自动携带LXL引擎

### 👉[点击前往 LiteLoaderBDS 项目](https://www.minebbs.com/liteloader/) 👈

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>

<br>



# LiteXLoader - 划时代 x 跨语言脚本插件加载器

[![GitHub license](https://img.shields.io/github/license/LiteLDev/LiteXLoader)](https://github.com/LiteLDev/LiteXLoader/blob/main/LICENSE)
[![Build](https://img.shields.io/badge/build-passing-brightgreen)](#)
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/LiteLDev/LiteXLoader?include_prereleases)

简体中文 | [English](README_en.md)

## 🎨 简介
`LiteXLoader`是一个基岩版官方服务端`Bedrock Dedicated Server`（以下简称**BDS**）插件框架，提供强大的跨语言脚本插件支持能力和稳定的开发API支持。  
由`LiteLoader`插件加载器加载并提供部分基础API。  
使用脚本开发**BDS**插件具有上手容易、代码简洁、便于维护的优点。同时脚本插件不需要随着**BDS**版本更新而修改代码，仅需本项目在底层适配即可，给插件开发与维护带来了很大的便利。  

## 🎁 优势
> “为什么我要选择LiteXLoader？”

1. **跨语言**插件开发支持 ⭐
   
    - `LiteXLoader`的插件可以使用**多种**不同的脚本语言开发。自由选择你的最爱！  
      同时，保证面向各种语言的接口统一    
    
      | 目前已支持的插件开发语言   | `JavaScript`，`Lua`                  |
      | -------------------------- | ------------------------------------ |
      | **即将支持的插件开发语言** | `Python`，`Ruby`，`C#`，`TypeScript` |

2. **功能强大，设施完备** ⭐

    - 提供众多的游戏API支持、游戏事件监听，为你发挥创意打好技术基础

    - 配备大量基础设施，如统一配置文件接口、统一日志接口、文件系统接口、数据库接口等等  
      让你专注于业务代码实现，而非各种琐碎的技术细节
3. **兼容性强** ⭐

     - LXL支持通过Wine在Linux平台运行，给Linux平台也带来自由的插件体验  
       一次编写，多平台共享
     - 仅依赖LiteLoader加载器和标准的C/C++运行时库，没有其他的额外依赖，兼容性极强
     - 兼容绝大多数其他主流插件加载器（`CSR` `PYR`等）
     - 后续版本更新时将保证 API 向后兼容，避免出现插件需要一再重写的情况。  
       脚本插件不需要随版本更新而修改代码，一次编写，全版本适配。
4. **模块化，高性能** ⭐
   
     - 使用C++开发，底层性能优越。借助ScriptX的高效率通用接口，让脚本插件也可以做到高效运行。
     
     - 底层仅有一套统一的C++ API，维护和适配都比较方便，新版本适配速度快。  
5. **开源 & 永久免费** ⭐ 
   
     - 项目采用`GPL-3.0`开源许可证，保证**永远不会**收费或者推出商业版。  
       希望社区多多贡献力量，共同维护和建设这个项目💕    

## 🔨 Compiling
1. Install newest **Microsoft Visual Studio** with standard C++ building suite
2. Install the newest version of **Windows SDK**
3. Install **CMake** and add it to `PATH`
4. Run the building batch below  

#### Build & Link
- `build/BuildJs.bat`&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;Build LiteXRunner for Js
- `build/BuildLua.bat`&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;Build LiteLuaRunner for Lua
- `build/BuildAll.bat`&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;Build All targets above

#### Clean everything generated & Rebuild & Link
- `build/ReBuildJs.bat`&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;ReBuild LiteXRunner for Js
- `build/ReBuildLua.bat`&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;ReBuild LiteXRunner for Lua
- `build/ReBuildAll.bat`&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;&nbsp;ReBuild All targets above

##### After building, DLLs will generate at `Release` directory.    

##### If you want to get the release zip pack, run `build/PackRelease.bat` and it will generate at `Release` directory.    

## 💻 安装
项目主要发布于**MineBBS**，请[移步MineBBS](https://www.minebbs.com/)下载
1. 正确安装`LiteLoader`插件加载器
2. 下载`LiteXLoader`，解压，把全部内容复制到 **BDS **的`plugins`目录中。如果有冲突，选择覆盖即可。
3. 开服

## 🎯 加载插件
1. 将需要加载的脚本插件直接放置到`plugins`目录中
2. 开服

> 没错，就这么简单 o(*￣▽￣*)ブ

关于具体的**安装与使用指南** ，请👉[移步文档站](https://liteldev.github.io/LiteXLoader/#/zh_CN/Usage)👈查看

## 💡 兼容性与可扩展性
兼容`旧LiteLuaRunner`的大部分插件。  
小部分API并未适配，仅为了方便用户而设计兼容层。  
请[移步文档站](https://liteldev.github.io/LiteXLoader/#/)查看详细的分析  

## 📡 实时调试
在BDS后台控制台执行
- `jsdebug`  
进入Js实时调试模式
- `luadebug`  
进入Lua实时调试模式

实时调试模式下，标准输入会被当做对应类型的脚本语言执行，并实时输出结果。  
如果发生错误，引擎将输出错误信息与堆栈跟踪信息。  
再次输入对应的`jsdebug`或`luadebug`将退出实时调试模式。

<br>

------

## 📕 开发文档

请👉[移步文档站](https://liteldev.github.io/LiteXLoader/#/zh_CN/Development)👈查看详细的**API文档**和**插件开发教程**  
如果有修订需求或者有新增API的需要，欢迎联系作者或者发布Issue  

## 🎬 参与贡献

  你可以通过下面这些方法来`LiteXLoader`项目出一份力

1. 贡献代码，维护项目和符号
2. 帮助修改和优化开发文档
3. 按格式编写你想要的新API并提交PR，或者提出好的建议
4. 帮助我们宣传LXL，对我们的开发给予支持

⭐⭐⭐我们欢迎你对LiteXLoader做出自己的贡献！⭐⭐⭐  
如果你有意为LXL贡献代码，欢迎👉[移步文档站](https://liteldev.github.io/LiteXLoader/#/zh_CN/Maintance)👈查看 **项目维护与支持文档**  

有你们，LiteXLoader将变得更好~

## 📍 许可协议声明
在使用我们的产品的时候，我们默认您已经承认并遵守了[Mojang Studios EULA](https://account.mojang.com/documents/minecraft_eula)协议。  
这意味着你不能对本项目进行任何违反EULA的商业性使用。违反EULA协议造成的一切后果由违反者自行承担。  
另外，您需要遵守本项目的`GPL-3.0`开源许可证条款，以及下列提到的各关联项目的开源许可证条款 

[LiteLoader](https://github.com/LiteLDev/LiteLoader) GPLv3 with extra restrictions&exceptions    
[ScriptX](https://github.com/Tencent/ScriptX) Apache License Version 2.0  
[BedrockX](https://github.com/Sysca11/BedrockX) GPLv3 with extra restrictions&exceptions  
[ElementZero](https://github.com/Element-0/ElementZero) GPL v3  
[ChakraCore](https://github.com/chakra-core/ChakraCore) MIT License  
[OpenSSL](https://github.com/openssl/openssl) Apache License Version 2.0    
[Minini](https://github.com/compuphase/minIni) Apache License Version 2.0  
[Nlohmann-Json](https://github.com/nlohmann/json) MIT License  

### Extra Restrictions & Exceptions
If you provides a server hosting service,you can use this framework for free, but you SHOULD NOT make PRIVATE changes to this framework as a selling point. If you fixed or tweaked the code, please pull request, instead of making it private for commercial use. 
> Do not do evil.

Although we expected to build an open-source community, but forcing everything open-source will ruin this community.
So you can write plugins based on `LiteXLoader` with ANY open-source license or even dont publish your source code.
but if you modified the framework, or write a new framework based on this framework, you MUST open-source it.

## 🏆 鸣谢
- 开源 [ScriptX](https://github.com/Tencent/ScriptX) 项目提供的跨语言引擎支持
- [LiteLoader ](https://github.com/LiteLDev/LiteLoaderBDS)项目提供的加载服务与基础API  
- [LiteLuaLoader ](#)项目 和 [BDSPyRunner ]()项目 提供的部分底层接口实现

> 特别鸣谢：[LiteLDev](https://github.com/orgs/LiteLDev/people) 各位大佬们 和 ScriptX开发者 [@LanderlYoung](https://github.com/Tencent/ScriptX/commits?author=LanderlYoung)   
> 在开发过程中给予了作者以非常大的支持。感谢他们！ 💖💖

## 📞 联系我们

LiteXLoader交流群：850517473 [点击加入](https://jq.qq.com/?_wv=1027&k=zeUbrETH)  
LiteLoader交流群：656669024 [点击加入](https://jq.qq.com/?_wv=1027&k=lagwtrfh)  
Telegram电报频道：#LiteLoader [点击加入](https://t.me/LiteLoader)  
欢迎反馈崩溃和版本适配问题。务必准备好详细的情况描述，过于简略的提问将不予作答。  

## 💕赞助作者💕
项目已接入爱发电 [点击此处](https://afdian.net/@LiteXLoader?tab=home)   
给我们不断继续下去的动力！  