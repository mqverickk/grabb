![](https://s6.imgcdn.dev/YPsoB2.png)
# Grabb
Grabb is a tools that allows you to grab any plugin you want using Modrinth API just from your terminal.

## Compile
Make sure you have installed [CMake](https://cmake.org) and [GCC](https://gcc.gnu.org), if not then install first:
```bash
$ sudo pacman -S base-devel
$ cd src/
$ make
```

## Usage
```bash
$ grabb -f luckperms
[ info ] Searching Modrinth for 'luckperms'...

 ID (Slug)                 | Name                           | Author
--------------------------------------------------------------------------------
 luckperms                 | LuckPerms                      | lucko
 clearlag++                | ClearLag++                     | fernsehheft
 lpc-chat                  | LPC Minimessage - Chat Format  | Ayont
 luckprefix                | LuckPrefix                     | ezTxmMC
 prefix-system             | Prefix System                  | 7AGAM
 axrankmenu                | AxRankMenu                     | ArtillexStudios
 universal-perms           | Universal Perms                | MattiDragon
 homeward-bound            | Homeward Bound                 | AdyTech99
 chat-formatter            | Chat Formatter                 | 7AGAM
 lprm                      | LPRM - LuckPerms Rank Maker    | Olafcio1
--------------------------------------------------------------------------------
[ info ] Found 10 plugins matching 'luckperms'.

$ grabb -p luckperms -v 1.21.8 -s paper
[ info ] Resolving version for 'luckperms' (v1.21.8, paper)...
[ info ] Downloading file: LuckPerms-Bukkit-5.5.17.jar
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100  1445k 100  1445k   0     0  2465k     0  --:--:-- --:--:-- --:--:--  2463k
[ success ] Saved as LuckPerms-Bukkit-5.5.17.jar
```

## Project Structure
```
grabb
├── README.md
└── src
    ├── download.c
    ├── grabb.h
    ├── logs.c
    ├── main.c
    ├── Makefile
    ├── network.c
    ├── search.c
    └── stats.c
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
This project is released under [MIT](https://choosealicense.com/licenses/mit/) license.
