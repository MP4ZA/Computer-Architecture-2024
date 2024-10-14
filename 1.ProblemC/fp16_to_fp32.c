#include <stdio.h>
#include <stdint.h>

static inline int my_clz(uint32_t x)
{
    int count = 0;
    for (int i = 31; i >= 0; --i)
    {
        if (x & (1U << i))
            break;
        count++;
    }
    return count;
}

static inline uint32_t fp16_to_fp32(uint16_t h)
{

    const uint32_t w = (uint32_t)h << 16;
    const uint32_t sign = w & UINT32_C(0x80000000);
    const uint32_t nonsign = w & UINT32_C(0x7FFFFFFF);

    uint32_t renorm_shift = my_clz(nonsign);
    renorm_shift = renorm_shift > 5 ? renorm_shift - 5 : 0;

    const int32_t inf_nan_mask = ((int32_t)(nonsign + 0x04000000) >> 8) & INT32_C(0x7F800000);
    const int32_t zero_mask = (int32_t)(nonsign - 1) >> 31;

    return sign | ((((nonsign << renorm_shift >> 3) + ((0x70 - renorm_shift) << 23)) | inf_nan_mask) & ~zero_mask);
}

#define test1 0x3C00
#define ans1 0x3F800000
#define test2 0xCC10
#define ans2 0xC1820000
#define test3 0x962C
#define ans3 0xBAC58000

int main()
{
    uint16_t input;
    uint32_t ans;
    input = test1;
    ans = fp16_to_fp32(input);
    printf("%d %d %x\n", input, ans, ans == ans1);
    input = test2;
    ans = fp16_to_fp32(input);
    printf("%d %d %x\n", input, ans, ans == ans2);
    input = test3;
    ans = fp16_to_fp32(input);
    printf("%d %d %x\n", input, ans, ans == ans3);
}