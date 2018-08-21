[说明]
	用动态规划，求解三角形的最大路径问题;
[动态规划算法]
	动态规划的定义：
	dynamic programming is a method for solving a complex problem
	by breaking it down into a collection of simpler subproblems.
	动态规划操作的核心是:拆分问题.在拆分问题的基础上，找出状态转移方程．
	在算法原理上是：利用空间换取时间，即记录每一步的操作的结果，用于下
	一步的计算，即计算结果的存储和利用．
[本例说明]
　　本例求解三角形的最大路径．对问题拆分为求解叶子节点的最大值和求解节点
	路径上的最大值．
	求解节点路径上的最大值，用了动态规划的思想，即记录每个节点通过路径上
	的最大值，用于子节点判断本身路径的最大值．
	字节点通过比较左右父亲节点的最大值，来选取本身路径的最大值．　　　　
	
[参考网址]　
1. http://blog.csdn.net/xianglunxi/article/details/9451471
