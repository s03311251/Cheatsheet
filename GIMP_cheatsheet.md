# GIMP Cheatsheet

* remove unwanted object from background
  * [Source](http://templatetoaster.com/tutorials/gimp-resynthesizer-plugin/)

  1. Install resynthesizer plugin
     * AUR
       * <https://aur.archlinux.org/python2-gimp.git>
         * necessary for version >= 2.10, because official Arch package dropped Python2, and GIMP switched to its own Python2 interpreter
       * <https://aur.archlinux.org/gimp-plugin-resynthesizer.git>
  2. Filters -> Enchance -> Heal Selection

* text outline
  * <https://itsfoss.com/gimp-text-outline/>
  1. right click the text -> `Path from text`
  2. Add layer
  3. `Select` -> `From Path` -> `Grow` -> `Fill`
