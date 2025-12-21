## Desktop create

Reference `code.desktop`

```sh
cd /usr/share/applications
cat code.desktop

[Desktop Entry]
Name=Visual Studio Code
Comment=Code Editing. Redefined.
GenericName=Text Editor
Exec=/usr/share/code/code %F
Icon=vscode
Type=Application
StartupNotify=false
StartupWMClass=Code
Categories=TextEditor;Development;IDE;
MimeType=application/x-code-workspace;
Actions=new-empty-window;
Keywords=vscode;
```

### Clion related
```sh
cd /usr/share/applications
cat > clion.desktop << "EOF"
[Desktop Entry]
Name=CLion
Comment=CLion IDE
Exec=/home/costa/Downloads/clion-2025.3.1/bin/clion.sh
Icon=/home/costa/Downloads/clion-2025.3.1/bin/clion.png
Terminal=false
Type=Application
Categories=Development;IDE;
StartupWMClass=jetbrains-clion
EOF

sudo chmod +x clion.desktop
cp /usr/share/applications/clion.desktop ~/Desktop/
```

### [clash related](https://mymonocloud.com/)

```sh
cd /usr/share/applications/
sudo cat > clash.desktop << "EOF"
[Desktop Entry]
Name=Clash
Comment=Clash from mymonocloud.com
Exec="/home/costa/Downloads/Clash for Windows-0.20.39-x64-linux/cfw"
Icon="/home/costa/Downloads/Clash for Windows-0.20.39-x64-linux/cfw.png"
Terminal=false
Type=Application
Categories=Development;IDE;
StartupWMClass=Clash
EOF

sudo chmod +x clash.desktop
cp /usr/share/applications/clash.desktop ~/Desktop/
# right click clash.desktop in the desktop and click allow launch
```

![Network Proxy Manual Setting](imgs/image.png)

```txt
choose manual
HTTP Proxy:127.0.0.1, port: 7890
HTTPS Proxy:127.0.0.1, port: 7890
Socks Host:127.0.0.1, port: 7890
Ignore Hosts:localhost, 127.0.0.0/8, ::1
```

![Clash GUI](imgs/image-1.png)

## Chinese Language input
```sh
# Add IBus environment variables to bashrc
echo '
# IBus input method settings
export GTK_IM_MODULE=ibus
export QT_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export IBUS_ENABLE_SYNC_MODE=1' >> ~/.bashrc

# Source bashrc to apply immediately
source ~/.bashrc

sudo apt install ibus-libpinyin

ibus-setup
ps aux | grep ibus-daemon
ibus-daemon -drx
ibus engine libpinyin

# GNOME 桌面环境与 IBus 之间的配置冲突：
# GNOME 有自己的输入源管理机制​ (org.gnome.desktop.input-sources)
# IBus 也有自己的引擎管理机制​ (org.freedesktop.ibus.general)
# 当两者配置不一致时，GNOME 会覆盖 IBus 的配置
# 您之前只在 IBus 中配置了输入法，但 GNOME 的设置中没有，导致切换时被 GNOME 重置

# 1. 配置 GNOME 输入源（控制桌面环境级别的切换）
gsettings get org.gnome.desktop.input-sources sources
gsettings set org.gnome.desktop.input-sources sources "[('xkb', 'us'), ('ibus', 'libpinyin')]"

# 2. 配置 IBus 预加载引擎（确保 IBus 内部正确加载）
gsettings set org.freedesktop.ibus.general preload-engines "['xkb:us::eng', 'libpinyin']"

# 3. 设置切换快捷键（可选，通常默认是 Super+Space）
gsettings set org.gnome.desktop.wm.keybindings switch-input-source "['<Super>space']"
gsettings set org.gnome.desktop.wm.keybindings switch-input-source-backward "['<Shift><Super>space']"

ibus restart
```

```sh
# 检查 GNOME 输入源
echo "GNOME 输入源配置:"
gsettings get org.gnome.desktop.input-sources sources
echo -e "\n当前输入源索引:"
gsettings get org.gnome.desktop.input-sources current

# 检查 IBus 配置
echo -e "\nIBus 预加载引擎:"
gsettings get org.freedesktop.ibus.general preload-engines

# 检查快捷键
echo -e "\n切换输入源快捷键:"
gsettings get org.gnome.desktop.wm.keybindings switch-input-source
```

this one 

![alt text](imgs/image-2.png)






## flameshot

```sh
sudo apt-get install flameshot

flameshot gui
```
![alt text](imgs/image-3.png)


## cmake & google test

```sh
cat > main.cpp << "EOF"
#include <cstdio>
int main(int argc, char* argv[]) {
    printf("Hello world, argc[%d], argv[0]=%s\n", argc, argv[0]);
    return 0;
}
EOF


cat > CMakeLists.txt << "EOF"
cmake_minimum_required(VERSION 3.14)
project(newbie)
add_executable(newbie main.cpp)
EOF

cat > ".gitignore" << "EOF"
.vscode
build
img
third_party
EOF


cmake -S . -B ./build/
# for windows and MinGW Generator
# cmake -S . -B ./build/ -G "MinGW Makefiles"
cmake --build ./build
./build/${execuatableName}
```
### Clion Usgae

> Edit CMake Profiles 

Choose the build type, Generator, and build path

![CMake Profiles](imgs/image-4.png)

> Edit Configurations > CMake Applications > newbie/tester

Names newbie or tester depends on the executable defined in CMakeLists.txt

![newbie](imgs/image-5.png)

![tester](imgs/image-6.png)


## .gitusage

```sh
ssh-keygen -t ed25519 -C "hancosta@outlook.com"
cat ~/.ssh/id_ed25519.pub
git config --global user.email "hancosta@outlook.com"
git config --global user.name "hancosta"
git config -l

# work with github existed compository
git clone git@github.com:CostaHector/learning.git

# …or create a new repository on the command line
echo "# learning" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M master
git remote add origin git@github.com:CostaHector/learning.git
git push -u origin master

# …or push an existing repository from the command line
git remote add origin git@github.com:CostaHector/learning.git
git branch -M master
git push -u origin master
```


## Refactor googletest



