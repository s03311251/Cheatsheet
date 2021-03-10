# Linux Cheatsheet

## Shell

* `pluma test.txt &`
  * The & sign instructs the shell to start the program in the background mode. In this mode, the shell will return immediately and continue to accept other commands. Note that if there is no & sign, the shell will be blocked until the gedit program is terminated.

* link
  * hard link: `ln <original> <link>`
  * symbolic (soft) link: `ln -s <original> <link>`

## Proxy

* [kifarunix](https://kifarunix.com/how-to-set-system-wide-proxy-in-ubuntu-18-04/)
* [ServerLab](https://www.serverlab.ca/tutorials/linux/administration-linux/how-to-set-the-proxy-for-apt-for-ubuntu-18-04/)

* try:

  ``` bash
  export http_proxy=http://10.1.1.101:8080/
  export https_proxy=https://10.1.1.101:8080/
  sudo netplan apply
  ```

* globally apply, append in /etc/environment:

  ``` plaintext
  http_proxy=http://10.1.1.101:8080/
  https_proxy=https://10.1.1.101:8080/
  ```

* to use apt, in `/etc/apt/apt.conf.d/proxy.conf`:

  ``` plaintext
  Acquire {
    HTTP::proxy "http://10.1.1.101:8080";
    HTTPS::proxy "http://10.1.1.101:8080";
  }
  ```

VIDEO
=====

## CONVERT
		ffmpeg -i "CCHU 9024 Version 5.mp4" -c:v libvpx -crf 10 -b:v 1M -c:a libvorbis output-file.webm
		ffmpeg -i 00033736.AVI -c:v libx264 -preset fast -crf 22 -c:a aac -strict -2 house.mp4

### MP3 VBR
		ffmpeg -i input.wav -codec:a libmp3lame -q:a 5 output.mp3
quality is encoder specific, for `libmp3lame`:
-b:a 320k	320 CBR (non VBR)
-q:a 0		220-260
-q:a 1		190-250
-q:a 2		170-210
-q:a 3		150-195
-q:a 4		140-185
-q:a 5		120-150
-q:a 6		100-130
-q:a 7		80-120
-q:a 8		70-105
-q:a 9		45-85



## CUT
ffmpeg -ss 00:00:13 -i avseq01.mpg -codec copy rthk.mpg
ffmpeg -ss 00:07:41 -i "我和殭屍有個約會2 粵語(8).mp4" -codec copy -t 00:00:2.7 1.mp4
ffmpeg -ss 00:04:05 -i MOV_0084.mp4 -codec copy -to 00:04:21 2.mp4

mencoder -ss 00:30:00 -endpos 00:00:05 -oac copy -ovc copy originalfile -o newfile

### starting at a non-keyframe
ffmpeg -i movie.mp4 -ss 00:00:03 -t 00:00:08 -async 1 cut.mp4


## CROP
avconv -i in.mp4 -filter:v "crop=out_w:out_h:x:y" -crf 18 out.mp4
eg. avconv -i SAKURA.avi -filter:v "crop=640:480:0:0" -crf 18 out.mp4

## MERGE
ffmpeg -i concat:file1.mpeg\|file2.mpeg\|file3.mpeg -c copy output.mpeg



https://trac.ffmpeg.org/wiki/Concatenate
Create a file mylist.txt with all the files you want to have concatenated in the following form (lines starting with a # are ignored):

	# this is a comment
	file '/path/to/file1'
	file '/path/to/file2'
	file '/path/to/file3'

Note that these can be either relative or absolute paths. Then you can stream copy or re-encode your files:

	ffmpeg -f concat -i mylist.txt -c copy output

# MERGE MP4
MP4Box -cat file1.mp4 -cat file2.mp4 -new mergedFile.mp4

# AUDIO+IMAGE->VIDEO
avconv -loop 1 -shortest -i 6cb.jpg -i POKEMON.mp3 -r 1 POKEMON.ogg

ffmpeg -r 1 -loop 1 -i Untitled.png -i cbc_raw4.wav -acodec copy -r 1 -shortest -vf scale=1280:720 cbc_raw4.avi

# AUDIO+VIDEO->VIDEO
ffmpeg -i "CCHU9024 version 2.mp4" -i "CCHU9024 version 2.1.mp3" \-c:v copy -c:a aac -strict experimental \ -map 0:v:0 -map 1:a:0 output.mp4

# REMOVE AUDIO
		ffmpeg -i example.mkv -c copy -an example-nosound.mkv

# SPEED UP
ffmpeg -i "CCHU9024 version 1.mp4" -filter_complex "[0:v]setpts=0.77*PTS[v];[0:a]atempo=1.298701299[a]" -map "[v]" -map "[a]" output.mp4

# CONVERT TO GIF
http://xmodulo.com/2013/11/convert-video-animated-gif-image-linux.html

STEP.1: (can skip -t,-ss,-r)
ffmpeg -t <duration> -ss <starting position in hh:mm:ss format> -i <input_video> out%04d.png
eg. ffmpeg -i 1.mp4 out%04d.png

STEP.2: (can skip -resize)
convert -delay <ticks>x<ticks-per-second> -loop 0 out*.png -resize <dimension(can skip width/height)> <output-gif-file>
eg.convert -delay 1x20 -loop 0 out*.png -resize x100 animation.gif

STEP.3:
convert -layers Optimize animation.gif animation_small.gif

# TIME LASPE

		ffmpeg -framerate 30 -i image%04d.jpg -c:v libx264 -r 30 outputfile.mp4
		ffmpeg -framerate 10 -start_number 10 -i %10d.jpg -c:v libx264 -r 10 outputfile.mp4
		ffmpeg -y -framerate 24 -i /home/pi/raspberry/data/%10d.jpg -c:v libtheora -qscale:v 6 -r 24 /home/pi/raspberry/data/output.ogg


Let’s break down those options:

    -framerate 30 = This is the input frame rate. It effectively says that you want each input image to appear on screen for 1/30 of a second. If you wanted each input image to appear on screen for a whole second, you’d use a -r 1. The default is 25. If you select a slower input frame rate than the output frame rate, ffmpeg will simply duplicate the input image appropriately so that it stays on screen for the desired amount of time.
    -i image%04d.jpg = ffmpeg will look for input images that match this filename pattern. As with the discussion above on filename patterns, the %04d tells ffmpeg to look for a 4-digit number in the filename. If you used %05d to generate your captured images, you’d want to use %05d here as well.
    -c:v libx264 = This specifies the video encoding to be used. libx264 is a good default choice for high quality and low file size, and should be readable by all sorts of video players. It may or may not work in some versions of PowerPoint on some operating systems, so check that before you get too excited about adding video into your presentations. It is possible to output as a wmv file or other formats, so search the web if you need a different format.
    -r 30 = specifies the framerate of the final movie. 30 frames per second is fairly standard, 24 fps is also common, and you could do something like 48 or 60 if you have special needs.
    outputfile.mp4 = the filename and format. As before, you can specify a different directory path to put the file into, otherwise it will appear in the current working directory. The .mp4 format should work on most web and mobile devices, and uploads to Youtube just fine.

# ADD SUBTITLE
http://stackoverflow.com/questions/21363334/how-to-add-font-size-in-subtitles-in-ffmpeg-video-filter

	ffmpeg -i gundam_hea_engineer_hea_pilot.mp4 -vf subtitles=subtitle.srt -strict -2 output_video.mp4

If need to change colour/font/size:

	ffmpeg -i subtitle.srt subtitle.ass
	ffmpeg -i gundam_hea_engineer_hea_pilot.mp4 -vf subtitles=subtitle.ass -strict -2 output_video.mp4

# RIPPING VCD
http://elliotli.blogspot.hk/2008/10/ripping-vcd-in-linux.html

Convert into .mpg
		vcdxrip -C=/dev/cdrom

# AUDIO DELAY
delay audio by 3 seconds
		ffmpeg -i test.webm -itsoffset 3.0 -i test.webm -map 0:v -map 1:a -vcodec copy -acodec copy delay.webm

delay video by 3 seconds
		ffmpeg -i test.webm -itsoffset 3.0 -i test.webm -map 1:v -map 0:a -vcodec copy -acodec copy delay.webm


AUDIO
==========

# NOISE REDUCTION
http://www.zoharbabin.com/how-to-do-noise-reduction-using-ffmpeg-and-sox/

Split the audio and video streams into 2 seperate files:
The VIDEO stream: 
	ffmpeg -i 魔女blog.mp4 -qscale 0 -an tmpvid.mp4
The AUDIO stream: 
	ffmpeg -i 魔女blog.mp4 -qscale 0 tmpaud.wav

Generate a sample of noise from the audio of the file:
	ffmpeg -i input.mp4 -vn -ss 00:00:00 -t 00:00:01 noiseaud.wav
-ss: the time offset from beginning. (h:m:s.ms).
-t duration: record or transcode duration seconds of audio/video.
Choose a segment of the audio where there’s no speech, only noise (e.g. speaker was silent for a sec).

Generate a noise profile in sox:
	sox noiseaud.wav -n noiseprof noise.prof

Clean the noise samples from the audio stream:
	sox tmpaud.wav tmpaud-clean.wav noisered noise.prof 0.21
Change 0.21 to adjust the level of sensitivity in the sampling rates (I found 0.2-0.3 often provides best result).

Merge the audio and video streams back together:
	ffmpeg -i tmpaud-clean.wav -i tmpvid.mp4 -q:a 0 -q:v 0 -strict -2 vid.mp4



# RIP VCD
http://elliotli.blogspot.hk/2008/10/ripping-vcd-in-linux.html

Convert into MPG file
		vcdxrip -C=/dev/cdrom



# PLAY MP3
		sudo apt install libsox-fmt-mp3
		play something.mp3



# MP3 GAIN
[Source](https://www.linux.com/news/adjusting-mp3s-mp3gain)

default 89 dB
-k: automatically lower Track gain to not clip audio
		mp3gain -r -k *.mp3 # single song
		mp3gain -a -k *.mp3 # album

tweak dB
		mp3gain -r -d 2.0 myquietsong.mp3 # 89 + 2.0 = 91 dB

undo
		mp3gain -u file.mp3



# VOLUME OF THE SPEAKER
[Source](https://unix.stackexchange.com/questions/21089/how-to-use-command-line-to-change-volume)

		amixer set Master 50%

To turn volume up/down 5%:

		amixer -D pulse sset Master 5%+
		amixer -D pulse sset Master 5%-

Mute/Unmute

		amixer -D pulse sset Master mute
		amixer -D pulse sset Master unmute

IMAGE
==========

# RESIZE
http://www.imagemagick.org/Usage/resize/
convert dragon.gif -resize 64x64 resize_dragon.gif
	82x100 -> 52x64 (based on the smallest fitting dimension)
convert dragon.gif -resize 64x64^ resize_dragon.gif
	82x100 -> 64x78 (based on the largest fitting dimension)
	convert *.png -resize 50% out/test.png

# FLIP
vertical
		convert MR1blue_2450x8000_100dpi.png -flip MR1blue_2450x8000_100dpif.png

horizontal
		convert MR1blue_2450x8000_100dpi.png -flop MR1blue_2450x8000_100dpif.png

# REDUCE QUALITY
convert DSC_0050.JPG -quality 75% DSC_0050.jpg

# SPLIT IMAGE INTO SEPERATE IMAGES
convert -crop 877x1241 *.jpg cropped_%d.jpg
convert -crop 780x1232+920+0 pc2015-2-*.jpg r2.jpg

# MERGE
convert \( 1.png 2.png -append \) \
\( 3.png 4.png -append \) +append result.png

# IMAGE TO PDF
convert *.png xyz.pdf

# PDF TO IMAGE FOR 1 PAGE ONLY
convert 0001_vol2.pdf[0] 0001_vol2_cover.jpg
convert -density 144 0708_vol1.pdf[0] -resize 50% 0708_vol1_cover.jpg

# REPLACE COLOUR IN A IMAGE
(from white to red)
convert image -fuzz XX% -fill red -opaque white result
convert image -fuzz XX% -fill red -opaque 'rgb(254,254,254)' result

# WEBP
https://developers.google.com/speed/webp/download?hl=zh-TW

		cwebp -q 70 picture_with_alpha.png -o picture_with_alpha.webp
		dwebp picture.webp -o output.png
		vwebp picture.webp

# TAKE PICTURE FROM WEBCAM
[](https://askubuntu.com/questions/106770/take-a-picture-from-terminal)
		ffmpeg -f video4linux2 -s 640x480 -i /dev/video0 -ss 0:0:2 -frames 1 /tmp/out.jpg










FILE
==========

# PRESENT WORKING DIRECTORY
		pwd

# CREATE EMPTY FILE
		touch <filename>

# DELETE FILE
		rm <filename>
		rm -d <empty directory name>
		rmdir <empty directory name>
		rm -r <non-emptydirectory name> (recursive)
		rm -f <filename> (ignore nonexistent files and arguments, never prompt)
		yes | rm -r <directory> # yes to all

# LIST FILE
		ls

lists the content in long format
		ls -l

lists all content including hidden files or hidden directories
		ls -a

sorts the output by the modification time
		ls -t 

# MAKE DIRECTORY
		mkdir <directory name>

# COPY
		cp [-adfilprsu] 來源檔(source) 目標檔(destination)

# RENAME
		mv a.in b.out

# RSYNC

* multithread
  * <https://stackoverflow.com/questions/24058544/speed-up-rsync-with-simultaneous-concurrent-file-transfers>

* OVERWRITE IF NEWER
  * `rsync --progress -r -u --exclude file1.txt --exclude dir3/file4.txt /from/one /to/another/directory`

* REMOTE
  * `rsync -ahvz Software s03311251@192.168.0.200:/home/s03311251`
    * -a archive mode (= -rlptgoD)
    * -h human readable numbers
    * -v verbose
    * -r recurse into directories
    * -z compress

# DISPLAY CONTENT
[StackExchange](https://unix.stackexchange.com/questions/86321/how-can-i-display-the-contents-of-a-text-file-on-the-command-line)
		echo "$(<filename)"

`cat` is ok but not recommanded:
		cat <filename>

# CHANGE PERMISSION
		sudo chmod [u/g/o/a(ALL)][+/-/=(SET)][r/w/x] filename

eg.
		sudo chmod o+rx file

# ADD USER TO GROUP
		sudo useradd -G {group-name} username

# CHANGE OWNERSHIP
		sudo chown username:group directory

		sudo chown -R username:group directory # recursively
		sudo chown -R s03311251:s03311251 blinkyLED
(change ownership (both user and group) of all files and directories inside of directory and directory itself.)

# CHANGE GROUP
		sudo chgrp debian-transmission ~/Downloads
		sudo chgrp -R debian-transmission ~/Downloads # recursively

# LOCK USER FROM LOGIN
[Source](http://www.ducea.com/2007/12/05/howto-disable-a-user-account-in-linux/)
		sudo passwd nvidia -l
unlock
		sudo passwd nvidia -u

# FIND
		find Path -name Filename [-type Type(file/directory)]
eg.	
		find . -name "hello.*" -type f

# FIND FILES CONTAINING SPECIFIC TEXT
(Source)[https://winaero.com/blog/find-files-containing-text-linux/]
		grep -iRl "your-text-to-find" ./
-i - ignore text case
-R - recursively search files in subdirectories.
-l - show file names instead of file contents portions.

# GLOBAL REGULAR EXPRESSION PRINT (GREP)
search in a file and return the lines that match the pattern specified in regular expression
		grep -E 'Regular Expression' filename
	(-E if regular expression is used)

## REGULAR EXPRESSION
.	Matching any single character.

^	Match the beginning of the line only.

$	Match the end of the line only.
	Put at the end -> Eg 'fuc$'

?	A single character followed by an ?, will match zero or one occurrence.
	E.g., 	'ap?' -> find 'a', 'ap'

+	A single character followed by an +, will match one or more occurrences.
	E.g., 	'ap+' -> find 'ap', 'app', 'appp'...

*	A single character followed by an *, will match zero or more occurrences.
	E.g., 	'ap*' -> find 'a', 'ap', 'app', 'appp'...
	E.g., 	'ap(pl)*' -> find 'ap', 'appl', 'applpl', 'applplpl'...

[]	Character enclosed inside the [ ]will be matched. 
	This can be a single or range of characters.
	E.g.,  '[Aa]pple' -> find 'Apple' and 'apple'
	You can use the “-“ to include a range inclusively. 
	E.g., instead of saying [12345], use [1-5].
	E.g., instead of saying [abcde], use [a-e].

\	Use this to escape the special meaning of a metacharacter. 
	E.g., As “.” means matching any single character, we need to use “\.” to mean that we are matching a dot in a pattern.

pattern{n}		Match n occurrences of the pattern.
pattern{n,}		Match at least n occurrences of the pattern.
pattern{n,m}	Match occurrences of the pattern between n and m.
	E.g.,(ab){3} -> 'ababab'

eg.
'^.{n,m}$'		Lines with length between n and m
'abc.*xyz'		Find 'abc(something)xyz'
'HKD[0-9]*'		Find 'HKD(some number here)'
'^[0-9]{1,2}[a-zA-Z]{3,}[0-9]{4}'	Find '2April2013', '13December2013'

-o	print only the matched parts instead of the whole line
-H	With filename
-h	without filename

# WORD COUNT
		wc (filename)
	-> (line) (word) (byte)

-c	bytes
-m	chars
-l	lines

without filename
		wc < (filename)

# SORT
Alphabetical Order
		sort (filename)

Numberic Sort ('9' in front of '10')
		sort -n (filename)

Reversing order
		sort -r (filename)

Specific sort key field
		sort -k (order of field) -t (field separator) (filename)

eg.	5,Apple,3.5
	4,Chicken,50
	1,Coke,5.5
	10,Jelly,5
	3,Chocolate,15
	2,Milk,8
		sort -k 3 -t , (filename)

Delete duplicate lines, left unique only
		sort -u

# UNIQ
		uniq (filename)

eg.
	Apple
	Apple pie
	Apple pie
	Apple

->	Apple
	Apple pie
	Apple

		uniq -c (filename)

# CHECKING SPELLING
		spell (filename)

eg.	It’s a beautiffful day!
	I am so happpy todday.

->	beautiffful
	happpy
	todday

# CUT
		cut -d (field delimiter) -f (which field) (filename)

eg.	input.txt = Hello World!
		cut -d " " -f 2 input.txt
->	World!

# HEAD
print first 10 lines of a file
		head (filename)

print first N lines
		head -n N (filename)

print first N bytes
		head -c N (filename)

# TAIL
print last 2 lines
		tail -2 (filename)
print second-to-last line
		tail -2 (filename) | head -1

# TR: TRANSLATE AND REPLACE
		tr '[:alnum:]' '[\n*]' < input.txt
		tr -c '[:alnum:]' '[\n*]' < input.txt
-c			complement
-d			delete
[:alnum:]	all letters and digits
[:upper:]	uppercase
[:lower:]	lowercase

		sed "s/^/'/" < file.txt
		sed -e "s/[0-9]\+.[0-9]\+.[0-9]\+.[0-9]\+\t//g" < file.txt
can use regular expression with -e in the command and \ in front of the symbol
https://www.tutorialspoint.com/unix/unix-regular-expressions.htm

## TO LOWER CASE
		tr '[:upper:]' '[:lower:]'

# DIFFERENCE BETWEEN 2 FILES
		diff fileA fileB

a -> add
c -> change
d -> delete

	eg. fileA	fileB
		aaa		eee
		bbb		aaa
		ccc		ddd

	->	0a1		means to add a line after line 0 of fileA, the line to be added is line 1 of fileB (denoted by > eee).
		> eee
		2,3c3	means to change line 2,3 of fileA to line 3 of fileB. The lines to be deleted are bbb and ccc (denoted by < bbb and < ccc); the line to inserted is ddd (denoted by > ddd).
		< bbb
		< ccc
		---
		> ddd

# REDIRECTION OPERATOR >
		wc data.txt 1> result.txt
		1(output), 2(error); default 1

appends the content to a file instead of replacing the content of the file.
		wc data.txt 1>> result.txt

Hide unwanted command output in shell script
		cp file123 fileabc 1>/dev/null 2>&1
/dev/null = nowhere
&1 -> redirect standard error (2>) to same location as standard output (1>)

# REDIRECTION OPERATOR <
		./add.o < input.txt
eg.	"add.o" adds 3 intergers
	"input.txt" = "3 4 5"

		./add.o
	3 4 5
	12

		./add.o < input.txt
	12

Important note: It is the cin in the add.cpp that receives the values from the file input.txt. Do not mix this technique with C++ file I/O (fstream objects).

# TEE
		last | tee last.list

# TEST CASE
		./add.o < input.txt > output.txt
		cat output.txt
	12
		diff output.txt correct.txt

# PIPE |
		ls -l | grep "Jan 26"

=
		ls -l > files.txt
		grep "Jan 26" < files.txt

can use with < >
eg.	$sort -k3 -n data.txt | cut -d' ' -f2,3 > result.txt

# FIND FILE WITH x PERMISSION
		ls -l | grep -E '^...x..x..x'

# FIND PATHS FOR PROGRAM
		which -a bash
->	/bin/bash

# MORE & LESS
The command more simply pause the file in each page so that you can switch to the next page by pressing the space keyboard button. This is useful for viewing long files like iostream.
		cat Scripts.md | more

less: can use Up & Down Arrow
		cat Scripts.md | less

# FRONTEND OF SUDO
		gksudo eclipse/cpp-neon/eclipse/eclipse

# rar 轉 jpg 教學
1. 準備一張JPG圖片和一個RAR壓縮檔，並放在同一個資料夾下。

2. 到[開始]→[執行]，輸入「cmd」，按確定打開DOS視窗。

3. 使用DOS指令到達上述兩個檔案的存放資料夾，有關DOS指令可以參見簡單的DOS指令。
    例如：若是存放在C槽的WINDOWS資料夾中，可以先輸入「cd　C:\」到達C槽，
    再輸入「cd　WINDOWS」，到達WINDOWS資料夾下。

4. 使用Copy指令合併檔案：
     到達目標資料夾後，
     輸入「copy/b　(圖片名稱).jpg　+　(壓縮檔名稱).rar　(新圖片名稱).jpg」
     待「複製了1個檔案」訊息出現後，表示製作完成。

5. 輸入「exit」退出。

Linux 裡可以使用 cat 把多個檔案合併成一個檔案，用 spilt 把檔案分割
例1：cat file1 file2 file3>file5
例2：spilt -b 200m a small

那在 Windows 裡的話可以用 copy 來做到跟 cat 一樣的事情
例1：copy /b file1+file2+file3 combineFileName

# BULK RENAME
http://tips.webdesign10.com/how-to-bulk-rename-files-in-linux-in-the-terminal

		rename -n 's/AAA/BBB/' *.pdf (test run)
		rename -v 's/AAA/BBB/' *.pdf

Perl regular expressions
http://www.troubleshooters.com/codecorn/littperl/perlreg.htm

# OPEN .lnk FILES
		strings filename.lnk

# PRINT RESOLVED SYMBOLIC LINKS
		readlink this_file_is_a_link

# EPUB TO MOBI
(Calibre is required)
		ebook-convert "The Grapes of Wrath - John Steinbeck.epub" "The Grapes of Wrath - John Steinbeck.mobi"

# UNCOMPRESS ECM FILE
(sudo apt-get install ecm)
		ecm-uncompress "Final Fantasy VIII (E) (Disc 4) [SLES-32080].bin.ecm" "Final Fantasy VIII (E) (Disc 4) [SLES-32080].bin"

# $PATH
http://askubuntu.com/questions/148337/adding-a-directory-to-a-path-in-profile

Check PATH
		echo $PATH

Add that directory to the end of the path
	Add following line at the end of ~/.profile:
	export PATH="$PATH:$HOME/Software/eclipse-java"

# MOUNT
[Source](https://help.ubuntu.com/community/Fstab)

You do not mount /dev/sda, that refers to the entire disk. You mount /dev/sda1 or whatever partition you want.

Check
		lsblk

Make a mount point, call it anything you like.
		sudo mkdir /media/2tb

Mount
		sudo mount -o ro /dev/sda1 /media/2tb

Unmount
		sudo umount /media/2tb



# UNMOUNT
		sudo fdisk -l
		sudo umount /media/s03311251/0811-0AD0



# EXTRACT TAR
	-x	extract
	-v	verbosely list files processed
	-f	file "loaction right after -f"
		tar -xf matlab92-glnxa64.tar.xz

## Incremental backups with tar



# DOWNLOAD WITH URL

* <https://stackoverflow.com/questions/2227182/how-can-i-find-out-a-files-mime-typecontent-type>
  * `wget http://example.com/file.jpg`
  * resume: `wget -c http://example.com/file.jpg`

# MIME TYPE
		file -i MSN.mp3
MSN.mp3: audio/mpeg; charset=binary

		file --mime-type MSN.mp3 
MSN.mp3: audio/mpeg

		file -b --mime-type MSN.mp3 
audio/mpeg
	


TWITCH
==========
		livestreamer http://www.twitch.tv/underground_dv source
		livestreamer http://www.twitch.tv/underground_dv medium
		livestreamer http://www.twitch.tv/underground_dv audio



READ SIMPLIFIED CHINESE IN PLUMA
================================
		gsettings set org.mate.pluma auto-detected-encodings "['UTF-8','GB2312', 'BIG5', 'BIG5-HKSCS', 'EUC-TW', 'CURRENT', 'ISO-8859-15', 'UTF-16']"



CHECK OpenGL VERSION
====================
		glxinfo | grep "OpenGL version"





CONVERT .CUE INTO .ISO
======================
		bchunk IMAGE.bin IMAGE.cue ANYNAME.iso





SCREEN 
==========

## ORIENTATION
		xrandr -o left/right/normal/inverted

(have bug in kernal: normal <-> inverted => black screen)
		xrandr -o left && xrandr -o inverted



## SECONDARY SCREEN AT 1680x1050

### Setup
		gtf 1680 1050 60
copy the output, then run something like:
		xrandr --newmode "1680x1050_60.00"  147.14  1680 1784 1968 2256  1050 1051 1054 1087  -HSync +Vsync

		xrandr --addmode VGA-1 "1680x1050_60.00"

### Apply
		xrandr --output VGA-1 --mode "1680x1050_60.00"



MULTI-LANGUAGE IN SML/SVG
=========================
        <switch allowReorder="yes">
            <text systemLanguage="de">de</text>
            <text systemLanguage="en">en</text>
            <text systemLanguage="es">es</text>
            <text systemLanguage="fr">fr</text>
            <text systemLanguage="it">it</text>
            <text systemLanguage="cs">cs</text>
            <text systemLanguage="tl">tl</text>
            <text>other</text>
        </switch>



GRUB
==========

## GRUB PASSWORD
[](http://askubuntu.com/questions/656206/how-to-password-protect-grub-menu)

Grub allows you to password protect its config and console, as well as individual operating system entries. Please note that this will not stop dedicated individuals, especially the ones that know what they are doing. But I assume you know that. Lets get started.

### generate a password hash
You could store your grub password in plain text but that is entirely insecure and anyone that had access to your account could quickly figure it out. To prevent this we hash the password using the grub-mkpasswd-pbkdf2 command, like so:

		user@host~ % grub-mkpasswd-pbkdf2
		Enter password: 
		Reenter password: 

PBKDF2 hash of your password is grub.pbkdf2.sha512.10000.63553D205CF6E...

While you type your password no characters will show in the terminal, this is to prevent people looking over your shoulders, etc. Now, copy the entirety of your hash with Ctrl+Shift+C.

### protecting the config, console
Run:
		sudo nano /etc/grub.d/40_custom

This will create a new configuration file called 40_custom in grub's configuration directory. Now add the lines:

		set superusers="username"
		password_pbkdf2 username hash

Where username is a username of your choice and hash is the hash we generated in the last command. Press Ctrl+O and then Ctrl+X to save and quit. Run:

		sudo update-grub

To finalize the changes. Now, when anyone attempts to edit the grub configuration or access a grub console it will prompt them for a username and password. 

### CHECK SHA256 SUM
		sha256sum file

output into a text file
		sha256sum file > file.sha




## BOOT TO CLI
(Source)[http://ubuntuhandbook.org/index.php/2014/01/boot-into-text-console-ubuntu-linux-14-04/]
Edit /etc/default/grub:
	Disable the Ubuntu purple screen:
		#GRUB_CMDLINE_LINUX_DEFAULT=”quiet splash”

	Boot directly into text mode:
		GRUB_CMDLINE_LINUX=”text”

	Grub Menu into real black & white Text Mode:
		GRUB_TERMINAL=console

		sudo update-grub

For system using systemd i.e. Ubuntu >15.04:
		sudo systemctl set-default multi-user.target
To change back:
		sudo systemctl set-default graphical.target

Start GUI
		sudo /etc/init.d/lightdm start



## OVERWRITTEN
(Source)[https://askubuntu.com/questions/992746/dual-boot-kubuntu-overwritten-grub]

		sudo update-grub2
		sudo grub-install /dev/sda



USING VI
==========

use vi
		/etc/vi <filename>
quit
		:wq
insert
		i



GIT
==========

# Start
		git init

Start a project for sharing 
can't edit files and commit changes
If using Github then no need
		git init --bare my-project.git

# Create a repo on Github
		git remote add <name> <url>
eg
		git remote add origin https://github.com/s03311251/hello.git

		git push <repository> <refspec>...
eg
		git push -u origin master

# Clone
		git clone <repo>
eg
		git clone https://github.com/s03311251/hello.git
	-> pwd test -> clone in test/hello
eg
		git clone https://github.com/s03311251/hello.git fuck
	-> pwd test -> clone in test/fuck

# Config
		git config --global --edit

	Name
		git config --global user.name <name>

	Email
		git config --global user.email <email>

	Alias
		git config --global alias.<alias-name> <git-command>

	Text editor
		sudo git config --system core.editor <editor>

	Credential Helpers: do not need to type username and pw every time for GitHub (default: 15 min)
	[Source](http://stackoverflow.com/questions/5343068/is-there-a-way-to-skip-password-typing-when-using-https-on-github)
		git config --global credential.helper cache

# Add file
		git add <file1> <file2> <file3>
		git add .

# Status
		git status

# Reset
		git reset

	Discard changes
		git reset --hard

	Unstages the file, but preserve its contents
		git reset [file]

	Undoes all commits after [commit] , preserving changes locally
		git reset [commit]

	Revert back certain file
		git checkout [file]

# Commit
		git commit -m "<commit>"

		git commit -m "Add new feature
		> 
		> After print \"Hello World\!\", it will read a line (your name), then print
		> \"Hello (name)\!\"."

use text editor
can't use GUI editor like pluma
		git commit

1st line: Abstract of the contents changed by commits
2nd line: Blank line
3rd line and the following lines: Reason for changes

1. Separate subject from body with a blank line
2. Limit the subject line to 50 characters
3. Capitalize the subject line
4. Do not end the subject line with a period
5. Use the imperative mood in the subject line
	"spoken or written as if giving a command or instruction"
6. Wrap the body at 72 characters
	Git never wraps text automatically. When you write the body of a commit message, you must mind its right margin, and wrap text manually.
7. Use the body to explain what and why vs. how

# View history
		git log
	just showing subject line
		git log --oneline
		git shortlog
	Graph
		git log --graph --oneline

# Show difference
	from last commit
		git diff HEAD HEAD~1

# Get back old commits
		git checkout [commit] -b [branch]
		git checkout [commit] .	# the same
	checkout a branch before editing, otherwise -> detached head
		git checkout master

# Branch
	Create
		git branch [branch name]

	Check how many branches are there
		git branch -v

	Change branch
		git checkout [branch name]

	Or create + change branch
		git checkout -b [branch name]

	Push with your new branch
		git push --set-upstream origin new-branch

	Delete local branch
		git branch -d the_local_branch

	Delete remote branch
		git push origin :the_remote_branch

	Merge branch
		git checkout master
		git pull origin master
		git merge testBranch
		git push origin master

		git branch -d testBranch
		git push origin :testBranch

	Push (and Create) remote branch
	[](https://stackoverflow.com/questions/11266478/git-add-remote-branch)
		git push origin local_branch:remote_branch

# Delete commit
	[](http://stackoverflow.com/questions/1338728/delete-commits-from-a-branch-in-git)
	Warning! Delete your working directory changes!
		git reset --hard HEAD~1				(1 commit)
		git reset --hard <sha1-commit-id> 	(back to commit you want)
	If already pushed:
		git push origin HEAD --force		(force update)



# Change commit

## last commit
	[](https://stackoverflow.com/questions/3042437/change-commit-author-at-one-specific-commit)
		git commit --amend --author="Author Name <email@address.com>"

### Add files only
		git add the_left_out_file
		git commit --amend --no-edit

## not last commit
    [](https://stackoverflow.com/questions/3042437/how-to-change-the-commit-author-for-one-specific-commit)

Method 1: use rebase

Method 2:
        git checkout 03f482d6
        git commit --amend --author "New Author Name <New Author Email>"
let's say new commit is 42627abe
        git replace 03f482d6 42627abe
        git filter-branch -- --all
remove original commit
        git replace -d 03f482d6
        git push -f origin master



# Put in other server
	check
		git remote -v

	remgove
		git remote rm destination

	add
		git remote add source https://github.com/kam3k/laser_line_extraction

	add to a PC on local network
		git remote add cone s03311251@192.168.1.116:/home/s03311251/Documents/Megaman_2/catkin_ws/src/m2_mr2019

	change
		git remote set-url origin https://github.com/s03311251/laser_line_extraction

	setting
		(find it later)

# Detached Head
		git commit -m "....."
		git branch my-temporary-work
		git checkout master
		git merge my-temporary-work

# Merge Conflict
	set merge tool (default: vimdiff)
		git config --global merge.tool mold
	
	solve merge conflict
		git mergetool

	remove merge head if you don't want to face it
		git merge --abort

# .gitignore
	#				as a comment
	ends with /		directory foo and paths underneath it, but not match a file foo
	(e.g. foo/)


* [stackoverflow](https://stackoverflow.com/questions/987142/make-gitignore-ignore-everything-except-a-few-files#987162)

  ``` .gitignore
  pippo/*
  !pippo/pluto
  pippo/pluto/*
  !pippo/pluto/paperino.xml
  ```

  * `!` is for the line above only

# Remove
		git rm file1.txt

	Remove only from repo
		git rm --cached file1.txt

# "Checkout-and-Link" (as it's kinda like Jump-and-Link XD)
## Stash: save indexed changes to temporary box
		git add .
		git stash
		git checkout master

		git stash list
		git checkout my-branch
		git stash apply stash@{0}
        
### Stash with a name
instead of `git stash`:
		git stash push -m "stashname"

### peek inside a stash
		git stash list
		git stash show -p stash@{1}

### drop stash
stash disappear only after "git stash pop"(commit suicide like Cyrus) but not "git stash apply"
to delete the stash:
		git stash drop stash@{2}

### recover dropped stash
[Source](https://stackoverflow.com/questions/89332/how-to-recover-a-dropped-stash-in-git)
find dropped stash
		git fsck --no-reflog | awk '/dangling commit/ {print $3}'
recover
		git stash apply <the hash>

## Reset
		git reset --hard HEAD
		git checkout master

### Reset single file
		git checkout filename

# Recover commit after git reset --hard
[](https://stackoverflow.com/questions/5788037/recover-from-git-reset-hard)
[](https://stackoverflow.com/questions/9560184/recover-dangling-blobs-in-git)
		git reset --hard HEAD~1 # fucked up
		git fsck --lost-found
		git git branch recovered-branch <dangling-commit-sha-goes-here>

# Override name & e-mail for 1 commit
		git -c "user.name=BananaShinshi" -c "user.email=s03311251@hotmail.com" commit -m "fire_catapult.py"

# Remove a large file from history
[](https://help.github.com/articles/removing-sensitive-data-from-a-repository/)
[](https://rtyley.github.io/bfg-repo-cleaner/)
Make sure the latest commit does not contains the file
		bfg --delete-files <filename> <root of repo=folder containing .git>
e.g.
		~/Software/bfg-1.13.0.jar --delete-files cyclone_mecanum.xcf ../..




POWER CONSUMPTION
=================
		sudo powertop



OPEN X WINDOW
=============
		startx



SSH
==========
		ssh pi@192.168.1.33
		ssh pi@s03311251.asuscomm.com -p 2022

		scp (file) pi@192.168.1.33:~/Downloads
		scp -r (folder) pi@192.168.1.33:~/Downloads

		sftp pi@192.168.1.33

		sftp> ls
		sftp> lls

		sftp> put (file)
		sftp> get (file)

		sftp> mkdir (dir)
		sftp> put -r (dir)

		sftp> exit

		sftp> rm folder_name/*
		sftp> rmdir folder_name

## SSH Key
[Source](https://blog.gtwang.org/linux/linux-ssh-public-key-authentication/)
[]()
		mkdir -p ~/.ssh
		chmod 700 ~/.ssh
		ssh-keygen
GitHub said that:
		ssh-keygen -t rsa -b 4096 -C "your_email@example.com"

		ssh-copy-id s03311251@192.168.your.PC

GitHub: Copy ~/.ssh/id_rsa.pub and add under "SSH and GPG keys"

FIND IP
==========

* `curl ifconfig.co`

* `ifconfig`
  * <https://ubuntu.com/blog/if-youre-still-using-ifconfig-youre-living-in-the-past>

* `ip -c address show` / `ip -c a`
  * `-c`: coloured

SHOW IP ONLY
============
[Source](https://stackoverflow.com/questions/8529181/which-terminal-command-to-get-just-ip-address-and-nothing-else)
		ip -4 addr show wlan0 | grep -oP '(?<=inet\s)\d+(\.\d+){3}'
		ifconfig wlan0 | grep 'inet addr' | cut -d: -f2 | awk '{print $1}'
		hostname -I # show all IP, only when there's 1 interface only
Anyone of them is ok



FIND ATTACHED DEVICES IN LAN
============================
		sudo nmap -sP 192.168.0.0/24



CHECK IF PORTS OPEN
===================
		nmap -p 80 example.com
		nmap example.com # all ports



PTT
==========
		ssh bbsu@ptt.cc



REMOTE DESKTOP USING RDP
========================
[Source](https://magiclen.org/rdesktop/)
		rdesktop hkurobotics.ddns.net
		rdesktop -u "hkum2" -p "m2m2m2m2" -g 1364x715 hkurobotics.ddns.net 

		rdesktop -x 0x8F mywinserver   # modem default + font smoothing
		rdesktop -x 0x81 mywinserver   # broadband default + font smoothing
		rdesktop -x 0x80 mywinserver   # LAN default + font smoothing


TERMINAL
==========
# Cowsay
		echo "Hello, World!" | cowsay
		fortune | cowsay

Use other ASCII art (-f)
		fortune | cowsay -f tux

User other eyes
		fortune | cowsay -d -f unipony

Random
		fortune | cowsay -f `ls /usr/share/cowsay/cows/ | shuf -n 1`

Setup
See Problems.md

# Clear Terminal History
[Source](https://www.howtogeek.com/179022/how-to-clear-the-terminal-history-on-linux-or-mac-os-x/)
		history -c
		rm ~/.bash_history

# Check alive process
		ps aux | grep process_name
# Kill Process
	Work even if Ctrl+C won't work
	Press Ctrl+Z, then:
		kill -9 %1 (or '%N' in general) 

# Alias
		alias avconv="ffmpeg"

	add into .bashrc so that it loads alias when open terminal
		
# Google Drive on Caja
[Source](http://www.omgubuntu.co.uk/2017/04/mount-google-drive-ocamlfuse-linux)
		google-drive-ocamlfuse
		mkdir ~/Google-Drive
		google-drive-ocamlfuse ~/Google-Drive



NOTIFICATION
============
		notify-send (title) (content)
		notify-send (title) (content) -i (icon)

Show for 1 sec
		notify-send (title) (content) -t 1000

Disappear only after click
		notify-send (title) (content) -t 0



RUN ON LOGIN
============
Append ~/.profile



SCAN IMAGE
==========

		scanimage >image.pnm
list devices e.g. printer
		scanimage -L

FIREFOX
==========

* WHOLE PAGE SCREENSHOT ON FIREFOX
  * Press Shift-F2, then:
    * `screenshot --fullpage`

* EDIT WEB PAGE ON FIREFOX
  1. right click -> Inspect Element
  2. edit the info in Inspector

* taobao.com can't switch location
  * <https://myptt.cc/article-threading/971e96475eb740c4a10585e6b0f8a2cb>
  * disable AdBlock

CHECK FOR MEMORY LEAK IN C PROGRAMMING
======================================
		valgrind --leak-check=full ./a.out
look at "total heap usage:"



MINICOM
==========
## Setting
		sudo minicom -s

## Execute
		sudo minicom



SERIAL MONITOR
==============
		screen /dev/ttyACM0 38400
exit: Ctrl+A -> \ -> y



TMUX
==========
Prefix key:		Ctrl+B
Pane:
	Horizontal:	%
	Hertical:	"
Window:
	New:		C
	Close:		&
	Previous:	P
	Next:		N
Session:
	Detech:		D
	Switch:		S
Scroll:			[
				press q to quit
 
list session
		tmux ls
attach 0th session
		tmux attach -t 0
kill 0th session
		tmux kill-session -t 0

start tmux with detached session
		/usr/bin/tmux new-session -s wtpi_bot -d /home/m2/BGM/telegram_music_player.py \; set -t wtpi_bot remain-on-exit on
-s:	session name



## Package Manager

### apt

* Add Repository
  * `sudo apt-add-repository "deb http://download.virtualbox.org/virtualbox/debian $(lsb_release -sc) contrib"`

* Update alternative
  * `sudo update-alternatives --config java`

### pacman

### AUR (Arch User Repository)

* Preparation
  * <https://wiki.archlinux.org/index.php/Arch_User_Repository>
  * `sudo pacman -S --needed base-devel`
    * select `all`
  * You may optimize `makepkg`, by the default setting already used parallel build
    * <https://wiki.archlinux.org/index.php/Makepkg#Tips_and_tricks>

* Install
  * <https://dev.to/nabbisen/installing-aur-packages-bdf>
  1. Install the dependencies listed in the page
  2. Check if it is flagged out-of-date
  3. Download the package
     * `git clone https://aur.archlinux.org/gimp-plugin-resynthesizer-git.git`; or
     * `curl -L -O https://aur.archlinux.org/cgit/aur.git/snapshot/gimp-plugin-resynthesizer-git.tar.gz` and `tar -xvf gimp-plugin-resynthesizer-git.tar.gz`
  4. `cd gimp-plugin-resynthesizer-git`
  5. `makepkg -si`
	 * `-s`: install its dependencies
	 * `-i`: automatically `packman -U *` after the package creation is done

MQTT
=========
## Broker Status
		service mosquitto status

## Publish & Subscribe
		mosquitto_sub -t sensor/test
		mosquitto_pub -t sensor/test -m "Hello, world!"



RETROPIE
==========
## SSH
		ssh pi@retropieF

## exit emulationstation from SSH
		killall emulationstation



SWAP PARTITION AND FILES
========================
## Check (both the same)
		cat /proc/swaps
		swapon -s

## Create swap files
[Source](https://digitizor.com/create-swap-file-ubuntu-linux/)

		cd /
		sudo dd if=/dev/zero of=swapfile bs=1M count=1000
1M <= block size
1000 <= number of block = 1000 MB = 1GB

Change to a swap file
		sudo mkswap swapfile

Turn on = mount the swap file
		sudo swapon swapfile

Ensure that the swap file is turned on automatically
		sudo nano etc/fstab
Add the line given below. Save and close
		/swapfile none swap sw 0 0

Check
		cat /proc/meminfo




CREATE LIVE USB
===============
(Source)[https://askubuntu.com/questions/372607/how-to-create-a-bootable-ubuntu-usb-flash-drive-from-terminal]
		sudo dd bs=4M if=/home/s03311251/Downloads/ubuntu-mate-16.04.4-desktop-amd64.iso of=/dev/sdb status=progress conv=fdatasync
progress: show progress
fdatasync: physically write output file data before finishing



PROCESS AND THREAD
==================
## VIEW THREAD
		ps -eLf
LWP: thread ID, if single-thread, LWP=PID
NLWP: # threads for underlying process
CMD: thread name



REPEAT COMMAND CONTINUOUSLY
===========================
-nX is the seconds between intervals
		watch -n1 sensors 

## PDF

* view PDF in terminal
  * Install pdftotext
    * `sudo apt install poppler-utils`
    * `less myfile.pdf`

* concat
  * [askUbuntu](https://stackoverflow.com/questions/2507766/merge-convert-multiple-pdf-files-into-one-pdf)  
  Warning! using `pdfunite` or `pdfjam` brakes hyperlinks, unsure with gs(ghostscript), ok with pdftk

    ``` bash
    gs -q -sPAPERSIZE=letter -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=output.pdf file1.pdf file2.pdf file3.pdf
    ```


QR CODE
==========
		qrencode -o /tmp/qrcode.png (Your text here)
		display /tmp/qrcode.png



CHANGE SHELL
============
		chsh -s `which zsh`
		sudo reboot



DISK ANALYSIS
=============
Home directory
		ncdu

specific directory
		ncdu -x /home/s03311251/Downloads



UPDATE FONT CACHE
=================
		sudo fc-cache -fv



OPENOCD
==========
(Source)[https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Programming-an-STM32F103XXX-with-a-generic-%22ST-Link-V2%22-programmer-from-Linux]
(Source)[https://balau82.wordpress.com/2013/08/14/flashing-the-stm32-p152-board-with-openocd/]

		openocd -f ~/Software/openocd-0.10.0/tcl/board/stm32f1.cfg
		telnet localhost 4444

Flash
		init
		reset init (This allow work in high speed mode)
		halt
		flash write_image erase ch.bin 0x08000000
		reset run
	Exit with Ctrl+Shift+], then Ctrl+D

Dump
		reset halt
		dump_image dump.bin 0x08000000 0x1ffff

Add in stm32f1_flash.cfg, then no need telnet



SHARE MEDIA WITH SMART TV (DLMA)
================================
Install miniDLNA
		sudo apt install minidlna

Edit config
		sudo pluma /etc/minidlna.conf
Content:
	inotify=yes
	media_dir=/home/user/Videos
	friendly_name=UbuntuDLNA

Restart miniDLNA and rebuild file list
		sudo service minidlna restart
		sudo service minidlna force-reload

Edit directory permission
???Which one would work???
		chmod o+rx-w mydir/
		sudo chgrp minidlna mkdir/

Stop from antostart if you want
		sudo update-rc.d minidlna disable



BE A SUPERUSER
==============
		su
won't work in Debian, therefore need
		sudo -i



ADD .so DYNAMIC LIBRARY PATH
============================
		export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/my_path



CRONTAB
==========
[vbird](http://linux.vbird.org/linux_basic/0430cron.php#whatiscron_type)
		crontab -e

3:00am and 6:00am
    0 3,6 * * * command

3:00am to 6:00am
    0 3-6 * * * command

Every 5 minutes
    */5 * * * * command

0, 5, 10, 15, 20, 25, 30
    0-30/5 * * * * command

At boot
	@reboot command



ASCENDING NUMBERS
=================
		echo {1..10}
1 2 3 4 5 6 7 8 9 10



SEPARATED MOUSE SPEED
=====================
[Source](https://askubuntu.com/questions/766309/how-to-change-mouse-dpi)
        xinput --list --short
        xinput --list-props "PixArt USB Optical Mouse"
        xinput --set-prop "PixArt USB Optical Mouse" "libinput Accel Speed" -0.2
ranges from -1 to 1, the higher the faster



ZFS
==========
(Setup a ZFS storage pool)[https://tutorials.ubuntu.com/tutorial/setup-zfs-storage-pool]
(How To Use ZFS on Linux for Your Home Directory)[https://scottlinux.com/2015/12/22/how-to-use-zfs-on-linux-for-your-home-directory/]

Create pool
		sudo zpool create my-pool mirror /dev/sda /dev/sdb
with mount point
		sudo zpool create -m /home my-pool mirror /dev/sda /dev/sdb

Create dataset
		sudo zfs create my-pool/home
Set mount point
		sudo zfs set mountpoint=/home my-pool/home
		sudo zfs mount my-pool/home


## import zpool from other system
list
		zpool import
import
		zpool import <pool_name>



NO-OP, DO NOTHING
=================
		:



PIP
==========
## Find package location
		pip show pytube



BATTERY
==========
[Source](https://www.ostechnix.com/how-to-check-laptop-battery-status-in-terminal-in-linux/)
		upower -i `upower -e | grep 'BAT'`





UNISON
==========
[Source](https://www.howtoforge.com/tutorial/unison-file-sync-between-two-servers-on-debian-jessie/)

* put preference in ~/.unison/default.prf, then can run directly:
  * `unison`

* if command not the same other the other clients, run with:
  * `unison -servercmd unison-jz.unison`

* Problem: Permission denied [opendir(/home/s03311251/.unison)]
  * reason: the directories are not in either of the machine, try to `rsync` them first for the first time

default.prf:
# Roots of the synchronization
root = /home/s03311251
root = ssh://192.168.0.200//home/s03311251

# Paths to synchronize
path = Arduino
path = Desktop/Favourite Websites
path = Desktop/Problems.md
path = Desktop/Scripts.md
path = Desktop/Vocab
path = Desktop/ღ♨☎❀.txt
path = Desktop/倉頡
path = Documents
path = Games
path = Music
#path = Pictures
#path = Software
path = tpacpi
path = .unison/default.prf

# Some regexps specifying names and paths to ignore
#ignore = Path stats    ## ignores /var/www/stats
#ignore = Path stats/*  ## ignores /var/www/stats/*
#ignore = Path */stats  ## ignores /var/www/somedir/stats, but not /var/www/a/b/c/stats
#ignore = Name *stats   ## ignores all files/directories that end with "stats"
#ignore = Name stats*   ## ignores all files/directories that begin with "stats"
#ignore = Name *.tmp    ## ignores all files with the extension .tmp
ignore = Path Documents/回憶

#          When set to true, this flag causes the user interface to skip
#          asking for confirmations on non-conflicting changes. (More
#          precisely, when the user interface is done setting the
#          propagation direction for one entry and is about to move to the
#          next, it will skip over all non-conflicting entries and go
#          directly to the next conflict.)
auto=true

#          When this is set to true, the user interface will ask no
#          questions at all. Non-conflicting changes will be propagated;
#          conflicts will be skipped.
batch=false

#          !When this is set to true, Unison will request an extra
#          confirmation if it appears that the entire replica has been
#          deleted, before propagating the change. If the batch flag is
#          also set, synchronization will be aborted. When the path
#          preference is used, the same confirmation will be requested for
#          top-level paths. (At the moment, this flag only affects the
#          text user interface.) See also the mountpoint preference.
confirmbigdel=true

#          When this preference is set to true, Unison will use the
#          modification time and length of a file as a `pseudo inode
#          number' when scanning replicas for updates, instead of reading
#          the full contents of every file. Under Windows, this may cause
#          Unison to miss propagating an update if the modification time
#          and length of the file are both unchanged by the update.
#          However, Unison will never overwrite such an update with a
#          change from the other replica, since it always does a safe
#          check for updates just before propagating a change. Thus, it is
#          reasonable to use this switch under Windows most of the time
#          and occasionally run Unison once with fastcheck set to false,
#          if you are worried that Unison may have overlooked an update.
#          The default value of the preference is auto, which causes
#          Unison to use fast checking on Unix replicas (where it is safe)
#          and slow checking on Windows replicas. For backward
#          compatibility, yes, no, and default can be used in place of
#          true, false, and auto. See the section "Fast Checking" for more
#          information.
fastcheck=true

#          When this flag is set to true, the group attributes of the
#          files are synchronized. Whether the group names or the group
#          identifiers are synchronizeddepends on the preference numerids.
group=true

#          When this flag is set to true, the owner attributes of the
#          files are synchronized. Whether the owner names or the owner
#          identifiers are synchronizeddepends on the preference
#          extttnumerids.
owner=true

#          Including the preference -prefer root causes Unison always to
#          resolve conflicts in favor of root, rather than asking for
#          guidance from the user. (The syntax of root is the same as for
#          the root preference, plus the special values newer and older.)
#          This preference is overridden by the preferpartial preference.
#          This preference should be used only if you are sure you know
#          what you are doing!
#prefer=newer

#          When this preference is set to true, the textual user interface
#          will print nothing at all, except in the case of errors.
#          Setting silent to true automatically sets the batch preference
#          to true.
silent=false

#          When this flag is set to true, file modification times (but not
#          directory modtimes) are propagated.
times=true



RSNAPSHOT
==========
[ArchWiki](https://wiki.archlinux.org/index.php/Rsnapshot)
In `/etc/rsnapshot.conf`:

...
snapshot_root	/home/s03311251/Yggdrasil_F/
...
retain	monthly	12
...
backup	/home/s03311251/Desktop/	.


Run
		sudo mount /dev/sdd5 /home/s03311251/Yggdrasil_F
		sudo rsnapshot monthly



TRANSMISSION DAEMON
===================
		sudo apt install transmission-deamon

# Edit username
[StackExchange](https://superuser.com/questions/113649/how-do-you-set-a-password-for-transmission-daemon-the-bittorrent-client-server)

		sudo /etc/init.d/transmission-daemon stop
In /etc/transmission-deamon/settings.json, edit `download-dir`, `incomplete-dir`, `rpc-username`, `rps-password` (In ""), `rpc-whitelist`, `umask` (See # Permission)
		sudo /etc/init.d/transmission-daemon start

# Permission
[StackExchange](https://askubuntu.com/questions/221081/permission-denied-when-downloading-with-transmission-deamon)
		sudo usermod -a -G debian-transmission s03311251 
		sudo chgrp debian-transmission ~/Downloads 
		sudo chmod 770 ~/Downloads 
		sudo /etc/init.d/transmission-daemon stop
In /etc/transmission-daemon/settings.json:
"umask": 2
		sudo /etc/init.d/transmission-daemon start

# Create torrent file
		transmission-create -t http://ehtracker.org/626250/announce "~/myfolder" -c "No comment" -o mytorrent.torrent

# List
		transmission-remote -n "username:password" -l

# Add
		transmission-remote -n "username:password" -C -w ~/Downloads/.internet -a "mytorrent.torrent"

-C	Don't store incomplete torrents in a different directory
-w	Download directory
-a	Add



MPLAYER
==========
# speed up
[ and ]

# speed up without changing pitch:
		mplayer -af scaletempo

# VCD
play Track 4
		mplayer vcd://4


CURL SPLIT DOWNLOAD
===================

[maketecheasier](https://www.maketecheasier.com/split-download-large-file-curl/)
	curl --range 1-999999 http://myurl.com -o test.zip.part1
	curl --range 1000000-1999999 http://myurl.com -o test.zip.part2
	curl --range 2000000- http://myurl.com -o test.zip.part3
	cat test.zip.part? > test.zip



EYE OF MATE STOP ZOOM WHEN SCROLL
=================================
		gsettings set org.mate.eom.view scroll-wheel-zoom false



Keyboard/Mouse click
====================
		sleep 2;xdotool mousedown 1;xdotool keydown w



INSTALL ADOBE FLASH (PPAPI)
===========================
[website for students](https://websiteforstudents.com/install-adobe-flash-player-on-ubuntu-18-04-lts-beta-desktop/)
		sudo add-apt-repository "deb http://archive.canonical.com/ $(lsb_release -sc) partner"
		sudo apt update
		sudo apt install adobe-flashplugin browser-plugin-freshplayer-pepperflash

* Arch
  * `sudo pacman -Syu flashplugin`

UDEV
==========
monitor
		udevadm monitor --environment --udev

show attributes
		udevadm info -a -p $(udevadm info -q path -n /dev/video2)



ANDROID SIMULATE SWIPE
======================
check if attached
		adb devices
click
		adb shell input tap x y
swipe
		adb shell input swipe x1 y1 x2 y2
			
Code
==========

* `code-oss` (in Arch repo) used open-vsx instead of Microsoft marketplace
  * <https://github.com/VSCodium/vscodium/blob/master/DOCS.md#extensions-marketplace>
  * <https://wiki.archlinux.org/index.php/Visual_Studio_Code>
  * fix: in `https://wiki.archlinux.org/index.php/Visual_Studio_Code`, replace the lines for `extensionsGallery` with:
  ``` json
  	"extensionsGallery": {
  		"serviceUrl": https://marketplace.visualstudio.com/_apis/public/gallery",
  		"itemUrl": "https://marketplace.visualstudio.com/items"
  	},
  ```

## KVM

* Install
  * <https://linuxhint.com/install_configure_kvm_archlinux/>
  1. `sudo pacman -S virt-manager qemu vde2 ebtables dnsmasq bridge-utils openbsd-netcat`
  2. `sudo systemctl enable libvirtd.service`
  3. In `/etc/libvirt/libvirtd.conf`, modify the lines as below:
    * `unix_sock_group = "libvirt"`
    * `unix_sock_rw_perms = "0770"`
  4. `sudo usermod -a -G libvirt $(whoami)`
  5. `newgrp libvirt`
  6. `sudo systemctl restart libvirtd.service`

* Network
  * `Requested operation is not valid: network 'default' is not active`
    * <https://blog.programster.org/kvm-missing-default-network>
    * `sudo virsh net-start default`
  * For Windows XP guest:
    * in NIC, try different `Device model` (e.g. rtl8139)

## Samba

* Install
  1. `sudo pacman -S samba`
  2. configure `/etc/samba/smb.conf`
  3. firewall:
    * In Arch Linux, need to write `/etc/ufw/applications.d/samba` by yourself:
      ``` plaintext
      [Samba]
      title=LanManager-like file and printer server for Unix
      description=The Samba software suite is a collection of programs that implements the SMB/CIFS protocol for unix systems, allowing you to serve files and printers to Windows, NT, OS/2 and DOS clients. This protocol is sometimes also referred to as the LanManager or NetBIOS protocol.
      ports=137,138/udp|139,445/tcp
      ```
    * `sudo ufw app update Samba` and `sudo ufw allow Samba`
  4. add user: `sudo smbpasswd -a s03311251`
  5. `sudo systemctl start smb.service`
  6. `sudo groupadd -r sambashare`
  7. `sudo chown s03311251:sambashare ~/Public` & `sudo chmod 1770 ~/Public` & `sudo gpasswd sambashare -a s03311251`
  8. `sudo systemctl restart smb.service` & `sudo systemctl restart nmb.service`
  
* enable SMBv1
  * <https://bbs.archlinux.org/viewtopic.php?id=231870>
  * in `/etc/samba/smb.conf` under `[global]`, add:
    * `client min protocol = NT1`
      * `NT1` for SMBv1, `SMB2` / `SMB3` for SMBv2/3

## Keyboard Input

### gcin

* <http://watchtvforfun.blogspot.com/2019/03/manjaro-linux-gcin.html>

1. ` sudo pacman -S gcin anthy`
2. in `~/.xprofile`, append:

   ``` plaintext
   #gcin
   export GTK_IM_MODULE=gcin
   export QT_IM_MODULE=gcin
   export LC_CTYPE=zh_TW.UTF-8
   export XMODIFIERS="@im=gcin"
   gcin &
   ```
3. `sudo gtk-query-immodules-2.0 --update-cache` & `sudo gtk-query-immodules-3.0 --update-cache`
4. reboot

## Network

### Virtual LAN

#### hamachi

* <https://wiki.archlinux.org/index.php/Hamachi>

1. if service not started: `sudo systemctl start logmein-hamachi.service`
2. `sudo hamachi login`
3. `sudo hamachi set-nick s03311251`
4. `sudo hamachi do-join "minecraft kate leung 2"`
5. `sudo hamachi go-online "minecraft kate leung 2"`
6. `sudo hamachi list`

#### Zerotier

* <https://wiki.archlinux.org/index.php/ZeroTier>

1. `sudo pacman -S zerotier-one`
2. `sudo systemctl start zerotier-one.service`
3. `sudo zerotier-cli join 17d709436c7648a3`
4. need to be authorized by network owner

* `sudo zerotier-cli info`
* `sudo zerotier-cli listnetworks`
* `sudo zerotier-cli listpeers`
