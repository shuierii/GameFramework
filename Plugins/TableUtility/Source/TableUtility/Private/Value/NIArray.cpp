// Copyright HuanMos. All Rights Reserved.


#include "Value/NIArray.h"
#include "Value/NIValue.h"
#include "Value/NIInt.h"
#include "Value/NIString.h"
#include "Value/NIUtility.h"


UNIArray::UNIArray()
{
    this->mType = EValueType::Array;
}

int32 UNIArray::Add(UNIValue* element)
{
    if (element == nullptr)
    {
        

        return -1;
    }

    return this->mValue.Add(element);
}

int32 UNIArray::Remove(UNIValue* element)
{
    if (element == nullptr)
    {
        

        return -1;
    }

    if (!this->mValue.Contains(element))
        return -1;

    return this->mValue.Remove(element);
}

bool UNIArray::RemoveAt(int32 index)
{
    if (index >= this->mValue.Num())
        return false;

    this->mValue.RemoveAt(index);

    return true;
}

bool UNIArray::Set(int32 index, UNIValue* value)
{
    if (value == nullptr)
    {
        

        return false;
    }

    if (index >= this->mValue.Num())
        return false;

    this->mValue[index] = value;

    return true;
}

UNIValue* UNIArray::Get(int32 index)
{
    if (index >= this->mValue.Num())
        return nullptr;

    return this->mValue[index];
}

int32 UNIArray::Num()
{
    return this->mValue.Num();
}

TArray<UNIValue*> UNIArray::GetValue()
{
    return this->mValue;
}

int32 UNIArray::Find(UNIValue* element)
{
    if (element == nullptr)
    {
        

        return -1;
    }

    return this->mValue.Find(element);
}

int32 UNIArray::FindValueOfInt(int32 value)
{
    int32 index = -1;

    for (UNIValue* element : this->mValue)
    {
        index++;

        if (element == nullptr)
            continue;

        // 不是UNIInt
        if (!element->IsInt())
            continue;

        // 找到相等第一个值
        if (element->AsInt()->GetValue() == value)
            return index;
    }

    return INDEX_NONE;
}

int32 UNIArray::FindValueOfString(FString value)
{
    if (value.IsEmpty())
    {
        

        return -1;
    }

    int32 index = -1;

    for (UNIValue* element : this->mValue)
    {
        index++;

        if (element == nullptr)
            continue;

        // 不是UNIString
        if (!element->IsString())
            continue;

        // 找到相等第一个值
        if (element->AsString()->GetValue() == value)
            return index;
    }

    return INDEX_NONE;
}

void UNIArray::AppendByTArray(TArray<UNIValue*> value)
{
    this->mValue.Append(value);
}

bool UNIArray::AppendByNIArray(UNIArray* value)
{
    if (value == nullptr)
    {
        

        return false;
    }

    this->mValue.Append(value->GetValue());

    return true;
}

FString UNIArray::GetDesc()
{
    return UNIUtility::ConvertToString(this);
}
