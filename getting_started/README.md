# Getting Started
While this version of Userspace Arduino doesn't support a GUI, it is very easy to get started using your own sketches on the CFA10036.

#### Pre-requisites

Typically, any 32/64-bit linux machines (Windows and Mac are **not** supported yet) would do. However, for beginners we recommend using Ubuntu 12.04 (or 14.04) LTS to avoid compatibility issues which may crop up in other distros.

If you don't have a linux machine, there are excellent guides available on the World Wide Web to dual-boot a linux distro with OS X or Windows.

#### Dependencies

Once you've got your linux machine running, you might want to run these commands to make sure that dependencies are installed:
```
sudo aptitude install g++ bison flex gettext ncurses-dev texinfo git
```
Use a terminal (Ctrl+Alt+t on Ubuntu) to copy-paste the above command.

**Note: You've to use Ctrl+Shift+v to paste in a Ubuntu terminal.**
#### Installing the toolchain
1. Get the CodeSourcery toolchain for ARM by executing this in the terminal:
```
    wget -c https://sourcery.mentor.com/public/gnu_toolchain/arm-none-linux-gnueabi/arm-2013.05-24-arm-none-linux-gnueabi.bin
```
*Note: If you're **not** using a 64-bit system, skip to step 3*
2. Execute in a terminal (for 64-bit only):
```
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install libgtk2.0-0:i386 libxtst6:i386 gtk2-engines-murrine:i386 \
lib32stdc++6 libxt6:i386 libdbus-glib-1-2:i386 libasound2:i386
```

3. Now:
```
    chmod +x arm-2013.05-24-arm-none-linux-gnueabi.bin
 ./arm-2013.05-24-arm-none-linux-gnueabi.bin
```
4. When asked, choose a typical install.
5. Logout and log back in. Congratulations! You're ready to start developing.

#### Get the Userspace-Arduino repository

Open a terminal. Now might be a good time to start familiarizing with linux commands as you'll be doing most of your development here.

Execute:

```
cd ~
git clone -b master --single-branch https://github.com/crystalfontz/Userspace-Arduino.git
cd Userspace-Arduino
```

#### Run an example

Connect the CFA10036 to your PC using a USB cable. Wait for it to boot-up.
```
cd arduino-makefile/examples
cd BlinkUserspace
make upload
```
When prompted, use username as "root" and password as "root".

You should see the LED blink periodically.
