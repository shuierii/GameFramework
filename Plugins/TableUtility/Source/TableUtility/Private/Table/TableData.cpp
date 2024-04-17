// Copyright HuanMos. All Rights Reserved.


#include "Table/TableData.h"
#include "Table/RowData.h"
#include "Table/TableParser.h"

void UTableData::SetTableName(FString tableName)
{
    this->mTableName = tableName;
}

void UTableData::SetFields(TArray<FFieldInfo>& fieldInfos)
{
    for (FFieldInfo& fieldInfo : fieldInfos)
    {
        this->mFields.Add(fieldInfo.Name);
    }
}

void UTableData::SetPrimaryKey(FString primaryKey)
{
    this->mPrimaryKey = primaryKey;
}

bool UTableData::AddRowBySKey(FString primaryKey, URowData* row)
{
    if (primaryKey.IsEmpty() || row == nullptr)
        return false;

    if (this->mRowMapOfSKey.Contains(primaryKey))
    {
        

        return false;
    }

    this->mRowMapOfSKey.Add(primaryKey, row);

    return true;
}

bool UTableData::AddRowByIKey(int32 primaryKey, URowData* row)
{
    if (row == nullptr)
        return false;

    if (this->mRowMapOfIKey.Contains(primaryKey))
    {
        

        return false;
    }

    this->mRowMapOfIKey.Add(primaryKey, row);

    return true;
}

bool UTableData::RemoveRowBySKey(FString primaryKey)
{
    if (primaryKey.IsEmpty())
        return false;

    if (!this->mRowMapOfSKey.Contains(primaryKey))
    {
        

        return false;
    }

    this->mRowMapOfSKey.Remove(primaryKey);

    return true;
}

bool UTableData::RemoveRowByIKey(int32 primaryKey)
{
    if (!this->mRowMapOfIKey.Contains(primaryKey))
    {
        

        return false;
    }

    this->mRowMapOfIKey.Remove(primaryKey);

    return true;
}

TArray<FString> UTableData::GetFields()
{
    return this->mFields;
}

URowData* UTableData::GetRowBySKey(FString primaryKey)
{
    if (primaryKey.IsEmpty())
        return nullptr;

    if (!this->mRowMapOfSKey.Contains(primaryKey))
        return nullptr;

    return this->mRowMapOfSKey[primaryKey];
}

URowData* UTableData::GetRowByIKey(int32 primaryKey)
{
    if (!this->mRowMapOfIKey.Contains(primaryKey))
        return nullptr;

    return this->mRowMapOfIKey[primaryKey];
}

bool UTableData::ContainsBySKey(FString primaryKey)
{
    return this->mRowMapOfSKey.Contains(primaryKey);
}

bool UTableData::ContainsByIKey(int32 primaryKey)
{
    return this->mRowMapOfIKey.Contains(primaryKey);
}

TMap<FString, URowData*> UTableData::GetRowMapOfSKey()
{
    return this->mRowMapOfSKey;
}

TMap<int32, URowData*> UTableData::GetRowMapOfIKey()
{
    return this->mRowMapOfIKey;
}

TArray<FString> UTableData::GetPrimaryKeysOfSKey()
{
    TArray<FString> list;

    for (TPair<FString, URowData*>& kvMap : this->mRowMapOfSKey)
    {
        list.Add(kvMap.Key);
    }

    return list;
}

TArray<URowData*> UTableData::GetRowsOfSKey()
{
    TArray<URowData*> list;

    for (TPair<FString, URowData*>& kvMap : this->mRowMapOfSKey)
    {
        list.Add(kvMap.Value);
    }

    return list;
}

TArray<int32> UTableData::GetPrimaryKeysOfIKey()
{
    TArray<int32> list;

    for (TPair<int32, URowData*>& kvMap : this->mRowMapOfIKey)
    {
        list.Add(kvMap.Key);
    }

    return list;
}

TArray<URowData*> UTableData::GetRowsOfIKey()
{
    TArray<URowData*> list;

    for (TPair<int32, URowData*>& kvMap : this->mRowMapOfIKey)
    {
        list.Add(kvMap.Value);
    }

    return list;
}

FString UTableData::GetTableName()
{
    return this->mTableName;
}

FString UTableData::GetPrimaryKey()
{
    return this->mPrimaryKey;
}

bool UTableData::AppendTable(UTableData* table)
{
    auto fields = table->GetFields();
    if (this->mFields.Num() != fields.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("the table fields num not equal native fields."));
        
        return false;
    }

    for (auto field : this->mFields)
    {
        if (!fields.Contains(field))
        {
            UE_LOG(LogTemp, Error, TEXT("the table fields not equal native fields."));
        
            return false;
        }
    }

    auto mapOfIkey = table->GetRowMapOfIKey();
    for (auto kv : mapOfIkey)
    {
        this->mRowMapOfIKey.Add(kv.Key, kv.Value);
    }

    auto mapOfSkey = table->GetRowMapOfSKey();
    for (auto kv : mapOfSkey)
    {
        this->mRowMapOfSKey.Add(kv.Key, kv.Value);
    }

    return true;
}

FString UTableData::GetDesc()
{
    FString str = "[";

    int32 index = 0;

    int32 num = this->mRowMapOfIKey.Num();

    // key:int32
    for (TPair<int32, URowData*>& kvMap : this->mRowMapOfIKey)
    {
        index++;

        if (kvMap.Value == nullptr)
            continue;

        str += kvMap.Value->GetDesc();

        if (index >= num)
            continue;

        str += ",";
    }

    index = 0;

    num = this->mRowMapOfSKey.Num();

    // key:FString
    for (TPair<FString, URowData*>& kvMap : this->mRowMapOfSKey)
    {
        index++;

        if (kvMap.Value == nullptr)
            continue;

        str += kvMap.Value->GetDesc();

        if (index >= num)
            continue;

        str += ",";
    }

    str += "]";

    return str;
}
