# Tiny Kernel Module
## 简介

OS课程大作业。给linux添加了一个内核模块，向 `/proc` 注册了 `/proc/modulecrypto`，以通过文件操作与内核模块进交互

## 编译与加载

```bash
sudo make
sudo make load
```

## 实现功能

实现了一个简单的 `base64` 编解码功能

## 使用方式

首次读取 `/proc/modulecrypto` 会返回一个使用简介

```
cat /proc/modulecrypto
```

向 `/proc/modulecrypo` 写如要使用的功能和要编码的数据，来触发内核模块进行编解码

```
echo "base64 encode\ntest\n" > /proc/modulecrypto
```

再次读取获得编码结果

```
cat /proc/modulecrypto
```