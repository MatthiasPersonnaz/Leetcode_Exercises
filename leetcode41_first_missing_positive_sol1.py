# SOLUTION LOUIS
class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        mx, mn = nums[0], nums[0]
        n = 0 # length
        for num in nums:
            n += 1
            mn = min(mn, num)
            mx = max(mx, num)
        
        # easy cases
        if mx <= 0:
            return 1
        if mn >= 2:
            return 1
        if 1 not in nums:
            return 1
        
        # preprocessing
        for (i, num) in enumerate(nums):
            if num <= 0:
                nums[i] = 1
            if num > n:
                nums[i] = 1
                
        # processing
        for num in nums:
            nums[num%(n+1) - 1] += (n+1) # flag, we've seen `num`
            
        # finding the solution
        for (i, num) in enumerate(nums):
            if num < (n+1): # we've not marked this one
                return i+1                
            
        return mx+1
