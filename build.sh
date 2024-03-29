#!/bin/bash


if [ -f "main.bc" ]; then
    rm main.bc
fi
if [ -d "target" ]; then
    rm -r target
fi
mkdir target

if [ ! -d "reports" ]; then
    mkdir reports
fi

# 遍历 src 目录下的所有.cc文件
for file in src/*.cc
do
    # compile to bc
    # echo $file
    # 获取 base name
    base=$(basename $file .cc)
    # echo $base
    clang -I /snap/klee/9/usr/local/include -I ./headers -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone $file -o target/$base.bc
done

# compile to bc
clang -I /snap/klee/9/usr/local/include -I ./headers -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone main.cc
mv ./main.bc ./target/main.bc

gener_bc="target/main.bc"
llvm-link target/*.bc -o $gener_bc

# # run klee
# 获取当前按照 yy_mm_dd_HH_MM_SS 命名的文件夹
dir=$(date "+%Y_%m_%d_%H_%M_%S")
echo $dir
klee -solver-backend=z3 -output-dir=reports/$dir $gener_bc
if [ -d "reports/klee-last" ]; then
    rm -r reports/klee-last
fi
# mkdir reports/klee-last
cp -r reports/${dir} reports/klee-last


# 编译回放用的代码
gener="./target/genc"
clang -I ./headers -L /home/klee/klee_build/lib $gener_bc -lkleeRuntest -o $gener

# 遍历 klee-last 目录下的所有.ktest文件
for file in reports/klee-last/*.ktest
do
    echo $file
    KTEST_FILE=$file $gener
    ret=$? # 获取返回值
    # 换行
    echo
    echo "return value: $ret"
done

