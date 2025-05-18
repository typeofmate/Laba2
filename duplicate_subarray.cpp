#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>


int longest_duplicate_subarray(const std::vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0; // нет возможности повторени€

    int low = 1, high = n - 1;
    int max_length = 0;

    // бинарный поиск по длине
    while (low <= high) {
        int mid = low + (high - low) / 2;
        bool found = false;
        std::unordered_set<std::string> seen;

        // проверка подмассивов длины mid
        for (int i = 0; i <= n - mid; ++i) {
            // подмассив в строку
            std::string subarray;
            for (int j = i; j < i + mid; ++j) {
                subarray += std::to_string(nums[j]);
                if (j != i + mid - 1) subarray += ",";
            }

            // ≈сли подмасс встречалс€, найден дубликат
            if (seen.count(subarray)) {
                found = true;
                max_length = std::max(max_length, mid);
                break;
            }
            seen.insert(subarray);
        }

        // границы бинарного поиска
        if (found) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return max_length;
}

int main()
{
    std::vector<int> nums1 = { 1, 2, 3, 4, 2, 3, 4, 5 };
    std::cout << longest_duplicate_subarray(nums1) << std::endl; // 3

    std::vector<int> nums2 = { 1, 2, 1, 2, 1, 2 };
    std::cout << longest_duplicate_subarray(nums2) << std::endl; // 4

    std::vector<int> nums3 = { 5, 5, 5, 5 };
    std::cout << longest_duplicate_subarray(nums3) << std::endl; // 3
}