#ifndef _MYBITSET_H_
#define _MYBITSET_H_
#include <bitset>
    #include <iostream>

template <int SIZE>
class Bitset {
  public:
	static const int len = (SIZE + 63) / 64;
	unsigned long long bits[len];

	void set() {
		memset(bits, -1, sizeof bits);
	}
	
	void reset() {
		memset(bits, 0, sizeof bits);
	}
	
	void set(int i) {
		bits[i >> 6] |= 1LL << (i & 63);
	}
	
	void reset(int i) {
		bits[i >> 6] &= ~(1LL << (i & 63));
	}
	
    int count() const {
        int cnt = 0;
        for (int i = 0; i < len; ++i)
            cnt += __builtin_popcountll(bits[i]);
        return cnt;
    }
    
    bool none() const {
        for (int i = 0; i < len; ++i)
            if (bits[i]) return false;
        return true;
    }
	
	void operator &= (const Bitset<SIZE> &ano) {
		for (int i = 0; i < len; ++i)
			bits[i] &= ano.bits[i];		
	}
	
	friend Bitset<SIZE> operator & (const Bitset<SIZE> &lhs, const Bitset<SIZE> &rhs) {
		Bitset<SIZE> res;
		for (int i = 0; i < len; ++i)
			res.bits[i] = lhs.bits[i] & rhs.bits[i];
		return res;
	}

    bool operator [] (const int &idx) const {
        return (bits[idx >> 6] >> (idx & 63)) & 1;
    }
};

#endif