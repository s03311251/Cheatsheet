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

## PDF

### concat

[askUbuntu](https://stackoverflow.com/questions/2507766/merge-convert-multiple-pdf-files-into-one-pdf)  
Warning! using `pdfunite` or `pdfjam` brakes hyperlinks, unsure with gs(ghostscript), ok with pdftk

``` bash
gs -q -sPAPERSIZE=letter -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=output.pdf file1.pdf file2.pdf file3.pdf
```

## Git

### .gitignore

[stackoverflow](https://stackoverflow.com/questions/987142/make-gitignore-ignore-everything-except-a-few-files#987162)

``` .gitignore
pippo/*
!pippo/pluto
pippo/pluto/*
!pippo/pluto/paperino.xml
```

`!` is for the line above only
