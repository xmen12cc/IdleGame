#include "BigNumber.h"

FBigNumber::FBigNumber()
{
    // Initialize with at least one group containing 0
    Groups.Add(0);
}

void FBigNumber::Add(int32 Value)
{
    int32 Carry = Value;
    for (int32 i = 0; i < Groups.Num() && Carry > 0; i++)
    {
        Groups[i] += Carry;
        Carry = Groups[i] / 1000000000; // Overflow to the next group
        Groups[i] %= 1000000000; // Keep within the group range
    }

    if (Carry > 0)
    {
        Groups.Add(Carry); // Add a new group for the carry
    }
}

void FBigNumber::Subtract(int32 Value)
{
    int32 Borrow = Value;
    for (int32 i = 0; i < Groups.Num() && Borrow > 0; i++)
    {
        Groups[i] -= Borrow;
        if (Groups[i] < 0)
        {
            Borrow = (-Groups[i] - 1) / 1000000000 + 1; // Borrow from the next group
            Groups[i] += Borrow * 1000000000; // Adjust the current group
        }
        else
        {
            Borrow = 0;
        }
    }

    // Remove empty groups at the end
    while (Groups.Num() > 1 && Groups[Groups.Num() - 1] == 0)
    {
        Groups.RemoveAt(Groups.Num() - 1);
    }
}

FString FBigNumber::ToString() const
{
    FString Result = FString::Printf(TEXT("%d"), Groups[Groups.Num() - 1]);

    for (int32 i = Groups.Num() - 2; i >= 0; i--)
    {
        Result += FString::Printf(TEXT("%09d"), Groups[i]);
    }

    return Result;
}
