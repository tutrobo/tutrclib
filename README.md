# tutrclib

とよはし⭐︎ロボコンズ 新入生講習用ライブラリ

- STM32CubeF4 V1.28.1
- CMSIS-RTOS2 V2.1.0
- FreeRTOS Kernel V10.3.1

で開発・動作確認しています。

## ドキュメント

### tutrclib

https://tutrobo.github.io/tutrc/

### CMSIS-RTOS2
 
https://arm-software.github.io/CMSIS_5/RTOS2/html/index.html

### FreeRTOS

https://www.freertos.org/Documentation/00-Overview

## 導入方法

このライブラリには CMSIS-RTOS2(FreeRTOS) が必要です。

### Timebase Sourceの切り替え

RTOSを使用するにあたって Timebase Source を `SysTick` から任意のハードウェアタイマーに切り替えることが推奨されています。

`Pinout & Configuration` -> `System Core` -> `SYS` を選択し、Timebase Source に空いているハードウェアタイマーを指定してください(TIM6 が一般的)。

### CMSIS-RTOS2 の有効化

`Pinout & Configuration` -> `Middleware and Software Packs` -> `FREERTOS` を選択し、Interface に `CMSIS_V2` を指定します。

Configuration欄から `Advanced settings` を選択し、`USE_NEWLIB_REENTRANT` を `Enabled` にします。

### プロジェクトにライブラリを追加

Git submodule として導入するのがおすすめです。プロジェクトのルートで

```sh
$ git submodule add https://github.com/tutrobo/tutrc.git
```

を実行します。

#### STM32 VS Code Extension ユーザーの場合

このライブラリは CMake に対応しています。STM32CubeMX を用いて CMake 向けにプロジェクトを書き出したあと、`Import CMake project` からプロジェクトを取り込み、`CMakeLists.txt` を以下のように書き換えます。

##### 変更前:

```cmake
# ~前略~

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
```

##### 変更後:

```cmake
# ~前略~

add_subdirectory(tutrc)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    tutrc
)
```

#### STM32CubeIDE ユーザーの場合

`C/C++ General` -> `Paths and Symbols` を開き、Languages から `GNU C++` を選択したあと、

- Includes: `プロジェクトルート/tutrc/include`
- Source Location: `プロジェクトルート/tutrc/src`

を追加します。

## サンプル

サンプルコードは各クラスのドキュメントに付属しています。また、全てのサンプルコードは CMSIS-RTOS2 で起動可能なスレッド関数として実装しています。

以下はサンプルコードを実行する際の例です。

```cpp
#include "cmsis_os2.h"

// 以下のコードは別スレッドやmain関数等から呼び出す
osThreadAttr_t thread_attr = {};
thread_attr.stack_size = 1024;
thread_attr.priority = osPriorityNormal;

osThreadNew(example_thread, nullptr, &thread_attr);
```

## ライセンス

MIT License
