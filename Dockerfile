FROM emscripten/emsdk:3.1.18 AS wasm-builder
COPY *.c /src
RUN mkdir -p /src/dist
RUN emcc -o dist/mul_mats-wasm.js mul_mats.c
RUN emcc -o dist/mul_mats-wasm-simd.js -msimd128 mul_mats.c
RUN emcc -o dist/mul_mats_intrin-wasm-simd.js -msimd128 mul_mats_intrin.c
RUN emcc -o dist/mul_mats-wasm-O3.js -O3 mul_mats.c
RUN emcc -o dist/mul_mats-wasm-O3-simd.js -O3 -msimd128 mul_mats.c
RUN emcc -o dist/mul_mats_intrin-wasm-O3-simd.js -O3 -msimd128 mul_mats_intrin.c

FROM gcc:12.2.0 AS gcc-builder
RUN mkdir -p /src/dist
COPY *.c /src
WORKDIR /src
RUN gcc -o dist/mul_mats mul_mats.c
RUN gcc -o dist/mul_mats-O3 -O3 mul_mats.c

FROM scratch AS exportor
COPY --from=wasm-builder /src/dist /dist
COPY --from=gcc-builder /src/dist /dist
