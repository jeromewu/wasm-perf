const mulMats = (out, in_a, in_b, n) => {
	for (let i = 0; i < n; i++) {
		for (let j = 0; j < n; j++) {
			out.arr[i*n+j] = 0;
			for (let k = 0; k < n; k++) {
				out.arr[i*n+j] += in_a.arr[i*n+k] * in_b.arr[j*n+k];
			}
		}
	}
};

const n = 64;
const size = n*n;
const it = 10000;
const out = { arr: new Array(size) };
const in_a = { arr: new Array(size) };
const in_b = { arr: new Array(size) };

// transpose
for (let i = 0; i < n; i++) {
	for (let j = 0; j < i; j++) {
		let aux = in_b[i*n+j];
		in_b[i*n+j] = in_b[j*n+i];
		in_b[j*n+i] = aux;
	}
}

console.time("multiply matrixs");
for (let i = 0; i < it; i++) {
	mulMats(out, in_a, in_b, n);
}
console.timeEnd("multiply matrixs");
