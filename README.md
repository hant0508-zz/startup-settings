Language: **[Русский](/README.rus.md)|English**

# Startup Settings

There is no handy tool to control startup in GNOME 3. To add a custom command to
startup you have to create file `~/.config/autostart/file.desktop` manually. This
simple program written in C++ and GTK 3 provides user friendly graphical interface for
startup managing. The program is designed especially for GNOME 3, however it cam also be
used in any other desktop environment.

### Installation

- Installing dependencies <br />
Debian/Ubuntu: `sudo apt-get install g++ make git libgtk-3-dev` <br />
Arch/Manjaro x32: `sudo pacman -S gcc git make gtk3` <br />
Arch/Manjaro x64: `sudo pacman -S gcc-multilib git make gtk3` <br />
- Building <br />
`git clone https://github.com/hant0508/startup-settings.git` <br />
`cd startup-settings` <br />
`make`
- Installing application <br />
`sudo make install`

To save the disk space, you can delete all the downloaded files and dependencies after the installation.

### Usage

After the installation you can find the program in application menu or run
`strartup-settings` in terminal.

Enter startup command into the `Command` field. It can be:
- full path to file: `/usr/bin/file.sh`
- relative path to file in your your home directory: `scripts/file.sh`
- command from [$PATH](https://en.wikipedia.org/wiki/PATH_(variable)): `firefox`

Depending on the window manager, you can also use drag-and-drop. GNOME 3 allow
even drag and drop files.

### Screenshots

![img](https://raw.githubusercontent.com/hant0508/tmp/master/startup-settings/gif 1.gif) | ![img](https://raw.githubusercontent.com/hant0508/tmp/master/startup-settings/gif 2.gif)
:---:|:---:
Usage on GNOME 3 | Drag and drop on GNOME 3


![alt-text](https://raw.githubusercontent.com/hant0508/tmp/master/startup-settings/kde.png "KDE 5") | ![alt-text](https://raw.githubusercontent.com/hant0508/tmp/master/startup-settings/cinnamon.png "Cinnamon 3") |  ![alt-text](https://raw.githubusercontent.com/hant0508/tmp/master/startup-settings/xfce4.png "XFCE 4")
:-------------------------:|:-------------------------:|:-------------------------:
KDE 5                      | Cinnamon 3                | XFCE 4          

### Feedback

If you have any problems with the application, [open an
issue](https://github.com/hant0508/startup-settings/issues/new). Write me [at
email](mailto:hant0508@gmail.com?subject=GitHub issue | Filters), if you have no
GitHub account.
