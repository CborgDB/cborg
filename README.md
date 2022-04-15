# cborg

<p align="center">
  <img src='docs/media/cborgdb.png?raw=true' width='70%'>
</p>

---

CborgDB is 🚧 still under development 🚧 and will be a database management system.
The database will be developed in C language and the project is open source on 🐙 GitHub.

The purpose of CborgDB is to learn how existing database management systems work under the hood and maybe be able to do something different. Currently, CborgDB doesn't do anything interesting but you have the right to try it 😜.

## ⚙️ Build

```console
abenhlal@cborgdb:~$ git clone https://github.com/cborgdb/cborg.git
abenhlal@cborgdb:~$ cd cborg
abenhlal@cborgdb:~/cborg$ gcc -o cborg src/cborg.c
```

## ✨ Usage

1) Run Cborg
```console
abenhlal@cborgdb:~/cborg$ ./cborg
```

2) In another terminal
```console
abenhlal@cborgdb:~$ telnet localhost 30000
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Welcome to CborgDB !
Connection closed by foreign host.
```

## ✍️ Author

Made with ❤️ by Adil Benhlal
