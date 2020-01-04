# Openshot animated titles not transparent background
[Source](https://bugs.launchpad.net/openshot/+bug/1365851)

Hello,

there is a workaround, you can read on http://www.mp-development.de/blog/18-openshot-blender-titelanimation-transparenz-fehler (german language)

you have to edit the phython-script files which controls the blender rendering in /usr/share/pyshared/openshot/blender/scripts/

1) search for:
            'color' : [0.8,0.8,0.8],
            'alpha' : 1.0,

and add the line:
            'alpha_mode' : 'TRANSPARENT',

2) search for:
except:
    bpy.context.scene.render.image_settings.file_format = params["file_format"]
    bpy.context.scene.render.image_settings.color_mode = params["color_mode"]

and add the lines:
try:
    bpy.context.scene.render.alpha_mode = params["alpha_mode"]
except:
    pass

Please fix the scripts. without the transparency working directly, this function is completely useless!



# Firefox won't display .swf files
http://askubuntu.com/questions/478169/why-cant-firefox-run-local-swf-files



Edit /usr/share/mime/packages/freedesktop.org.xml as root and replace the following:

<mime-type type="application/vnd.adobe.flash.movie">

With:

<mime-type type="application/x-shockwave-flash">

And then run:

sudo update-mime-database /usr/share/mime


# GPT table broken
http://askubuntu.com/questions/388315/cant-format-or-delete-partitions-in-pendirve-cause-of-gpt-table-error

sudo gdisk /dev/sdX
o
(agree to delete partitions)
w
(agree to write partition table)



# Install PCSX2
# Depends: libsdl2-2.0-0:i386 (>= 2.0.0) but it is not going to be installed
https://forums.linuxmint.com/viewtopic.php?f=47&t=212153&p=1108633

apt install libwayland-egl1-mesa-lts-vivid:i386
apt install libsdl2-2.0-0:i386



# USB not recongised in Virtualbox
http://stackoverflow.com/questions/20021300/usb-devices-are-not-recognized-in-virtualbox-linux-host

1. sudo adduser YOURUSERNAME vboxusers
2. log out and log in again



# Disable Intel Turbo boost
http://luisjdominguezp.tumblr.com/post/19610447111/disabling-turbo-boost-in-linux

1. Check whether enabled:
	sudo rdmsr -p(i) 0x1a0 -f 38:38, where (i) is the cores number
	(Check cores number
		cat /proc/cpuinfo | grep processor)
	(If "rdmsr:open: No such file or directory"
		sudo modprobe msr)

2. Disable
	sudo wrmsr -p(i) 0x1a0 0x4000850089, where (i) is the particular core number

3. Enable
	sudo wrmsr -p(i) 0x1a0 0x850089, where (i) is the particular core number



# Install Oracle Java
[Source](http://forums.technicpack.net/topic/134443-guide-install-technic-launcher-on-linux-mint-17ubuntu-14/)

## Install
		sudo apt-get purge openjdk*
		sudo add-apt-repository ppa:webupd8team/java
		sudo apt-get update
		sudo apt-get install oracle-java9-installer

## Set as Default
		sudo update-alternatives --config java
		java -version


# Boot up: Continue to wait; or Press S to skip mounting or M for manual recovery
[Source](https://ubuntuforums.org/showthread.php?t=1583719)

The UUID could have been changed if another distro was installed.

Find the UUID:
	`sudo blkid /dev/sd??`

Then replace the existing UUID for for swap in fstab.
	`gksu gedit /etc/fstab`

Make sure that the UUIDs listed in fstab match.
	`sudo blkid -c /dev/null`



# The package lists or status file could not be parsed or opened
	`sudo rm /var/lib/apt/lists/* -vf`
	`sudo apt-get clean`
	`sudo apt-get update`
	`sudo apt-get upgrade`



# Folder in ZIP are Mojibake(亂碼)
[Source](https://www.zhihu.com/question/20523036)

	`unar file.zip`



# Install Brother Printer
[Download driver here](http://support.brother.com/g/b/downloadtop.aspx?c=hk&lang=zh&prod=mfc7360_as_cn)

need both cupswrapper and LPR files

[Follow steps here](http://support.brother.com/g/b/downloadhowto.aspx?c=hk&lang=zh&prod=mfc7360_as_cn&os=128&dlid=dlf006893_000&flang=4&type3=625)


[Source](https://ubuntuforums.org/showthread.php?t=2204606)

[Source](http://askubuntu.com/questions/280644/install-brother-mfc-7360n-for-beginners)

type 'localhost:631' in Firefox
-> Administration
-> Add Printer
pdd: usr/file/MFC7360.pdd

# Change IP
[Source](https://www.asus.com/hk/support/faq/112981/)

1. 請至路由器設定頁面，ASUS路由器預設設定頁面為http://192.168.1.1。
點擊『網路地圖』-> 點擊已連線的『圖示』-> 點擊網際網路狀態的『暫停』；此時以外部網路IP是『114.44.3.75』舉例。
2. 等待路由器中斷連線。
3. 點擊連線中斷的『圖示』-> 點擊網際網路狀態的『恢復』
4. 等待路由器重新取得IP位址。
5. 外部網路IP位址已變更完成。



# ping: icmp open socket: Operation not permitted
# ssh: connect to host 192.168.1.33 port 22: No route to host

`$ sudo chmod u+s /bin/ping`



# Add Markdown systax highlight to Pluma
[Source](https://ubuntu-mate.community/t/adding-syntax-highlighting-to-pluma/56)

The easy fix seems to be to check that libgtksourceview-3.0-common is installed, and if not, install it with your package manager of choice or from the terminal with:

		sudo apt-get install libgtksourceview-3.0-common

After making sure it is installed, sym-link the markdown.lang file included with libgtksourceview-3.0-common to the appropriate spot for the applications that rely on libgtksourceview2.0.

		sudo ln -s /usr/share/gtksourceview-3.0/language-specs/markdown.lang /usr/share/gtksourceview-2.0/language-specs/markdown.lang

Make sure that all your text editor windows are closed and then restart Pluma and you should find syntax highlighting for Markdown files now works. For the record, this fix also works for newer versions of mousepad (the xfce editor), as it also relies upon libgtksourceview2.0 for it's highlighting ability.



# Allow systax highlighting for certain file extension in Pluma
[Source](https://askubuntu.com/questions/44730/can-i-set-a-default-syntax-highlighting-in-gedit)

## add *.launch in XML
		sudo pluma /usr/share/gtksourceview-2.0/language-specs/xml.lang 

Add *.launch in this line:
<property name="globs">*.xml;*.xspf;*.siv;*.smil;*.smi;*.sml;*.kino;*.xul;*.xbel;*.abw;*.zabw;*.glade;*.jnlp;*.xhtml;*.svg;*.mml;*.rdf;*.rss;*.wml;*.xmi;*.fo;*.xslfo;*.launch</property>





# Unknown filesystem type 'exfat'
		sudo apt-get install exfat-utils exfat-fuse



# Chinese in Terminal
		luit -encoding big5 telnet ptt.cc



# Escape from freezed SSH
	Press "Enter", then type "~."



# Disable bluetooth on startup for Thinkpad
[Source](https://askubuntu.com/questions/67758/how-can-i-deactivate-bluetooth-on-system-startup)

		sudoedit /etc/rc.local 

	Add line before "exit 0":
		rfkill block bluetooth
		echo disable > /proc/acpi/ibm/bluetooth

The line "echo disable > /proc/acpi/ibm/bluetooth" is only needed for Thinkpad.



# OSError: [Errno 98] Address already in use
[Source](https://stackoverflow.com/questions/19071512/socket-error-errno-48-address-already-in-use)

You already have a process bound to the default port (8000). If you already ran the same module before, it is most likely that process still bound to the port. Try and locate the other process first:

		ps -fA | grep python
  501 81651 12648   0  9:53PM ttys000    0:00.16 python -m SimpleHTTPServer

The command arguments are included, so you can spot the one running SimpleHTTPServer if more than one python process is active. You may want to test if http://localhost:8000/ still shows a directory listing for local files.

The second number is the process number; stop the server by sending it a signal:

		kill 81651

This sends a standard SIGTERM signal; if the process is unresponsive you may have to resort to tougher methods like sending a SIGKILL (kill -s KILL <pid> or kill -9 <pid>) signal instead. See Wikipedia for more details.



# Fortune | Cowsay
Open ~/.bashrc, add at the bottom:

if [ -x /usr/games/cowsay -a -x /usr/games/fortune ]; then
    fortune | cowsay -f `ls /usr/share/cowsay/cows/ | shuf -n 1` | lolcat
fi



# Thinkpad Mic Mute Button & Indicator
[Source](https://askubuntu.com/questions/125367/enabling-mic-mute-button-and-light-on-lenovo-thinkpads)

1. 
		acpi_listen
then press the Mic Mute Button, get something like "button/f20 F20 00000080 00000000 K"

2. 
		amixer scontrols
get something like "Simple mixer control 'Capture',0"

3. 
		sudo pluma /etc/acpi/events/lenovo-mutemic

Content:

event=button/f20 F20 00000080 00000000 K
action=/etc/acpi/lenovo-mutemic.sh

4. 
		sudo pluma /etc/acpi/lenovo-mutemic.sh

Content:

#!/bin/bash
MICMUTE=/sys/devices/platform/thinkpad_acpi/leds/tpacpi::micmute/brightness
INPUT_DEVICE="'Capture'"
YOUR_USERNAME="s03311251"
if amixer sget $INPUT_DEVICE,0 | grep '\[on\]' ; then
    amixer sset $INPUT_DEVICE,0 toggle
	echo 1 > $MICMUTE
    su $YOUR_USERNAME -c 'DISPLAY=":0.0" notify-send -t 200 \
            -i microphone-sensitivity-muted-symbolic "Mic MUTED"'
else
    amixer sset $INPUT_DEVICE,0 toggle
    su $YOUR_USERNAME -c 'DISPLAY=":0.0" notify-send -t 200 \
            -i microphone-sensitivity-high-symbolic "Mic ON"'
	echo 0 > $MICMUTE
fi

5. 
		sudo chmod +x /etc/acpi/lenovo-mutemic.sh
		sudo service acpid restart



GRUB MENU
==========
		sudo pluma /etc/default/grub

change the value of "GRUB_TIMEOUT="



REPAIR GRUB
===========
(Source)[https://howtoubuntu.org/how-to-repair-restore-reinstall-grub-2-with-a-ubuntu-live-cd]



ACESTREAM
==========
## Install acestream-engine
		echo 'deb http://repo.acestream.org/ubuntu/ trusty main' | sudo tee /etc/apt/sources.list.d/acestream.list
		sudo wget -O - http://repo.acestream.org/keys/acestream.public.key | sudo apt-key add -
		sudo apt-get update
		sudo apt-get install acestream-engine

## Install acestream-launcher

### PIP
		pip2 install acestream-launcher

### Old method
		sudo apt-get install python python-psutil python-pexpect python-notify2 vlc
		git clone https://github.com/jonian/acestream-launcher.git
		sudo bash ./install.sh

## Enjoy
		acestream-launcher acestream://edca97797b5749855c9c0d512312312312323



ARDUINO ERROR
=============
Exception in thread "main" java.lang.ExceptionInInitializerError
    at processing.app.Preferences.setColor(Preferences.java:851)
    at processing.app.Preferences.init(Preferences.java:273)
    at processing.app.Base.main(Base.java:117)
Caused by: java.lang.NumberFormatException: For input string: "9-e"
    at sun.misc.FloatingDecimal.readJavaFormatString(FloatingDecimal.java:2054)
    at sun.misc.FloatingDecimal.parseFloat(FloatingDecimal.java:122)
    at java.lang.Float.parseFloat(Float.java:453)
    at java.lang.Float.<init>(Float.java:534)
    at processing.core.PApplet.<clinit>(Unknown Source)
    ... 3 more

		sudo update-alternatives --config java
choose Java 8: /usr/lib/jvm/java-8-oracle/jre/bin/java



Warning: the ECDSA host key for 'retropief' differs from the key for the IP address '192.168.0.147'
===========================================================================
		ssh-keygen -R 192.168.0.147



HKU VPN on Ubuntu
=============
		sudo apt install network-manager-openconnect-gnome



HP Printers
===========
		sudo apt install hplip-gui
or (without HP GUI tools)
		sudo apt install python3-pyqt4

		sudo hp-setup

## Network Printer
	Connection (I/O) Type: Network/Ethernet/Wireless network

### HPLIP cannot detect printers in your network.
	Tick "Manual Discovery", enter IP of the printer (In my PC, I can check with Avahi Zeroconf Browser)



SETUP MINECRAFT SERVER THROUGH HAMACHI
======================================
[Source](https://minecraft.gamepedia.com/Tutorials/Setting_up_a_server)

# Setup Minecraft Server
Get minecraft server from [official site](https://minecraft.net/zh-hant/download/server)
e.g.
		wget https://s3.amazonaws.com/Minecraft.Download/versions/1.12.2/minecraft_server.1.12.2.jar

Change permission
		chmod u+x minecraft_server.1.12.2.jar

Start the server
(start with 32MB RAM and maximum 1024 MB)
		java -Xms32M -Xmx1024M -jar minecraft_server.jar nogui

Agree Eula
		nano eula.txt
Change to true, then start again

# Setup Hamachi VPN
## Install and setup
		wget https://www.vpn.net/installers/logmein-hamachi_2.1.0.174-1_amd64.deb

		sudo dpkg -i logmein-hamachi_2.1.0.174-1_amd64.deb

		sudo nano /var/lib/logmein-hamachi/h2-engine-override.cfg
Content:
Ipc.User m2

		sudo /etc/init.d/logmein-hamachi restart

## Start
		hamachi login

		hamachi join 380-076-647 4everalone

		hamachi
Address: 25.89.125.89



# login screen loop after sudo startx
[Source](https://askubuntu.com/questions/223501/ubuntu-gets-stuck-in-a-login-loop)
		chown s03311251:s03311251 .Xauthority



# USB device no permission
owner/group of the device are root/dialout, add user to group dialout.
		sudo usermod -a -G dialout <username>



# Mojibake(亂碼) under some oh-my-zsh theme
Powerline font needed
		sudo apt-get install fonts-powerline
or [Download here](https://github.com/powerline/fonts)



# Close laptop lid without suspend
[Source](https://askubuntu.com/questions/15520/)
		sudoedit /etc/systemd/logind.onf
add:
		HandleLidSwitch=ignore

For Ubuntu >15.04:
		sudo service systemd-logind restart
For Ubuntu >? (at least >16.04):
		sudo systemctl restart systemd-logind.service



# MAME
## Install
[Source](http://www.upubuntu.com/2012/10/how-to-install-mame-multiple-arcade.html)

		mame
		cd ~/.mame && mame -cc
		pluma ~/.mame/mame.ini

change rompath in mame.ini

		mkdir  ~/.mame/nvram memcard roms inp comments sta snap diff

## Leave fullscreen
Alt+Enter

## Missing ROM or CHD

take ssf2t.zip as an example:
		mame64 -listroms ssf2t

...
sfx.11m 2097152 CRC(9bdbd476) SHA1(a8520f77f30b97aae36408e0c4ca1ebb
de1808a5)
sfx.12m 2097152 CRC(a05e3aab) SHA1(d4eb9cae66c74e956569fea8b815156f
bd420f83)
qsound.bin 8192 BAD CRC(059c847d) SHA1(229cead1be2f86733dd80573d498
3ba482355ece) BAD_DUMP

qsound.bin is missing



# Imagemagick
## convert: not authorized
[Source](https://stackoverflow.com/questions/42928765/convertnot-authorized-aaaa-error-constitute-c-readimage-453)
```
$ convert *.jpg tmp.pdf
convert: not authorized `tmp.pdf' @ error/constitute.c/WriteImage/1028.
```

change line
<policy domain="coder" rights="none" pattern="PDF" />
to
<policy domain="coder" rights="read|write" pattern="PDF" />
add line
<policy domain="coder" rights="read|write" pattern="LABEL" />



# Disable WiFi Power management in Raspberry Pi
[Source](https://www.raspberrypi.org/forums/viewtopic.php?t=194619)
		sudo iwconfig wlan0 power off

check with
		iwconfig


# APT
## Could not get lock /var/lib/dpkg/lock-frontend
		sudo dpkg --configure -a


# Errors were encountered while processing:
		sudo rm /var/lib/apt/lists/* -vf
		sudo apt update



# MATE Calculator from MATE 1.18
[Tips on Ubuntu](http://tipsonubuntu.com/2017/03/15/install-mate-desktop-1-18-in-ubuntu-16-04/)
		sudo add-apt-repository ppa:jonathonf/mate-1.18
		sudo apt update
		sudo install mate-calc
		sudo ppa-purge ppa:jonathonf/mate-1.18
remember not to remove mate-calc



# NEW USERS CAN'T ENTER GUI IN JETSON TX2
add the user in to group "video" so that it can use GPU
		sudo usermod the_new_user_name -a -G video



# "No default controller available" WHEN CONNECTING BLUETOOTH ON JETSON TX2
[ask ubuntu](https://askubuntu.com/questions/688090/cannot-unblock-soft-blocked-bluetooth)

check if blocked
		sudo rfkill list all
if blocked, use:
		sudo rfkill unblock bluetooth



# "sudo: unable to resolve host <your_PC_hostname>"
[ask-ubuntu](https://askubuntu.com/questions/59458/error-message-sudo-unable-to-resolve-host-none)
check the hostname:
		echo "$(</etc/hostname)"
check if the hostname is in hosts:
		echo "$(</etc/hosts)"
modify hosts if not
		


# sudo apt update GPG error, NO_PUBKEY F42ED6FBAB17C654
        sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key F42ED6FBAB17C654



# Waiting for network configuration
[csdn](https://blog.csdn.net/starpicker/article/details/82865673)
[systemd.service — Service unit configuration](https://www.freedesktop.org/software/systemd/man/systemd.service.html)

        /etc/systemd/system/network-online.target.wants/networking.service

TimeoutStartSec=5min













