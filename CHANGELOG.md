# Changelog

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
