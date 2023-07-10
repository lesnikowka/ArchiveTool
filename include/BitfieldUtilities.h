#pragma once



template<class T>
T getValueFromBitField(const TBitField& tf, size_t start) {
	size_t bitsize = sizeof(T) * 8;
	T val = 0;

	int deg = bitsize - 1;
	for (size_t i = start; i < start + bitsize; i++) {
		if (tf.GetBit(i)) {
			val += (T)1 << deg;
		}
		deg--;
	}

	return val;
}

template<class T>
void writeValueInBitField(TBitField& tf, const T& val, size_t start) {
	size_t bitsize = sizeof(T) * 8;

	for (int i = bitsize - 1; i >= 0; i--) {
		if ((val << bitsize - i - 1) >> bitsize - 1) {
			tf.SetBit(start + bitsize - i - 1);
		}
	}
}