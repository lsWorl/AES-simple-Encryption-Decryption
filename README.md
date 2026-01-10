运行该程序命令：gcc -g main.c common.c AESEncryption.c -o main.exe 2>&1  （采用GCC编译器，会产生main.exe文件）
然后再运行：main.exe

对应论文地址为https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
状态向量采用Appendix B中的测试向量
代码中encrypt和decrypt为论文复现
## 任意字长的明文加密说明
填充采用PKCS#7，填充规则为：（）
    如果数据长度正好是块大小的整数倍 → 补一个完整的块，这个块的每个字节都等于块大小的值。
    如果数据长度不足一块 → 补上需要的字节数，每个补上的字节值都等于需要补的字节数。

分组模式采用CBC，每个明文块先与前一密文块异或，再用密钥加密，具有良好的扩散性（ECB为直接为每个明文块加密，容易被分析，故采用CBC,因为只用于学习原理，IV向量只通过简单的rand函数实现）
