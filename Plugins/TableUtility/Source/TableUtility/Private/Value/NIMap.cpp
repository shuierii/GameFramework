// Copyright HuanMos. All Rights Reserved.


#include "Value/NIMap.h"
#include "Value/NIValue.h"
#include "Value/NIInt.h"
#include "Value/NIString.h"
#include "Value/NIUtility.h"

UNIMap::UNIMap()
{
    this->mType = EValueType::Map;
}

void UNIMap::AddBySKey(FString key, UNIValue* value)
{
    if (key.IsEmpty() || value == nullptr)
    {
        

        return;
    }

    if (this->mValueMapOfSKey.Contains(key))
        this->mValueMapOfSKey[key] = value;
    else
        this->mValueMapOfSKey.Add(key, value);
}

void UNIMap::AddByIKey(int32 key, UNIValue* value)
{
    if (value == nullptr)
    {
        

        return;
    }

    if (this->mValueMapOfIKey.Contains(key))
        this->mValueMapOfIKey[key] = value;
    else
        this->mValueMapOfIKey.Add(key, value);
}

bool UNIMap::RemoveBySKey(FString key)
{
    if (key.IsEmpty())
    {
        

        return false;
    }

    if (!this->mValueMapOfSKey.Contains(key))
        return false;

    this->mValueMapOfSKey.Remove(key);

    return true;
}

bool UNIMap::RemoveByIKey(int32 key)
{
    if (!this->mValueMapOfIKey.Contains(key))
        return false;

    this->mValueMapOfIKey.Remove(key);

    return true;
}

UNIValue* UNIMap::GetValueBySKey(FString key)
{
    if (key.IsEmpty())
    {
        

        return nullptr;
    }

    if (!this->mValueMapOfSKey.Contains(key))
        return nullptr;

    return this->mValueMapOfSKey[key];
}

int32 UNIMap::GetValueOfIntBySKey(FString key, int32 defaultValue /*= 0*/)
{
    if (key.IsEmpty())
    {
        

        return defaultValue;
    }

    if (!this->mValueMapOfSKey.Contains(key))
        return defaultValue;

    UNIValue* value = this->mValueMapOfSKey[key];
    if (value == nullptr)
    {
        

        return defaultValue;
    }

    if (!value->IsInt())
        return defaultValue;

    return value->AsInt()->GetValue();
}

FString UNIMap::GetValueOfStringBySKey(FString key, FString defaultValue /*= ""*/)
{
    if (key.IsEmpty())
    {
        

        return defaultValue;
    }

    if (!this->mValueMapOfSKey.Contains(key))
        return defaultValue;

    UNIValue* value = this->mValueMapOfSKey[key];
    if (value == nullptr)
    {
        

        return defaultValue;
    }

    if (!value->IsString())
        return defaultValue;

    return value->AsString()->GetValue();
}

UNIMap* UNIMap::GetValueOfMapBySKey(FString key)
{
    if (key.IsEmpty())
    {
        

        return nullptr;
    }

    if (!this->mValueMapOfSKey.Contains(key))
        return nullptr;

    UNIValue* value = this->mValueMapOfSKey[key];
    if (value == nullptr)
    {
        

        return nullptr;
    }

    if (!value->IsMap())
        return nullptr;

    return value->AsMap();
}

UNIArray* UNIMap::GetValueOfArrayBySKey(FString key)
{
    if (key.IsEmpty())
    {
        

        return nullptr;
    }

    if (!this->mValueMapOfSKey.Contains(key))
        return nullptr;

    UNIValue* value = this->mValueMapOfSKey[key];
    if (value == nullptr)
    {
        

        return nullptr;
    }

    if (!value->IsArray())
        return nullptr;

    return value->AsArray();
}

UNIValue* UNIMap::GetValueByIKey(int32 key)
{
    if (!this->mValueMapOfIKey.Contains(key))
        return nullptr;

    return this->mValueMapOfIKey[key];
}

int32 UNIMap::GetValueOfIntByIKey(int32 key, int32 defaultValue)
{
    if (!this->mValueMapOfIKey.Contains(key))
        return defaultValue;

    UNIValue* value = this->mValueMapOfIKey[key];
    if (value == nullptr)
    {
        

        return defaultValue;
    }

    if (!value->IsInt())
        return defaultValue;

    return value->AsInt()->GetValue();
}

FString UNIMap::GetValueOfStringByIKey(int32 key, FString defaultValue)
{
    if (!this->mValueMapOfIKey.Contains(key))
        return defaultValue;

    UNIValue* value = this->mValueMapOfIKey[key];
    if (value == nullptr)
    {
        

        return defaultValue;
    }

    if (!value->IsString())
        return defaultValue;

    return value->AsString()->GetValue();
}

UNIMap* UNIMap::GetValueOfMapByIKey(int32 key)
{
    if (!this->mValueMapOfIKey.Contains(key))
        return nullptr;

    UNIValue* value = this->mValueMapOfIKey[key];
    if (value == nullptr)
    {
        

        return nullptr;
    }

    if (!value->IsMap())
        return nullptr;

    return value->AsMap();
}

UNIArray* UNIMap::GetValueOfArrayByIKey(int32 key)
{
    if (!this->mValueMapOfIKey.Contains(key))
        return nullptr;

    UNIValue* value = this->mValueMapOfIKey[key];
    if (value == nullptr)
    {
       

        return nullptr;
    }

    if (!value->IsArray())
        return nullptr;

    return value->AsArray();
}

bool UNIMap::ContainsBySKey(FString key)
{
    if (key.IsEmpty())
    {
       

        return false;
    }

    return this->mValueMapOfSKey.Contains(key);
}

bool UNIMap::ContainsByIKey(int32 key)
{
    return this->mValueMapOfIKey.Contains(key);
}

void UNIMap::Append(UNIMap* map)
{
    if (map == nullptr)
        return;

    for (TPair<FString, UNIValue*>& kvMap : map->mValueMapOfSKey)
    {
        if (kvMap.Key.IsEmpty() || kvMap.Value == nullptr)
        {
            

            continue;
        }

        this->AddBySKey(kvMap.Key, kvMap.Value);
    }

    for (TPair<int32, UNIValue*>& kvMap : map->mValueMapOfIKey)
    {
        if (kvMap.Value == nullptr)
        {
            

            continue;
        }

        this->AddByIKey(kvMap.Key, kvMap.Value);
    }
}

UNIMap* UNIMap::ShallowCopy()
{
    UNIMap* map = UNIValue::CreateMap()->AsMap();

    for (TPair<FString, UNIValue*>& kvMap : this->mValueMapOfSKey)
    {
        map->AddBySKey(kvMap.Key, kvMap.Value);
    }

    for (TPair<int32, UNIValue*>& kvMap : this->mValueMapOfIKey)
    {
        map->AddByIKey(kvMap.Key, kvMap.Value);
    }

    return map;
}

void UNIMap::Clear()
{
    this->mValueMapOfSKey.Empty();

    this->mValueMapOfIKey.Empty();
}

int32 UNIMap::Num()
{
    return this->mValueMapOfSKey.Num() + this->mValueMapOfIKey.Num();
}

int32 UNIMap::NumOfSKey()
{
    return this->mValueMapOfSKey.Num();
}

int32 UNIMap::NumOfIKey()
{
    return this->mValueMapOfIKey.Num();
}

TMap<FString, UNIValue*> UNIMap::GetValueMapOfSKey()
{
    return this->mValueMapOfSKey;
}

TMap<int32, UNIValue*> UNIMap::GetValueMapOfIKey()
{
    return this->mValueMapOfIKey;
}

TArray<FString> UNIMap::GetKeysOfSKey()
{
    TArray<FString> list;

    for (TPair<FString, UNIValue*>& kvMap : this->mValueMapOfSKey)
    {
        list.Add(kvMap.Key);
    }

    return list;
}

TArray<UNIValue*> UNIMap::GetValuesOfSKey()
{
    TArray<UNIValue*> list;

    for (TPair<FString, UNIValue*>& kvMap : this->mValueMapOfSKey)
    {
        list.Add(kvMap.Value);
    }

    return list;
}

TArray<int32> UNIMap::GetKeysOfIKey()
{
    TArray<int32> list;

    for (TPair<int32, UNIValue*>& kvMap : this->mValueMapOfIKey)
    {
        list.Add(kvMap.Key);
    }

    return list;
}

TArray<UNIValue*> UNIMap::GetValuesOfIKey()
{
    TArray<UNIValue*> list;

    for (TPair<int32, UNIValue*>& kvMap : this->mValueMapOfIKey)
    {
        list.Add(kvMap.Value);
    }

    return list;
}

FString UNIMap::GetDesc()
{
    return UNIUtility::ConvertToString(this);
}

