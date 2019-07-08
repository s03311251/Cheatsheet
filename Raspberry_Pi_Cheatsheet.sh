##### Remote Desktop
# http://elinux.org/RPi_VNC_Screen_Sharing

##### Install
$ sudo apt-get install vino

##### Configure
$ sudo apt-get install dconf-editor
# search org.gnome.desktop.remote-access

#### Lightdm autostart
$ sudo nano /etc/xdg/autostart/vino-server.desktop

# Put to following in that file
[Desktop Entry]
Name=Desktop Sharing
Comment=GNOME Desktop Sharing Server
Exec=/usr/lib/vino/vino-server
Terminal=false
Type=Application
X-GNOME-Autostart-Phase=Applications
X-GNOME-AutoRestart=true
NoDisplay=true

#### Access remotely
$ sudo apt-get install xtightvncviewer



##### /usr/lib/chromium-browser/chromium-browser: symbol lookup error: /usr/lib/chromium-browser/chromium-browser: undefined symbol: mmal_vc_init_fd
sudo rpi-update
sudo reboot



##### Play mp4 videos
omxplayer -t 1 --font /usr/share/fonts/truetype/wqy/wqy-zenhei.ttc --align center -o hdmi 01.mp4 

####KEY BINDINGS
#       Key bindings to control omxplayer while playing:
#           1           decrease speed
#           2           increase speed
#           <           rewind
#           >           fast forward
#           z           show info
#           j           previous audio stream
#           k           next audio stream
#           i           previous chapter
#           o           next chapter
#           n           previous subtitle stream
#           m           next subtitle stream
#           s           toggle subtitles
#           w           show subtitles
#           x           hide subtitles
#           d           decrease subtitle delay (- 250 ms)
#           f           increase subtitle delay (+ 250 ms)
#           q           exit omxplayer
#           p / space   pause/resume
#           -           decrease volume
#           + / =       increase volume
#           left arrow  seek -30 seconds
#           right arrow seek +30 seconds
#           down arrow  seek -600 seconds
#           up arrow    seek +600 seconds



##### omxplayer.bin: SubtitleRenderer.cpp:133: SubtitleRenderer::load_glyph(SubtitleRenderer::InternalChar)::<lambda(FT_Face, VGFont, bool)>: Assertion `!vgGetError()' failed.

change /boot/config.txt
set
gpu_mem=128 (or higher)



##### Set up a Wi-Fi Access Point
$ sudo apt-get install hostapd dnsmasq

# hostapd: create AP
# dnsmasq: host DHCP and DNS



