FROM ubuntu:22.04 as build

WORKDIR /cborgdb
COPY . .

RUN apt-get update \
    && apt-get -y upgrade \
    && apt-get -y install cmake gcc
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --config Release
RUN ctest --test-dir build

FROM ubuntu:22.04

WORKDIR /
COPY --from=build /cborgdb/build/cborg /cborgdb/cborg
COPY --from=build /cborgdb/build/cborg-cli /cborgdb/cborg-cli

CMD /cborgdb/cborg 
