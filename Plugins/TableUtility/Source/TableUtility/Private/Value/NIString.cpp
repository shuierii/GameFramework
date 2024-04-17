// Copyright HuanMos. All Rights Reserved.


#include "Value/NIString.h"

UNIString::UNIString()
{
    this->mType = EValueType::String;
}

void UNIString::SetValue(FString value)
{
    this->mValue = value;
}

FString UNIString::GetValue()
{
    return this->mValue;
}
