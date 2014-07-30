# Debug your Application

Unlike microcontroller, Linux machine uses device drivers to access its pheripherals. Messages, having status of low level pheripheral along with time stamp of calling function, are displayed using debug configuration. Debug messages are infused in Userspace-Arduino low level APIs, and displayed on the terminal, only if the sketch is compiled as **debug**.

It may helpful in solving logical, device driver or device tree errors by analyzing debug messages.

To compile the sketch,

```
make clean
make CFG=debug
```

To compile and upload ELF file file directly,

```
make clean
make CFG=debug upload
```

```NOTE: Use 'make clean' before compilation.```

Here's the output of **GPIO Demo/Demo/Example1**

```
Begin output log
====================
root@192.168.42.1's password:
[00:02:37]: [pinInit] Exporting GPIOs...
[00:02:37]: [pinInit] Exporting GPIO102
[00:02:37]: [pinInit] Exporting GPIO103
[00:02:37]: [pinInit] Exporting GPIO104
[00:02:37]: [pinInit] Exporting GPIO105
[00:02:37]: [pinInit] Exporting GPIO108
[00:02:37]: [pinInit] Exporting GPIO109
[00:02:37]: [pwmInit] Exporting PWM...
[00:02:37]: [pwmInit] Exporting PWM 0
[00:02:37]: [pwmInit] Exporting PWM 1
[00:02:37]: [pwmInit] Exporting PWM 2
[00:02:37]: [pwmInit] Exporting PWM 3
[00:02:37]: [pwmInit] Exporting PWM 4
[00:02:37]: [pwmInit] Exporting PWM 5
[00:02:37]: [pinMode] configuring pin 13 as OUTPUT
[00:02:38]: [digitalWrite] writing 1 to pin 13
[00:02:39]: [digitalWrite] writing 0 to pin 13
[00:02:40]: [digitalWrite] writing 1 to pin 13
[00:02:41]: [digitalWrite] writing 0 to pin 13
[00:02:42]: [digitalWrite] writing 1 to pin 13
[00:02:43]: [digitalWrite] writing 0 to pin 13
[00:02:44]: [digitalWrite] writing 1 to pin 13

```
