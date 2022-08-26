all: build

build:
	docker buildx build -o . .

run-all: run-js run-wasm run-wasm-simd run-wasm-simd-intrin run-wasm-O3 run-wasm-O3-simd run-wasm-O3-simd-intrin run-c run-c-O3

run-js:
	node mul_mats.js

run-wasm:
	node dist/mul_mats-wasm.js

run-wasm-simd:
	node dist/mul_mats-wasm-simd.js

run-wasm-simd-intrin:
	node dist/mul_mats-wasm-simd-intrin.js

run-wasm-O3:
	node dist/mul_mats-wasm-O3.js

run-wasm-O3-simd:
	node dist/mul_mats-wasm-O3-simd.js

run-wasm-O3-simd-intrin:
	node dist/mul_mats-wasm-O3-simd-intrin.js

run-c:
	./dist/mul_mats

run-c-O3:
	./dist/mul_mats-O3
