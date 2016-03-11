class Solution {
public:
	/**
	* @param nums a list of integer
	* @return void
	*/
	void wiggleSort(vector<int>& nums) {
		// Write your code here
		if (nums.size() == 0)
			return;
		bool flag = true;
		size_t num = nums.size() - 1;
		for (size_t i = 0; i != num; ++i)
		{
			if (flag) // <=
			{
				if (nums[i] > nums[i + 1])
					std::swap(nums[i], nums[i + 1]);
			}
			else // >=
			{
				if (nums[i] < nums[i + 1])
					std::swap(nums[i], nums[i + 1]);
			}
			flag = !flag;
		}
	}
};