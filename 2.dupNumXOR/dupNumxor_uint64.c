#include <stdint.h>
#include <stdio.h>

int duplicateNumbersXOR(int *nums, int numsSize)
{
    uint64_t set = 0ULL;
    int xor = 0;
    for (int i = 0; i < numsSize; ++i)
    {
        if (set & (1ULL << nums[i]))
            xor ^= nums[i];
        set |= (1ULL << nums[i]);
    }
    return xor;
}

#define test1_Size 4
#define test1_ans 1
int test1_data[test1_Size] = {1, 2, 1, 3};

#define test2_Size 14
#define test2_ans 12
int test2_data[test2_Size] = {1, 2, 3, 4, 6, 7, 8, 2, 9, 9, 3, 5, 1, 5};

#define test3_Size 16
#define test3_ans 43
int test3_data[test3_Size] = {3, 49, 49, 3, 8, 12, 19, 19,
                              28, 27, 28, 50, 31, 36, 50, 36};

int main()
{
    int ans1 = duplicateNumbersXOR(test1_data, test1_Size);
    printf("%2d, %2d, %2d\n", ans1, test1_ans, ans1 == test1_ans);

    int ans2 = duplicateNumbersXOR(test2_data, test2_Size);
    printf("%2d, %2d, %2d\n", ans2, test2_ans, ans2 == test2_ans);

    int ans3 = duplicateNumbersXOR(test3_data, test3_Size);
    printf("%2d, %2d, %2d\n", ans3, test3_ans, ans3 == test3_ans);
}