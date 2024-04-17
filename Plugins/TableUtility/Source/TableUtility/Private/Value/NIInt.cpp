// Copyright HuanMos. All Rights Reserved.


#include "Value/NIInt.h"


UNIInt::UNIInt()
{
    this->mType = EValueType::Int;
}

void UNIInt::SetValue(int32 value)
{
    this->mValue = value;
}

int32 UNIInt::GetValue()
{
    return this->mValue;
}
