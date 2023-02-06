# Changelog

## [0.7.0](https://github.com/CborgDB/cborg/compare/v0.6.0...v0.7.0) (2023-02-06)


### Features

* **cbor:** add encode array start, indef and break ([85b0ebc](https://github.com/CborgDB/cborg/commit/85b0ebc277884abe054831afbd5ab3087389ae37))
* **cbor:** add encode bytestring ([c66a0a6](https://github.com/CborgDB/cborg/commit/c66a0a6e92ce1fdd438261f3aaee5d9bde725b9f))
* **cbor:** add encode false, true, undefined and break ([69b9143](https://github.com/CborgDB/cborg/commit/69b91435648846120aea8fab7718784b0337fec2))
* **cbor:** add encode map start, indef and break ([254d650](https://github.com/CborgDB/cborg/commit/254d650b7f266825e5a30f44c7b91e14ba3af8b3))
* **cbor:** add encode string indef and rename def ([f1282a2](https://github.com/CborgDB/cborg/commit/f1282a25c501147a93ff079069eba464d91a3992))
* **cbor:** cbor_get_string function ([b38d864](https://github.com/CborgDB/cborg/commit/b38d8643fc075b2f4081c55d2540f4d5a8afb423))


### Bug Fixes

* include for bsd systems ([dec9b01](https://github.com/CborgDB/cborg/commit/dec9b01856360c05377e3e2eabeb10a425934f93))

## [0.6.0](https://github.com/CborgDB/cborg/compare/v0.5.0...v0.6.0) (2022-11-01)


### Features

* **server:** allow multiple client on BSD systems using kqueue ([#49](https://github.com/CborgDB/cborg/issues/49)) ([bfd85b9](https://github.com/CborgDB/cborg/commit/bfd85b9c92efef1419257bd9c704a8ebf8fdc8d6))


### Bug Fixes

* **ops:** update operations reading new item was wrong ([4169f01](https://github.com/CborgDB/cborg/commit/4169f01df3caa627d26e7a70e2a052a809bf5f3a))
* **server:** close client socket on BSD systems ([b16fe5d](https://github.com/CborgDB/cborg/commit/b16fe5d9089c9b6cc2d64234aaa55a7cb0296a6a))
* **server:** createCollection returns wrong message ([26c8a1f](https://github.com/CborgDB/cborg/commit/26c8a1f6ed6c528d5593b72586a4e9951543b756))

## [0.5.0](https://github.com/CborgDB/cborg/compare/v0.4.1...v0.5.0) (2022-10-02)


### Features

* add Dockerfile, build and push automatically ([#42](https://github.com/CborgDB/cborg/issues/42)) ([bf04c2f](https://github.com/CborgDB/cborg/commit/bf04c2f287ce569b31cded69e56b9a06f0ac5fc3))

## [0.4.1](https://github.com/CborgDB/cborg/compare/v0.4.0...v0.4.1) (2022-10-01)


### Bug Fixes

* version number ([#39](https://github.com/CborgDB/cborg/issues/39)) ([7457823](https://github.com/CborgDB/cborg/commit/745782345c810d04b2a6bb5f3a4fbc52a5427901))

## [0.4.0](https://github.com/CborgDB/cborg/compare/v0.3.0...v0.4.0) (2022-10-01)


### Features

* add opts(host,port) to cborg server and cli ([#31](https://github.com/CborgDB/cborg/issues/31)) ([9631899](https://github.com/CborgDB/cborg/commit/96318990460efc3c18ded547163c90abf92a9ea1))
* **release-please:** add first configuration ([#36](https://github.com/CborgDB/cborg/issues/36)) ([33bd503](https://github.com/CborgDB/cborg/commit/33bd503f0f6b83f603f221ea7dddc419b9e4fafc))


### Bug Fixes

* **cbor:** change return type cbor int ([#28](https://github.com/CborgDB/cborg/issues/28)) ([13ccba3](https://github.com/CborgDB/cborg/commit/13ccba35465ac161e1ee53127f08fac12ff1a6ba))
* **cbor:** change return type of cbor encoding functions ([#29](https://github.com/CborgDB/cborg/issues/29)) ([a762489](https://github.com/CborgDB/cborg/commit/a7624891409955a1ed7453f1a73d3669a9700f31))
* **cli:** host required argument ([#33](https://github.com/CborgDB/cborg/issues/33)) ([83966be](https://github.com/CborgDB/cborg/commit/83966be46d164835c15704f1a2316f104aa0a6be))
