// Copyright HuanMos. All Rights Reserved.

#include "Table/RowData.h"
#include "Value/NIValue.h"
#include "Value/NIMap.h"
#include "Value/NIArray.h"
#include "Value/NIInt.h"
#include "Value/NIString.h"
#include "Value/NIUtility.h"

bool URowData::AddData(FString field, UNIValue* data)
{
    if (field.IsEmpty() || data == nullptr)
        return false;

    if (this->mDataMap.Contains(field))
    {

        
        return false;
    }

    this->mDataMap.Add(field, data);

    return true;
}

bool URowData::RemoveData(FString field)
{
    if (field.IsEmpty())
        return false;

    if (!this->mDataMap.Contains(field))
    {
        

        return false;
    }

    this->mDataMap.Remove(field);

    return true;
}

UNIValue* URowData::GetData(FString field)
{
    if (!this->mDataMap.Contains(field))
        return nullptr;

    return this->mDataMap[field];
}

int32 URowData::GetDataOfInt(FString field, int32 defaultData /*= 0*/)
{
    UNIValue* data = this->GetData(field);
    if (data == nullptr)
        return defaultData;

    if (!data->IsInt())
        return defaultData;

    return data->AsInt()->GetValue();
}

FString URowData::GetDataOfString(FString field, FString defaultData /*= ""*/)
{
    UNIValue* data = this->GetData(field);
    if (data == nullptr)
        return defaultData;

    if (!data->IsString())
        return defaultData;

    return data->AsString()->GetValue();
}

UNIMap* URowData::GetDataOfMap(FString field)
{
    UNIValue* data = this->GetData(field);
    if (data == nullptr)
        return nullptr;

    if (!data->IsMap())
        return nullptr;

    return data->AsMap();
}

UNIArray* URowData::GetDataOfArray(FString field)
{
    UNIValue* data = this->GetData(field);
    if (data == nullptr)
        return nullptr;

    if (!data->IsArray())
        return nullptr;

    return data->AsArray();
}

bool URowData::Contains(FString field)
{
    return this->mDataMap.Contains(field);
}

TArray<FString> URowData::GetAllFields()
{
    TArray<FString> list;

    for (TPair<FString, UNIValue*>& kvMap : this->mDataMap)
    {
        list.Add(kvMap.Key);
    }
    return list;
}

FString URowData::GetDesc()
{
    int32 index = 0;

    int32 num = this->mDataMap.Num();

    FString content = "{";

    for (TPair<FString, UNIValue*>& kvMap : this->mDataMap)
    {
        if (kvMap.Value == nullptr)
            continue;

        // key
        content += "\"" + kvMap.Key + "\"" + ":";

        // value
        content += UNIUtility::ConvertToString(kvMap.Value);

        index++;

        // 遍历到最后一个
        if (index >= num)
            continue;

        // 分号
        content += ",";
    }

    return content + "}";
}
