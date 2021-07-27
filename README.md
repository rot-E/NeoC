# NeoC
Neo C Programming Environment Library

![](https://user-images.githubusercontent.com/85844095/125081210-b6ea7380-e100-11eb-9f34-0871e29de9cc.png)
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;__↑↑↑ examples/Theme.c ↑↑↑__

&emsp;&emsp;&emsp;__↓↓↓ Sample Code (examples/SampleCode.c) ↓↓↓__
```C
#include <NeoC.h>

void main() $_ {
   String_t *text = String.New(u8"NeoC is a Neo C Programming Environment Library !");
   Console.WriteLine(text);

   uint8_t target = 'i';
   try {
      defer {
         Map_t *map = Map.New() in (String_t *, int32_t *);

         map->Put(map, String.New(u8"NeoC!    "), $(int32_t, 1));
         map->Put(map, String.New(u8"NeoC!!!  "), $(int32_t, 3));
         map->Put(map, String.New(u8"NeoC!!!!!"), $(int32_t, 5));

         for (int32_t i = 0; i < map->GetLength(map); i++) {
            Console.WriteLine(String.NewFormat(
               u8"%s : %d",
               String.Unpack( map->Get(map, i).Key ),
               *(int32_t *)( map->Get(map, i).Value )
            ));
         }
      } set

      defer {
         Console.WriteLine(text);
         Console.NewLine();
      } set

      execute {
         int32_t fi = String.FirstIndexOf(text, target);
                   // text->FirstIndexOf(text, target);
         int32_t li = text->LastIndexOf(text, target);
                   // String.LastIndexOf(text, target);

         for (int32_t i = 0; i < String.GetLength(text); i++) {
            Console.WriteChar((i == fi || i == li)? '^' : ' ');
            System.USleep(50 * 1000);
         }
         Console.NewLine();
      } ret
   } catch (String.Failure) {
      Console.WriteErrorLine(String.NewFormat(u8"Target character '%c' not found.", target));
   } fin
} _$
```
<br><br>

## Build
Dependencies: **`Git` `CMake` `GNU Make` `GCC`**
<br><br>

### 1. NeoC Library
CMakeを用いてビルド環境を作成した後にビルドを行う。

NeoCライブラリはGCC拡張を使用しているため、コンパイラにはGCCを使用しなければならず、環境によっては `CMAKE_C_COMPILER` オプションによる指定が必要である。
```fish
             $ git clone https://github.com/RotationE/NeoC.git
             $ cd NeoC
      [NeoC/]$ mkdir build
      [NeoC/]$ cd build
[NeoC/build/]$ cmake ..
[NeoC/build/]$ make -j
```
**→ `NeoC/include/` `NeoC/build/lib/libNeoC.a`**
<br><br><br><br>

ビルド環境の作成時には、以下のオプションが利用可能である。

- `CMAKE_C_COMPILER` 使用するコンパイラの指定
- `CMAKE_BUILD_TYPE` `Debug` または `Release`
- `CMAKE_INSTALL_PREFIX` ライブラリのインストールディレクトリの指定 (インストールする場合)
- `NEOC_BUILD_SHARED_LIBS` ライブラリの形式の指定： 静的ライブラリ または 共有ライブラリ
<br><br><br>

`CMAKE_C_COMPILER` では、使用するコンパイラを指定できる。
GCC拡張を使用しているため、コンパイラにはGCCを使用する必要がある。
(特にMacなど)デフォルトで利用するコンパイラがGCC以外である場合は、以下のように適切に指定する必要がある。
```fish
[NeoC/build/]$ cmake .. -DCMAKE_C_COMPILER=/usr/bin/gcc
```
<br>

`CMAKE_BUILD_TYPE` では、`Debug` か `Release` などが利用できる。
```fish
# デバッグするために、-gオプションをつける
[NeoC/build/]$ cmake .. -DCMAKE_BUILD_TYPE=Debug

# 最適化をするために、-O3オプションをつける
[NeoC/build/]$ cmake .. -DCMAKE_BUILD_TYPE=Release
```
<br>

`CMAKE_INSTALL_PREFIX` では、NeoCライブラリのインストールディレクトリを指定できる。
指定しない場合は `/usr/local/` 以下にインストールされる。
インストール場所として `$HOME/.local/` がよく利用され、これを指定するには、以下のようにする。
```fish
[NeoC/build/]$ cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local
```
<br>

`NEOC_BUILD_SHARED_LIBS` では、ライブラリを静的ライブラリではなく共有ライブラリとして出力する事ができる。
指定しなければ、静的ライブラリとして `libNeoC.a` が出力される。
```fish
[NeoC/build/]$ cmake .. -DNEOC_BUILD_SHARED_LIBS=ON
```
<br><br>

### 2. Examples
```fish
[NeoC/build/]$ make examples -j
```
**→ `NeoC/build/examples/*`**
<br><br><br>

## Clean
```fish
[NeoC/build/]$ make clean
```
<br><br>

## Install
`NeoC/include/` `NeoC/build/lib/libNeoC.a` を任意のディレクトリに配置する。

インストールする場合、ビルド環境の作成の際に `CMAKE_BUILD_TYPE` には `Release` を、`CMAKE_INSTALL_PREFIX` には配置先のディレクトリを指定することを推奨する。
```fish
[NeoC/build/]$ cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$HOME/.local
[NeoC/build/]$ make install -j
```
<br>

## Usage
### 1. 一時凌ぎの場合...
```fish
$ gcc -Ipath-to-NeoC-include-directory -Lpath-to-NeoC-archive-file -lNeoC -lpthread Source.c -o Exec
```
**→** `./Exec`
<br><br>

### 2. CMakeを使用する場合
Visit [Hiroya-W/NeoC-sample-project](https://github.com/Hiroya-W/NeoC-sample-project)
<br><br>

## License
&emsp;[`AGPLv3`](https://www.gnu.org/licenses/agpl-3.0.html)
