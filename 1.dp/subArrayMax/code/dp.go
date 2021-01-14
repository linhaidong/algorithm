package main
import "fmt"
func max(a, b int) int{
	if a > b {
		return a
	}
	return b
}
func MaxSubArrayGet(nums []int) int{
	if len(nums) < 1{
		return 0
	}
	dp := make([]int, len(nums))
	//set init status
	dp[0] = nums[0]
	for i := 1; i < len(nums); i++{
		if dp[i-1] < 0{
			dp[i] = nums[i]
		}else{
			dp[i] = dp[i-1] + nums[i]
		}
	}
	result := -1 << 31
	for _, k:= range dp{
		result = max(result, k)
	}
	return result
}
func slice(){
	array := []int{3, 4,}
	fmt.Println(array)
}

func main(){
	nums := []int{-2,1,-3,4,-1,2,1,-5,4}
	max :=  MaxSubArrayGet(nums)  
	fmt.Println("get max is ", max)
}
