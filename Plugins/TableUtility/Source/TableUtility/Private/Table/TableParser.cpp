// Copyright HuanMos. All Rights Reserved.

#include "Table/TableParser.h"
#include "Table/TableData.h"
#include "Value/NIUtility.h"
#include "Table/RowData.h"
#include "Value/NIValue.h"
#include "Value/NIString.h"
#include "Value/NIInt.h"

UTableData* UTableParser::ParseTable(FString tableName, TArray<FString>& lines, bool ignoreCommentCol)
{
    if (lines.Num() <= 0)
        return nullptr;

    // 0.记录数据
    this->mTableName = tableName;

    // 1.提取表格信息
    if (!this->FetchTableInfo(tableName, lines, ignoreCommentCol))
        return nullptr;

    // 2.构建表格数据
    return this->CreateTableData(tableName);
}

bool UTableParser::FetchTableInfo(FString tableName, TArray<FString>& lines, bool ignoreCommentCol)
{
    if (lines.Num() <= 0)
        return false;

    int32 validLineNum = 0; // 有效行数目
    FString fieldMemoLine; // 字段备注行
    TArray<FString> fieldType; // 列数据类型声明行数据
    int32 fieldNum = 0; // 字段数目
    TArray<int32> validFieldIndexs; // 有效列下标

    for (FString& line : lines)
    {
        // 1.去掉首位空格
        line = line.TrimStartAndEnd();

        // 2.注释行
        if (this->IsAnnotationLine(*line))
        {
            // 此行为列备注行
            if (validLineNum == 0)
                fieldMemoLine = line;

            continue;
        }

        // 3.获取行所有字段数据
        TArray<FString> fields = this->FetchFields(*line);

        // 空行,例如: ,,,,,
        if (this->IsEmptyLine(fields))
            continue;

        // 有效行数目递增
        validLineNum++;

        // 4.数据类型声明行
        if (validLineNum == 1)
        {
            fieldType = fields;

            fieldNum = fieldType.Num();

            continue;
        }

        // 列数目不一致
        if (fields.Num() != fieldNum)
        {
            

            return false;
        }

        // 5.列字段声明行
        if (validLineNum == 2)
        {
            // 提取列备注行字段数据
            TArray<FString> fieldMemoFields = this->FetchFields(*fieldMemoLine);
            if (fieldMemoFields.Num() != fieldNum)
            {
                

                return false;
            }

            // 获取有效字段下标
            validFieldIndexs = this->FetchValidFieldIndexs(fieldMemoFields, ignoreCommentCol);
            if (validFieldIndexs.Num() <= 0)
            {
                

                return false;
            }

            // 根据有效列收集有效列信息
            for (int32 i = 0; i < validFieldIndexs.Num(); i++)
            {
                int32 validIndex = validFieldIndexs[i];

                FFieldInfo fieldInfo;
                fieldInfo.Name = fields[validIndex];
                fieldInfo.Type = fieldType[validIndex];

                this->mFieldInfos.Add(fieldInfo);
            }

            // 默认第一列为主键
            if (this->mFieldInfos.Num() > 0)
                this->mPrimaryKey = this->mFieldInfos[0].Name;

            continue;
        }

        // 6.收集有效列
        TArray<FString> validFields;
        if (validFieldIndexs.Num() != fields.Num())
        {
            for (int32 i = 0; i < validFieldIndexs.Num(); i++)
            {
                int32 validIndex = validFieldIndexs[i];

                validFields.Add(fields[validIndex]);
            }

            fields = validFields;
        }

        // 7.收集行数据
        FRowInfo rowInfo;
        for (int32 i = 0; i < this->mFieldInfos.Num(); i++)
        {
            rowInfo.InfoMap.Add(this->mFieldInfos[i].Name, fields[i]);
        }

        // 8.加入到表格数据中
        this->mTableInfo.Add(rowInfo);
    }

    return true;
}

UTableData* UTableParser::CreateTableData(FString tableName)
{
    if (this->mFieldInfos.Num() <= 0 || this->mTableInfo.Num() <= 0)
        return nullptr;

    UTableData* tableData = NewObject<UTableData>(this);
    if (tableData == nullptr)
        return nullptr;

    // 1.设置基本信息
    tableData->SetTableName(tableName);
    tableData->SetPrimaryKey(this->mPrimaryKey);
    tableData->SetFields(this->mFieldInfos);

    // 2.遍历行
    for (FRowInfo& rowInfo : this->mTableInfo)
    {
        URowData* rowData = NewObject<URowData>(this);
        if (rowData == nullptr)
            return nullptr;

        // 3.遍历列
        for (FFieldInfo& fieldInfo : this->mFieldInfos)
        {
            if (!rowInfo.InfoMap.Contains(fieldInfo.Name))
            {
                

                continue;
            }

            // 字段值
            FString fieldValue = rowInfo.InfoMap[fieldInfo.Name];

            // 解析字段值
            UNIValue* value = this->ParseFieldValue(fieldInfo.Type, fieldValue);
            if (value == nullptr)
            {
                

                return nullptr;
            }

            // 3.1.记录行数据
            rowData->AddData(fieldInfo.Name, value);
        }

        // 2.1.记录表格数据
        UNIValue* primaryKeyValue = rowData->GetData(this->mPrimaryKey);
        if (primaryKeyValue == nullptr)
        {
            

            return nullptr;
        }

        // 主键是string类型
        if (primaryKeyValue->IsString())
        {
            tableData->AddRowBySKey(primaryKeyValue->AsString()->GetValue(), rowData);
        }
        // 主键是int类型
        else if (primaryKeyValue->IsInt())
        {
            tableData->AddRowByIKey(primaryKeyValue->AsInt()->GetValue(), rowData);
        }
        // 无法识别的主键类型
        else
        {
            

            return nullptr;
        }
    }

    return tableData;
}

bool UTableParser::IsAnnotationLine(const TCHAR* line)
{
    if (line == nullptr || FCString::Strlen(line) <= 0)
        return true;

    int32 length = FCString::Strlen(line);

    for (int32 i = 0; i < length; i++)
    {
        auto c = line[i];

        if (c == TEXT('"'))
            continue;

        if (c == TEXT(' '))
            continue;

        if (c == TEXT('#'))
            return true;

        return false;
    }

    return false;
}

TArray<FString> UTableParser::FetchFields(const TCHAR* line)
{
    TArray<FString> fields;
    int32 startPos = 0;
    int32 offset = 0;
    int32 length = FCString::Strlen(line);

    int32 qMarkNum = 0; // 双引号数目

    while (offset < length)
    {
        auto c = line[offset];

        switch (c)
        {
        case TEXT('"'):
            {
                qMarkNum++;
            }
            break;

        // 分割符号
        case TEXT(','):
            {
                if (qMarkNum % 2 == 0)
                {
                    fields.Add(this->FetchField(line, startPos, offset - startPos));

                    startPos = offset + 1;
                }
            }
            break;
        }

        offset++;
    }

    fields.Add(this->FetchField(line, startPos, offset - startPos));

    return fields;
}

FString UTableParser::FetchField(FString line, int32 startPos, int32 length)
{
    if (length < 1)
        return "";

    // 非""包裹的数据，可能是int、float、空格、等等
    if (line[startPos] != '"')
        return line.Mid(startPos, length);

    // 双重引号
    FString valueFormat = TEXT("\"\"");
    if (length <= valueFormat.Len())
        return "";

    // 获取引号内的数据
    startPos++;
    length -= valueFormat.Len();
    FString str = line.Mid(startPos, length);

    // 双重双引用替换为单双引号
    // 例如: ""class_id"":80000 -> "class_id":80000
    str = str.Replace(*valueFormat, TEXT("\""));

    return str;
}

bool UTableParser::IsEmptyLine(TArray<FString>& fields)
{
    if (fields.Num() <= 0)
        return true;

    for (FString field : fields)
    {
        field = field.TrimStartAndEnd();

        // 空字段数据
        if (field.IsEmpty())
            continue;

        // 非空字段数据
        return false;
    }

    return true;
}

TArray<int32> UTableParser::FetchValidFieldIndexs(TArray<FString>& fields, bool ignoreCommentCol)
{
    TArray<int32> validIndexs;

    for (int32 i = 0; i < fields.Num(); i++)
    {
        // 加了*为注释列
        if (ignoreCommentCol && fields[i].EndsWith(TEXT("*")))
            continue;

        // 记录有效列下标
        validIndexs.Add(i);
    }

    return validIndexs;
}

UNIValue* UTableParser::ParseFieldValue(FString valueType, FString valueStr)
{
    if (valueType.IsEmpty())
        return nullptr;

    UNIValue* value = nullptr;

    if (valueType == "auto")
    {
        value = this->ParseAutoType(valueStr);
    }
    else if (valueType == "int")
    {
        value = this->ParseIntType(valueStr);
    }
    else if (valueType == "string")
    {
        value = this->ParseStringType(valueStr);
    }
    else if (valueType == "map")
    {
        value = this->ParseMapType(valueStr);
    }
    else if (valueType == "array")
    {
        value = this->ParseArrayType(valueStr);
    }
    else
    {
        return nullptr;
    }

    return value;
}

UNIValue* UTableParser::ParseAutoType(FString valueStr)
{
    // 空位
    if (valueStr.IsEmpty())
        return UNIValue::CreateString(valueStr);

    // 1.别名符号
    // if (valueStr.StartsWith(TEXT("@")))
    // {
    //     // 获取别名
    //     // @EQUIP_TYPE_HAT -> EQUIP_TYPE_HAT
    //     FString alias = valueStr.Replace(TEXT("@"), TEXT(""));
    //
    //     // 获取别名值
    //     int32 aliasValue = UAliasParser::GetAliasValue(alias);
    //     if (aliasValue < 0)
    //     {
    //         
    //
    //         // 这里默认使用string处理
    //         return UNIValue::CreateString(valueStr);
    //     }
    //
    //     return UNIValue::CreateInt(aliasValue);
    // }

    // 2.map类型
    if (valueStr.StartsWith(TEXT("{")))
    {
        return UNIUtility::RestoreFromString(valueStr);
    }

    // 3.array类型
    if (valueStr.StartsWith(TEXT("[")))
    {
        return UNIUtility::RestoreFromString(valueStr);
    }

    // 4.int/float
    if (FCString::IsNumeric(*valueStr))
    {
        return UNIUtility::RestoreFromString(valueStr);
    }

    // 5.string
    if (valueStr.StartsWith(TEXT("\"")))
    {
        return UNIUtility::RestoreFromString(valueStr);
    }

    // 6.其他一律当做string处理
    return UNIValue::CreateString(valueStr);
}

UNIValue* UTableParser::ParseIntType(FString valueStr)
{
    if (valueStr.IsEmpty())
        return nullptr;

    // 1.别名符号
    // if (valueStr.StartsWith(TEXT("@")))
    // {
    //     // 获取别名
    //     // @EQUIP_TYPE_HAT -> EQUIP_TYPE_HAT
    //     FString alias = valueStr.Replace(TEXT("@"), TEXT(""));
    //
    //     // 获取别名值
    //     int32 aliasValue = UAliasParser::GetAliasValue(alias);
    //     if (aliasValue < 0)
    //     {
    //         
    //
    //         // 这里默认使用string处理
    //         return UNIValue::CreateString(valueStr);
    //     }
    //
    //     return UNIValue::CreateInt(aliasValue);
    // }
    // 2.整形数字
    else
    {
        int32 value = FCString::Atoi(*valueStr);

        return UNIValue::CreateInt(value);
    }
}

UNIValue* UTableParser::ParseStringType(FString valueStr)
{
    return UNIValue::CreateString(valueStr);
}

UNIValue* UTableParser::ParseMapType(FString valueStr)
{
    if (valueStr.IsEmpty())
        return nullptr;

    if (!valueStr.StartsWith(TEXT("{")))
        return nullptr;

    return UNIUtility::RestoreFromString(valueStr);
}

UNIValue* UTableParser::ParseArrayType(FString valueStr)
{
    if (valueStr.IsEmpty())
        return nullptr;

    if (!valueStr.StartsWith(TEXT("[")))
        return nullptr;

    return UNIUtility::RestoreFromString(valueStr);
}
