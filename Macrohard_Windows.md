# Windows Controls

## Network

* list all neighbours in the network
  * [StackExchange](https://superuser.com/questions/340932/how-to-list-all-computers-in-a-windows-wi-fi-network)
  * `arp -a`

* show MAC address
  * `ipconfig /all`

### ICS (Internet connection Sharing)

[Windows 7 Internet connection Sharing (ICS) Host Computer Setup](https://www.home-network-help.com/windows-7-internet-connection-sharing.html)

`Control Panel\Network and Internet\Network and Sharing Center`

### SSH

#### WinSCP

[StackExchange](https://superuser.com/questions/106360/how-to-enable-execution-of-powershell-scripts/533745)
Powershell (run as Administrator)

``` Powershell
set-executionpolicy remotesigned
```

[WinSCP](https://winscp.net/eng/docs/guide_windows_openssh_server#windows_older)

1. Download [OpenSSH](https://github.com/PowerShell/Win32-OpenSSH/releases)
2. Go to the folder, run `powershell.exe -ExecutionPolicy Bypass -File install-sshd.ps1`
3. Control Panel > System and Security > Windows Firewall1 > Advanced Settings > Inbound Rules and add a new rule for port 22
4. Control Panel > System and Security > Administrative Tools and open Services. Locate OpenSSH SSH Server service
    * Action > Properties. In the Properties dialog, change Startup type to Automatic and confirm
    * click the Start the service

#### Windows 10

* [Using the OpenSSH Beta in Windows 10 Fall Creators Update and Windows Server 1709 - Microsoft](https://devblogs.microsoft.com/powershell/using-the-openssh-beta-in-windows-10-fall-creators-update-and-windows-server-1709/)

## create empty file

a 4194304 byte file:

```bat
fsutil file createnew my_file.tmp 4194304
```

## Link

* hard link
  * [How-To Geek](https://www.howtogeek.com/howto/16226/complete-guide-to-symbolic-links-symlinks-on-windows-or-linux/)
  * `mklink /H link_file.txt original_file.txt`

* relative path shortcut:
  * `%windir%\explorer.exe "wineagle\Utility\AsmUsbTest\v140+x64+Debug\AsmUsbTest_v140_64_d.exe"`

* print shortcut:
  * `type mylink.lnk | find "\"`

## Hyper-V

* installation
  * `J:\system\Public\UsefulInternalTools\AutoRepeat Doc\`

## Batch file .bat

* `whereis` equivalent
  * `where`

* press a key to continue ...
  * `pause`

### Print & Read

* print
  * `echo %my_variable%`

* read input
  * `set /p my_variable="Your input:"`

* not to print every line of .bat on terminal
  * `@echo off`

* terminal colour
  * [COLOR - SS64](https://ss64.com/nt/color.html)
  * `COLOR [background][foreground]`
    * Colour attributes are specified by 2 of the following hex digits. There should be **no space** between the two color numbers.
  * Each digit can be any of the following values:
    * 0 = Black
    * 8 = Gray
    * 1 = Blue
    * 9 = Light Blue
    * 2 = Green
    * A = Light Green
    * 3 = Aqua
    * B = Light Aqua
    * 4 = Red
    * C = Light Red
    * 5 = Purple
    * D = Light Purple
    * 6 = Yellow
    * E = Light Yellow
    * 7 = White
    * F = Bright White

* timer

  ```bat
  @echo off
  color 07
  set /p delay_time="Count for (seconds):"
  timeout %delay_time%

  :red_alert
  color 04
  timeout /t 1 /nobreak > nul
  color 0c
  timeout /t 1 /nobreak > nul
  goto red_alert
  ```

### Files

* `xcopy C:\From.txt C:\To`

## Alt code

* × 0215
* ÷ 246
* ° 248/0176
* Ø 0216
* ± 241
* ≥ 242
* ≤ 243
* ≈ 247
* √ 251

* α 224
* ß 225
* Γ 226
* δ 235
* Δ
* ε 238
* Θ 233
* π 227
* µ 230
* Σ 228
* σ 229
* τ 231
* Φ 232
* φ 237
* Ω 234

## Windows Subsystem for Linux

* root directory: `C:\Users\aeemcng\AppData\Local\Packages\CanonicalGroupLimited.Ubuntu20.04onWindows_79rhkp1fndgsc\LocalState\rootfs`
* C:\ : `/mnt/c`

## Macrohard Office

### Word

* Browse Outline (Headings)
  * Ctrl + F -> Press tab "Browse the Heading in your documents"

* Heading Numbering
  * [extendoffice](https://www.extendoffice.com/documents/word/1365-word-number-headings.html)
  1. Home > Multilevel List (on the right of bullet list and numbering list)
  2. Select the style you want
  3. Click "Define New Multilevel List"
  4. Click "More >>"
  5. Select the level, change "Link level to style:" on the right

* Table of Contents
  * References -> Table of Contents
  * Format: (e.g. no. of levels)
    * References -> Table of Contents -> Insert Table of Contents
    * [Microsoft](https://support.office.com/en-us/article/format-or-customize-a-table-of-contents-9d85eb9c-0b55-4795-8abb-a49885b3a58d#ID0EAACAAA=Office_2010)

* Translate

### Excel

* Find substring
  * [Udemy](https://blog.udemy.com/excel-substring/)
  * `=Find(find_text, within_text, [start_number])`
* split with delimiter
  * `=TRIM(MID(SUBSTITUTE(C2,"<delimiter>",REPT(" ",LEN(C2))),(<Nth field>-1)*LEN(C2)+1,LEN(C2)))`
    * e.g. `=TRIM(MID(SUBSTITUTE(C2,",",REPT(" ",LEN(C2))),(2-1)*LEN(C2)+1,LEN(C2)))`

* Open multiple Excel windows
  * Open a new Excel windows from toolbar and open the file with it
  * [Opening Excel 2007/2010 in New Windows for Multi-Monitor Support](http://fielddata.blogspot.com/2011/07/opening-excel-20072010-in-new-windows.html)
    * add excel to "Open With" by putting a shortcut of "excel.exe" into `%APPDATA%\Microsoft\Windows\SendTo`

* Intersection of 2 sets
  * `=IF(ISERROR(MATCH(A1,$B$1:$B$600,0)),"",A1)`
    * assume the 2 sets are put in A: & B1:B600 respectively

## Powerpoint

* change from imperial to metric units
  * https://support.microsoft.com/en-us/office/change-the-measurement-units-from-inches-to-centimeters-7fb08d33-750b-4e95-b332-e568d4550d82
  * Windows control panel -> Region and Language -> Format -> Additional Setting -> Measurement Unit -> Metric
