package main

import (
	"fmt"
	"strings"
)

//映射值
const primeRK = 16777619

// hashStr returns the hash and the appropriate multiplicative
// factor for use in Rabin-Karp algorithm.
func hashStr(sep string) (uint32, uint32) {
	hash := uint32(0)
	//计算查找字符串的hash
	for i := 0; i < len(sep); i++ {
		hash = hash*primeRK + uint32(sep[i])
	}

	//计算每次减去最高位的乘数因子
	// 计算 sep 最高位 + 1 位的权值 pow（乘数因子）
	// 也就是上面说的 M 的 n 次方
	// 这里通过遍历 len(sep) 的二进制位来计算，减少计算次数
	var pow, sq uint32 = 1, primeRK
	for i := len(sep); i > 0; i >>= 1 {
		if i&1 != 0 {
			pow *= sq
		}
		sq *= sq
	}
	return hash, pow
}

func indexRabinKarp(s, substr string) int {
	// Rabin-Karp search
	//对查找字符串计算hash
	hashss, pow := hashStr(substr)

	//得到查找字符串的长度
	n := len(substr)

	//计算s的前n个字符是否匹配
	var h uint32
	for i := 0; i < n; i++ {
		h = h*primeRK + uint32(s[i])
	}
	//hash相等，比较字符串
	if h == hashss && s[:n] == substr {
		return 0
	}
	//第一个字符串不匹配
	for i := n; i < len(s); {
		h *= primeRK
		h += uint32(s[i])
		//减去前一个字符的hash计算值
		h -= pow * uint32(s[i-n])
		i++
		//首先比较hash,然后比较字符串
		if h == hashss && s[i-n:i] == substr {
			return i - n
		}
	}
	return -1

}
func main() {
	fmt.Println("vim-go")
	str := "abcdefgh"
	sub := "fg"
	index := strings.Index(str, sub)
	fmt.Println("index is ", index)
	index = indexRabinKarp(str, sub)
	index = indexRabinKarp(str, sub)
	fmt.Println("index is ", index)
}
