# C51 单片机播放 Bad Apple


## 本项目采用的硬件
- C51 单片机，型号为 STC89C52RC
- 4 块双色点阵屏，每块点阵屏由三个 74HC595 芯片驱动，作用分别为控制行，控制红色，控制绿色
![Image text](https://raw.githubusercontent.com/MirandaMeow/BadApple-C51/main/images/1.png)

## 说明
单个 LED 屏幕有 3 个 74HC595，其中一个负责行选，那么就至少需要 1Byte 的数据才能使一行亮起，所以显示一帧图像 1 * 8 * 4 = 32Bytes，完整的 Bad Apple 视频有大约 6000 帧，大约 187kb，不可能存入只有 8k 的 C51 中，所以本项目采用串口通讯方式来传输帧数据。

Python 脚本负责向串口发送数据，使用 ```pySerial``` 库作为串口发送库，安装方法：
```pip install pyserial```

## 使用方法
通过 Keil5 导入项目，然后编译成 hex 文件，通过 stc-isp 软件烧录进 C51，随后上电，```main.py``` 里配置好串口，默认为 ```COM3```，波特率为 ```9600```，运行 ```main.py``` 即可播放 Bad Apple。
