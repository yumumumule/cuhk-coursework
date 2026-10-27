# 双矩阵纳什均衡求解器

CUHK ESTR1005 博弈论项目，使用 C11 实现，支持两名玩家各有 **1–3 个策略**
的一般双矩阵博弈，同时兼容零和博弈。

矩阵 `A[i][j]` 表示行玩家的收益，`B[i][j]` 表示列玩家的收益。
**双方都最大化自己的收益**；只有在零和模式下，才有 `B = -A`。

## 功能

- 枚举行、列双方的支持集，寻找纯策略与混合策略纳什均衡。
- 输出双方策略概率、期望收益、单方面改变策略能获得的最大收益。
- 支持 2×2、2×3、3×3 等小型矩阵，以及只有一个策略的边界情况。
- 使用带部分主元选择的高斯消元；跳过奇异方程组。
- 用约束可行性处理退化情形及大小不相同的支持集。
- 支持标准输入、文件输入、`#` 注释、JSON 输出、输入错误提示。
- 提供 CMake 构建、示例、自动测试和独立算法对照。

退化博弈可能有无穷多个均衡。程序每对支持集最多选择一组可行策略，去重后输出
有限个**代表解**，不声称列举完整的连续均衡集合。

## 编译与运行

在此项目目录中，使用 GCC 或 Clang：

```sh
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/nash.c -lm -o nash
./nash --file examples/battle_of_the_sexes.txt
```

Windows 下把输出文件名改为 `nash.exe`，然后在 PowerShell 中执行：

```powershell
.\nash.exe --file examples/battle_of_the_sexes.txt
```

也可以把编译命令中的 `gcc` 换成 `zig cc`。
使用 CMake 时需要 CMake 3.16+、C 编译工具链；测试需要 Python 3.8+：

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Visual Studio 构建的可执行文件通常在 `build/Release/nash.exe`；
Ninja 或 MinGW 构建通常在 `build/nash.exe`。
只编译程序时可加 `-DBUILD_TESTING=OFF`，无需 Python。

## 输入格式

第一行是行数、列数，接下来依次填写矩阵 A 和 B，各矩阵按行排列。例如：

```text
2 2
# A：行玩家
2 0
0 1
# B：列玩家
1 0
0 2
```

双方的策略顺序均为 Opera、Football。这个例子有两个纯策略均衡，以及一个混合均衡：

- 行玩家：`(2/3, 1/3)`。
- 列玩家：`(1/3, 2/3)`。
- 双方期望收益都是 `2/3`。

```powershell
.\nash.exe --file examples/rock_paper_scissors.txt --json
.\nash.exe --zero-sum --file examples/zero_sum_legacy.txt
.\nash.exe --help
```

不指定 `--file` 时从标准输入读取。`--zero-sum` 只读取 A，自动生成 B。
原程序的九个输入数字前需要补上 `3 3`，并使用 `--zero-sum`。
一般双矩阵模式必须提供双方收益矩阵，不能仅凭 A 推断 B。

输入必须是有限数字，绝对值不超过 `1e100`；解析时发生上溢或下溢会报错。
退出码：`0` 为成功，`1` 为输入或参数错误，`2` 为未找到数值验证通过的结果。
有限博弈存在纳什均衡，因此退出码 2 只能表示数值求解受限，不能解释为数学上无解。

## 如何理解误差

程序分别计算双方“保持对方策略不变，自己换策略能多赚多少”。
验证时先将每人的收益矩阵除以其最大绝对值，归一化后的最大偏离收益须不超过 `1e-8`。
原始单位的偏离收益也会输出：收益量级很大时，即使相对误差很小，原始误差也可能较大。

程序使用双精度浮点数，适合课程中的小规模、条件良好的例子。
极接近退化的博弈仍可能受舍入误差影响；概率坐标差不超过 `1e-7` 的结果会合并。
人类可读输出保留六位小数，进一步分析请使用 JSON。

## 测试与项目说明

```sh
python tests/test_solver.py build/nash
python -m pip install -r tests/requirements.txt
python tests/cross_check.py build/nash
```

Windows 下请对应改成 `.exe` 路径。运行求解器本身不需要 Python 或第三方库。
基础回归测试只使用 Python 标准库；Nashpy 仅用于可选的独立对照测试。

数学模型、求解步骤和原始代码的问题见 [算法说明](docs/ALGORITHM.md)。
实际测试环境与结果见 [验证记录](docs/VALIDATION.md)。
可在展示时依次运行囚徒困境、协调博弈、石头剪刀布和退化例子，解释
纯策略均衡、多个均衡、完全混合均衡与连续均衡集合的区别。
