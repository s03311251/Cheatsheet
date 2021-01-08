# Linux Commands

## Proxy

[kifarunix](https://kifarunix.com/how-to-set-system-wide-proxy-in-ubuntu-18-04/)

[ServerLab](https://www.serverlab.ca/tutorials/linux/administration-linux/how-to-set-the-proxy-for-apt-for-ubuntu-18-04/)

try:

``` bash
export http_proxy=http://10.1.1.101:8080/
export https_proxy=https://10.1.1.101:8080/
sudo netplan apply
```

globally apply, append in /etc/environment:

``` plaintext
http_proxy=http://10.1.1.101:8080/
https_proxy=https://10.1.1.101:8080/
```

to use apt, in `/etc/apt/apt.conf.d/proxy.conf`:

``` plaintext
Acquire {
  HTTP::proxy "http://10.1.1.101:8080";
  HTTPS::proxy "http://10.1.1.101:8080";
}
```

* for pip: `pip --proxy http://10.1.1.101:8080 install somepackage --user`

## PDF

* rotate

  

* concat
  * [askUbuntu](https://stackoverflow.com/questions/2507766/merge-convert-multiple-pdf-files-into-one-pdf)  
  * Warning! using `pdfunite` or `pdfjam` brakes hyperlinks, unsure with gs(ghostscript), ok with pdftk

    ``` bash
    gs -q -sPAPERSIZE=letter -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=output.pdf 1.pdf 2.pdf
    ```

* extract pages  
  `  gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=1 -dLastPage=4 -sOutputFile=out.pdf in.pdf`

* GhostScript on Windows
  * `C:\Program Files\gs\gs9.52\bin>gswin64c.exe`

* iamges to pdf
  * `convert *.png output.pdf`

  * Problem: `convert-im6.q16: attempt to perform an operation not allowed by the security policy `PDF' @ error/constitute.c/IsCoderAuthorized/408.`
    * https://stackoverflow.com/questions/52998331/imagemagick-security-policy-pdf-blocking-conversion
    * In `/etc/ImageMagick-7/policy.xml`, change the related line to `<policy domain="coder" rights="read | write" pattern="PDF" />`

## Git

* Proxy
  * [Getting Git to work with a proxy server - fails with “Request timed out” - stackoverflow](https://stackoverflow.com/questions/783811/getting-git-to-work-with-a-proxy-server-fails-with-request-timed-out)
  * `git config --global http.proxy http://proxyuser:proxypwd@proxy.server.com:8080`

### Get a copy of an older vesrion of a file

[stack overflow](https://stackoverflow.com/questions/14995506/how-to-get-a-copy-of-an-older-version-of-a-file-in-a-git-repository/53161472#53161472?newreg=256aebcc543949aba7bc41288768435e)

``` bash
git show revision:repo/module/package/code.file > code.file.old
git show revision:repo/module/package/code.file # see only
git show revision:./code.file > workdir/code.file.old # relative path, ./ is necessary
```

### .gitignore

[stackoverflow](https://stackoverflow.com/questions/987142/make-gitignore-ignore-everything-except-a-few-files#987162)

``` .gitignore
pippo/*
!pippo/pluto
pippo/pluto/*
!pippo/pluto/paperino.xml
```

`!` is for the line above only

## SAMBA

* [Ubuntu Tutorials](https://tutorials.ubuntu.com/tutorial/install-and-configure-samba)

1. install

   ``` bash
   sudo apt install samba
   ```

2. add directory to share  
   In `/etc/samba/smb.conf`, append:

   ``` config
   [sambashare]
   comment = Samba on Ubuntu
   path = /home/username/sambashare
   read only = no
   browsable = yes
   ```

3. restart and firewall

   ``` bash
   sudo service smbd restart
   sudo ufw allow samba
   ```

## Remote Desktop (RDP) - xrdp

* [How to Install Xrdp Server (Remote Desktop) on Ubuntu 18.04 - Linuxize](https://linuxize.com/post/how-to-install-xrdp-on-ubuntu-18-04/)
* [Ubuntu 18.04: Connect to MATE desktop environment via XRDP - Narrow Escape](https://www.hiroom2.com/2018/05/07/ubuntu-1804-xrdp-mate-en/)
* [How to setup an xRDP server on Ubuntu 18.04 - Vivek Teega](https://medium.com/@vivekteega/how-to-setup-an-xrdp-server-on-ubuntu-18-04-89f7e205bd4e)
* [Remote Desktop — blue screen after login - StackExchange](https://askubuntu.com/questions/1166568/remote-desktop-blue-screen-after-login)

* Install and configure

  ``` bash
  sudo apt install xrdp
  sudo apt install xorgxrdp-hwe-18.04 # for Ubuntu 18.04.3, not sure if necessary
  sudo apt-get install mate-core mate-desktop-environment mate-notification-daemon # for mate

  sudo systemctl status xrdp
  sudo adduser s03311251 ssl-cert

  echo "mate-session" > ~/.xsession # not sure if necessary
  sudo sed -i.bak '/fi/a #xrdp multiple users configuration \n mate-session \n' /etc/xrdp/startwm.sh # not sure if necessary, but seems working after this

  sudo systemctl restart xrdp
  sudo /etc/init.d/xrdp restart # or this? I don't know which one

  # firewall setting
  sudo ufw allow from 192.168.1.0/24 to any port 3389
  sudo ufw allow 3389 # access from anywhere
  sudo ufw allow 3389/tcp # or this
  ```

* Login  
  Session: `Xorg`

## Memory test

* http://benjr.tw/98338
