



01
PART
大数打印
38.png
本题原始版本出自《剑指offer》，leetcode或许是因为自身原因，并没有很好的进行移植。当然，这道题本身也确实不太好移植，尤其是测试样例的构建，很容易把系统搞崩掉，所以一些测试样例处理成内存溢出，也是情有可原。

题目：输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

示例 1:

输入: n = 1 输出: [1,2,3,4,5,6,7,8,9]

 说明：

用返回一个整数列表来代替打印

n 为正整数








02
PART
简单解法
38.png
如果是第一次看到本题，应该是会想到👇👇👇的解法。

直接通过 Math.pow 函数，计算出最大的 n 位十进制数，通过遍历求解。因为过于简单，所以直接上代码：
 1//java
 2class Solution {
 3    public int[] printNumbers(int n) {
 4        int len = (int) Math.pow(10, n);
 5        int[] res = new int[len - 1];
 6        for (int i = 1; i < len; i++) {
 7            res[i - 1] = i;
 8        }
 9        return res;
10    }
11}


补一个c++版本的：



 1//c++
 2class Solution {
 3public:
 4    vector<int> printNumbers(int n) {
 5        vector<int> res;
 6        if (n == 0) return res;
 7        //打印到数组中
 8        for (int i=1,max=pow(10,n);i<max;i++)
 9        {
10            res.push_back(i);
11        }
12        return res;
13    }
14}; 


这种题解，应该不存在说有看不懂的。。。吧？（有的话，面壁思过！）

timg (1).gif
郑重申明（读我的文章必看）：

本系列所有教程都不会用到复杂的语言特性，大家无须担心没有学过相关语法，算法思想才是最重要的！

作为学术文章，虽然风格可以风趣，但严谨，我是认真的。本文所有代码均在leetcode进行过测试运行。


03
PART
面试官说话了
38.png
“不允许使用math.pow，请手动实现一下”，“恶毒”的面试官发问了。

不让使用 math.pow ， 那我们就不使用呗。根据上面的题解，我们已经把握到了关键，只要能找到 最大的 n 位十进制数，就可以解决问题。那我们就手动算一下：



 1//go
 2func printNumbers(n int) []int {
 3    res := []int{}
 4    l := 0
 5    for 0 < n {
 6        n--
 7        l = l*10+9
 8    }
 9    for i := 1; i < l+1; i++ {
10        res = append(res, i)
11    }
12    return res
13}




（看起来还不错～但我肯定不会告诉你这是因为go语言提交少的缘故！）




04
PART
面试官又说话了
38.png
“这道题目的名字叫做大数打印，如果阈值超出long类型，该怎么办呢？请手动实现一下！” 面试官总是可以想方设法为难咱们。（玩笑归玩笑，其实这个才是本题的核心）

到现在为止，本题才进入到关键环节。因为如果一个数很大，肯定没办法用单个变量类型进行表达。问题也发生了转化：如何使用其他的数据类型来模拟大数的表达？







这里先复习一下大数加法：在加法运算的时候假如有两个10000位数的两个数进行相加,那么用int、long、double型都装不下这么多位数，一般采用char数组来实现加法运算，解决精度的问题。说白了是啥意思，我们用 1234567 和 1234 来模拟一下：







取两个数位数大的一个作为数组长度

对两个数建立char数组，保存每一位上的值

对于位数小的数，高位补0。

同时创建sumArr，用来保存两数之和

考虑进位



当然，一般我们还使用一些比如 翻转存储计算 之类的技巧，这里就不说了，回头我会出一个单独的大数计算系列篇单独讲解。回到今天的题目。



对于本题，我们该如何模拟一个 “最大的n位十进制数” 呢？其实也是一样的，我们采用 char 数组进行存储。而我们每次递增1，相当于进行一次字符串相加的运算。但是这里额外要说明的一点是，我把题解恢复成了原题的要求：使用打印输出，而不是通过数组返回的形式。毕竟返回数组的形式只是 leetcode 为了兼容平台测试而改编的。这里我就直接给出从剑指offer改编的题解了（JAVA）：



 1//java
 2public void printNumbers(int n) {
 3        //声明字符数组,用来存放一个大数
 4        char[] number = new char[n];
 5        Arrays.fill(number, '0');
 6        while (!incrementNumber(number)) {
 7            saveNumber(number); //存储数值
 8        }
 9    }
10
11    private boolean incrementNumber(char[] number) {
12        //循环体退出标识
13        boolean isBreak = false;
14        //进位标识
15        int carryFlag = 0;
16        int l = number.length;
17        for (int i = l - 1; i >= 0; i--) {
18            //取第i位的数字转化位int
19            int nSum = number[i] - '0' + carryFlag;
20            if (i == l - 1) {
21                //最低位加1
22                ++nSum;
23            }
24            if (nSum >= 10) {
25                if (i == 0) {
26                    isBreak = true;
27                } else {
28                    //进位之后减10，并把进位标识设置为1
29                    nSum -= 10;
30                    carryFlag = 1;
31                    number[i] = (char) ('0' + nSum);
32                }
33            } else {
34                number[i] = (char) (nSum + '0');
35                break;
36            }
37        }
38        return isBreak;
39    }
40
41    private void saveNumber(char[] number) {
42        boolean isBegin0 = true;
43        for (char c : number) {
44            if (isBegin0 && c != '0') {
45                isBegin0 = false;
46            }
47            if (!isBegin0) {
48                // 到这里并没有继续往下实现一个存储数组的版本，是因为原题其实就是要求打印数值。
49                // 这道题目在leetcode上被改动成返回int数组的形式，也只是为了测试方便，
50                // 本身leetcode并没有提供对应的大数测试样例，也是担心其内存溢出。
51                // 总之大家知道本题的考察点所在就可以了。
52                System.out.print(c);
53            }
54        }
55        System.out.println();
56    }


上面的代码强调两点：

对最低位 nSum 的值递增（也就是字符串加1运算），当大于等于10时，我们把进位标识改为1，同时恢复对 nSum 减10（29-31）

通过判断首位是否进位来判断到达最大的n位数情况。比如 n=4，只有对 9999 加 1，才会对第一个字符进位。



同样，我也实验了一下，如果我硬性的把代码改成数组的形式，然后在leetcode测试用例中构造 n = 10，就会出现这个：



