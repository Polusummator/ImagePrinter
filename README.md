# ImagePrinter

Terminal image renderer with alpha-channel support

## Dependencies

* [ImageMagick](https://imagemagick.org/index.php) (tested with 6.9.12-98 & 7.1.1-43)
* [xtermcontrol](https://thrysoee.dk/xtermcontrol/) & xterm-compatible terminal (for full alpha-channel support)

<details>
<summary><b>Debian-based</b></summary>
  
```
sudo apt install imagemagick libmagick++-dev xtermcontrol
```
</details>

<details>
<summary><b>Arch-based</b></summary>
  
```
sudo pacman -S imagemagick
git clone https://aur.archlinux.org/xtermcontrol.git
cd xtermcontrol
makepkg -si
cd ..
rm -rf xtermcontrol
```
</details>

<details>
<summary><b>RHEL-based</b></summary>

```
sudo dnf install ImageMagick-c++-devel
wget https://thrysoee.dk/xtermcontrol/xtermcontrol-3.10.tar.gz
tar zxf wget xtermcontrol-3.10.tar.gz
cd xtermcontrol-3.10
./configure && make install
cd ..
rm -rf xtermcontrol-3.10 && rm -f xtermcontrol-3.10.tar.gz
```
</details>

## Building

```
cmake .
make
```

## Usage

```
./ImagePrinter <file>
```
