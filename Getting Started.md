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
#### Installing the toolchain

1. Get the CodeSourcery toolchain for ARM from https://sourcery.mentor.com/GNUToolchain/release2450
2. Download the "Lite Edition" of the toolchain. You will need to register your email with Mentor Graphics first, after which a Download Link will be mailed to you.
3. Once you get the to the software selection page from the Download Link, select *Sourcery CodeBench Lite 2013.05-24* and then select the IA32 GNU/Linux Installer.
4. Once the download is complete, note the path of the binary. You'll need it later.
5. Execute in a terminal:
```
    sudo dpkg-reconfigure -plow dash
```
6. Choose "No" if you're asked about setting "dash" as the default shell.
7. Execute the binary from the path you noted earlier to begin installation.
8. Congratulations! You're ready to start developing.

#### Get the Userspace-Arduino repository

Open a terminal. Now might be a good time to start familiarizing with linux commands as you'll be doing most of your development here.

Execute:

```
cd ~
git clone https://github.com/crystalfontz/Userspace-Arduino.git
cd Userspace-Arduino
```
