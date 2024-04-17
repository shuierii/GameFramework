// Copyright HuanMos. All Rights Reserved.


#include "Value/NIValue.h"
#include "Value/NIInt.h"
#include "Value/NIString.h"
#include "Value/NIMap.h"
#include "Value/NIArray.h"

#pragma region 构建接口

UNIInt* UNIValue::CreateInt(int32 value /*= 0*/)
{
    UNIInt* obj = NewObject<UNIInt>();

    obj->SetValue(value);

    return obj;
}

UNIString* UNIValue::CreateString(FString value /*= FString()*/)
{
    UNIString* obj = NewObject<UNIString>();

    obj->SetValue(value);

    return obj;
}

UNIMap* UNIValue::CreateMap()
{
    return NewObject<UNIMap>();
}

UNIArray* UNIValue::CreateArray()
{
    return NewObject<UNIArray>();
}

#pragma endregion

#pragma region 类型判断接口

bool UNIValue::IsInt() const
{
    return this->mType == EValueType::Int;
}

bool UNIValue::IsString() const
{
    return this->mType == EValueType::String;
}

bool UNIValue::IsMap() const
{
    return this->mType == EValueType::Map;
}

bool UNIValue::IsArray() const
{
    return this->mType == EValueType::Array;
}

#pragma endregion

#pragma region 类型转换接口

UNIInt* UNIValue::AsInt()
{
    // 不是UNIInt类型
    if (this->mType != EValueType::Int)
    {
        

        return nullptr;
    }

    return Cast<UNIInt>(this);
}

UNIString* UNIValue::AsString()
{
    // 不是UNIString类型
    if (this->mType != EValueType::String)
    {
        

        return nullptr;
    }

    return Cast<UNIString>(this);
}

UNIMap* UNIValue::AsMap()
{
    // 不是UNIMap类型
    if (this->mType != EValueType::Map)
    {
       

        return nullptr;
    }

    return Cast<UNIMap>(this);
}

UNIArray* UNIValue::AsArray()
{
    // 不是UNIArray类型
    if (this->mType != EValueType::Array)
    {
       

        return nullptr;
    }

    return Cast<UNIArray>(this);
}

#pragma endregion

UNIValue* UNIValue::DeepCopy(UNIValue* value)
{
    if (value == nullptr)
    {
        

        return nullptr;
    }

    if (value->IsInt())
        return UNIValue::CreateInt(value->AsInt()->GetValue());
    else if (value->IsString())
        return UNIValue::CreateString(value->AsString()->GetValue());
    else if (value->IsArray())
    {
        UNIArray* newArray = UNIValue::CreateArray();

        for (UNIValue* element : value->AsArray()->GetValue())
        {
            newArray->Add(DeepCopy(element));
        }

        return newArray;
    }
    else if (value->IsMap())
    {
        UNIMap* newMap = UNIValue::CreateMap();

        for (TPair<FString, UNIValue*> kvMap : value->AsMap()->GetValueMapOfSKey())
        {
            newMap->AddBySKey(kvMap.Key, DeepCopy(kvMap.Value));
        }

        for (TPair<int32, UNIValue*> kvMap : value->AsMap()->GetValueMapOfIKey())
        {
            newMap->AddByIKey(kvMap.Key, DeepCopy(kvMap.Value));
        }

        return newMap;
    }
    else
    {
        

        return nullptr;
    }
}