# Petalinux

## Installation

1. Download Installer from [Xilinx](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html)

2. install dependencies  
   based on UG1144 - Installation Requirements

    ``` bash
    sudo dpkg --add-architecture i386
    sudo apt update
    sudo apt install iproute2 gawk make net-tools libncurses5-dev tftpd zlib1g:i386 libssl-dev flex bison libselinux1 gnupg wget diffstat chrpath socat xterm autoconf libtool tar unzip texinfo zlib1g-dev gcc-multilib build-essential screen pax gzip python2.7
    ```

3. For Debian or Ubuntu, select `bash` instead of `dash` as default sh shell (`/bin/sh`)

   ``` bash
   sudo dpkg-reconfigure dash
   ```

   select `No`

4. create a directory where you would like to install PetaLinux  
   e.g. `./PetaLinux`

5. Reboot  
   I don't know if this is necessary

6. Run Installer  
  (if install path not specified i.e. without `./PetaLinux/` below, default path: `/opt/pkg/petalinux`)

   ``` bash
   ./petalinux-v2019.1-final-installer.run ./PetaLinux/
   ```

   you may need to agree some EULA in the meantime, press `q` when you finish reading the EULA (in case you really do), then type `Y<Enter>` to agree

7. add settings script `settings.sh` into user login shell

   ``` bash
   echo "source ~/PetaLinux/settings.sh" >> .bashrc
   ```

   replace `~/PetaLinux/` with path to installed PetaLinux

   Verify that the working environment has been set

   ``` bash
   echo $PETALINUX
   ```
   Example output: `/home/aeekycheung/PetaLinux`

### License

I don't know whether a license is necessary

### Boot

1. Setup path for QEMU (optional)  

   It seems that QEMU is included in PetaLinux but may not be added to environment path, so the easiest way is to add an alias to user login script `.bashrc`

   ``` bash
   # depends on where PetaLinux is installed
   echo "alias qemu-system-aarch64=~/PetaLinux/components/yocto/source/aarch64/buildtools/sysroots/x86_64-petalinux-linux/usr/bin/qemu-xilinx/qemu-system-aarch64" >> .bashrc

   source ~/.bashrc # reload .bashrc
   ```

2. For evaluation board ZCU102, download ZCU102 BSP from [Xilinx](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools/2019-1.html)

3. Create a PetaLinux project using the `.bsp` file

   ``` bash
   petalinux-create -t project -s <path to bsp>/xilinx-zcu102-v2017.3-final.bsp -n xilinx-qemu-first-run
   ```

   This create a project called `xilinx-qemu-first-run`, but all I want is the `pre-built/linux/images/zynqmp-qemu-arm.dtb` inside.

4. Run  
   In this example, the desired binary is put in `./hello.elf` (i.e. `hello.elf` under this folder).

   ``` bash
   qemu-system-aarch64 -nographic -M arm-generic-fdt -dtb ~/share/xilinx-qemu-first-run/pre-built/linux/images/zynqmp-qemu-arm.dtb -device loader,file=./hello.elf,cpu-num=0 -device loader,addr=0xfd1a0104,data=0x8000000e,data-len=4
   ```
