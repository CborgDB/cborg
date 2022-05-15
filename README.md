# cborg

<p align="center">
  <img src='docs/media/cborgdb.png?raw=true' width='80%'>
</p>

---

CborgDB is 🚧 still under development 🚧 and will be a database management system.
The database will be developed in C language and the project is open source on 🐙 GitHub.

The purpose of CborgDB is to learn how existing database management systems work under the hood and maybe be able to do something different. Currently, CborgDB doesn't do anything interesting but you have the right to try it 😜.

## ⚙️ Build

```console
abenhlal@cborgdb:~$ git clone https://github.com/cborgdb/cborg.git
abenhlal@cborgdb:~$ cd cborg
abenhlal@cborgdb:~/cborg$ mkdir build
abenhlal@cborgdb:~/cborg$ cd build
abenhlal@cborgdb:~/cborg/build$ cmake ..
abenhlal@cborgdb:~/cborg/build$ make
```

## 🏡 Install

```console
abenhlal@cborgdb:~/cborg/build$ make install
```

## ✨ Usage

1) Version
```console
abenhlal@cborgdb:~/cborg/build$ ./cborg --version
CborgDB v0.2.0

Maintained by Adil Benhlal <a.benhlal@cborgdb.com>
```

2) Help

- long option
```console
abenhlal@cborgdb:~/cborg/build$ ./cborg --help
Usage:
    ./cborg [options]

Options:
    -h, --help    Display this help
    --version     Print the version of CborgDB
```

- short option
```console
abenhlal@cborgdb:~/cborg/build$ ./cborg -h
Usage:
    ./cborg [options]

Options:
    -h, --help    Display this help
    --version     Print the version of CborgDB
```

2) Run Cborg
```console
abenhlal@cborgdb:~/cborg/build$ ./cborg
CborgDB is running on port 30000.
```

3) In another terminal
```console
abenhlal@cborgdb:~$ telnet localhost 30000
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Welcome to CborgDB !
Connection closed by foreign host.
```

## 🚪🚶 Uninstall

```console
abenhlal@cborgdb:~/cborg/build$ make uninstall
```

## ✍️ Author

Made with ❤️ by Adil Benhlal
