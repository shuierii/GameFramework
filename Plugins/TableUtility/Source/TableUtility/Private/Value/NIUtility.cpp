// Copyright 2020 Andras Ketzer, All rights reserved.

#include "Value/NIUtility.h"
#include "Value/NIInt.h"
#include "Value/NIString.h"
#include "Value/NIArray.h"
#include "Value/NIMap.h"
#include "Value/NIValue.h"

TMap<FString, TArray<FString>> UNIUtility::mPathSplits;

#pragma region 混合数据转换

FString UNIUtility::ConvertToString(UNIValue* value)
{
    if (value == nullptr)
        return FString();

    FString content = FString();

    if (value->IsInt())
    {
        return FString::FromInt(value->AsInt()->GetValue());
    }
    else if (value->IsString())
    {
        return "\"" + value->AsString()->GetValue() + "\"";
    }
    else if (value->IsArray())
    {
        content = "[";

        int32 num = value->AsArray()->Num();

        for (int32 i = 0; i < num; i++)
        {
            content += ConvertToString(value->AsArray()->Get(i));

            if (i + 1 >= num)
                continue;

            content += ",";
        }

        return content + "]";
    }
    else if (value->IsMap())
    {
        content = "{";

        int32 index = 0;

        int32 numOfString = value->AsMap()->NumOfSKey();

        int32 numOfInt = value->AsMap()->NumOfIKey();

        for (TPair<FString, UNIValue*> kvMap : value->AsMap()->GetValueMapOfSKey())
        {
            content += "\"" + kvMap.Key + "\"" + ":";

            content += ConvertToString(kvMap.Value);

            index++;

            // 遍历到最后一个 && mValueMapOfIKey没有数据
            if (index >= numOfString && numOfInt <= 0)
                continue;

            content += ",";
        }

        index = 0;

        for (TPair<int32, UNIValue*> kvMap : value->AsMap()->GetValueMapOfIKey())
        {
            content += FString::FromInt(kvMap.Key) + ":";

            content += ConvertToString(kvMap.Value);

            index++;

            // 遍历到最后一个
            if (index >= numOfInt)
                continue;

            content += ",";
        }

        return content + "}";
    }
    else
    {
        
    }

    return FString();
}

UNIValue* UNIUtility::RestoreFromString(FString content)
{
    if (content.IsEmpty())
        return nullptr;

    int32 offset = 0;

    wchar_t c = content[offset];

    switch (c)
    {
    // String
    case '"':
        {
            offset++;

            return RestoreString(content, offset);
        }
        break;

    // Array
    case '[':
        {
            offset++;

            return RestoreArray(content, offset);
        }
        break;

    // map
    case '{':
        {
            offset++;

            return RestoreMap(content, offset);
        }
        break;

    // 数字
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        {
            return RestoreNumber(content, offset);
        }
        break;

    default:
        {
            
        }
        break;
    }

    return nullptr;
}

#pragma endregion

#pragma region 混合数据操作

bool UNIUtility::ExpressSet(const FString& path, UNIMap* dbase, UNIValue* value)
{
    // 输入参数检测
    if (path.IsEmpty() || dbase == nullptr || value == nullptr)
        return false;

    // 路径step
    TArray<FString> pathArray;

    // 1.不包含此路径,解析路径且记录
    if (!mPathSplits.Contains(path))
    {
        // 通过"/"切割路径step
        if (path.ParseIntoArray(pathArray, TEXT("/")) <= 0)
            return false;

        // 记录此路径
        mPathSplits.Add(path, pathArray);

        // 容量体积太大了，警告
        if (mPathSplits.Num() >= 1024)
        {
            
        }
    }
    else
        pathArray = mPathSplits[path];

    // 当前路径Map
    UNIMap* current = dbase;

    // 2.追踪到目标路径，沿途路径为空的话创建对应路径数据
    for (int i = 0; i < pathArray.Num() - 1; i++)
    {
        // 当前路径Key
        FString step = pathArray[i];

        // 2.1.没有相应路径数据，构建
        if (!current->ContainsBySKey(step))
        {
            // 构建Map
            UNIMap* map = UNIValue::CreateMap();
            if (map == nullptr)
                return false;

            // 添加路径中
            current->AddBySKey(step, map);

            // 更新当前路径数据
            current = map;

            // 继续下一步
            continue;
        }

        // 2.2.获取当前路径数据
        UNIValue* map = current->GetValueBySKey(step);
        if (map != nullptr && map->IsMap())
        {
            // 更新当前路径数据
            current = map->AsMap();

            // 继续下一步
            continue;
        }

        // 2.3.空/不是map直接覆盖(不应该出现这种情况)
        // 构建Map
        map = UNIValue::CreateMap();
        if (map == nullptr)
            return false;

        // 添加路径中
        current->AddBySKey(step, map);

        // 更新当前路径数据
        current = map->AsMap();
    }

    // 未找到数据
    if (current == nullptr)
        return false;

    // 3.设置数据
    // 获取最后一个路径step
    FString field = pathArray.Top();
    if (field.IsEmpty())
        return false;

    // 设置数据
    current->AddBySKey(field, value);

    // 返回成功
    return true;
}

UNIValue* UNIUtility::ExpressQuery(const FString& path, UNIMap* dbase)
{
    // 输入参数检测
    if (path.IsEmpty() || dbase == nullptr)
        return nullptr;

    // 路径step
    TArray<FString> pathArray;

    // 1.不包含此路径,解析路径且记录
    if (!mPathSplits.Contains(path))
    {
        // 通过"/"切割路径step
        if (path.ParseIntoArray(pathArray, TEXT("/")) <= 0)
            return nullptr;

        // 记录此路径
        mPathSplits.Emplace(path, pathArray);

        // 容量体积太大了，警告
        if (mPathSplits.Num() >= 1024)
        {
           
        }
    }
    else
        pathArray = mPathSplits[path];

    // 当前路径Map
    UNIMap* current = dbase;

    // 2.追踪到目标路径
    for (int i = 0; i < pathArray.Num() - 1; i++)
    {
        // 当前路径Key
        FString step = pathArray[i];

        // 2.1.没有相应路径数据
        if (!current->ContainsBySKey(step))
            return nullptr;

        // 2.2.获取当前路径数据
        UNIValue* map = current->GetValueBySKey(step);
        if (map != nullptr && map->IsMap())
        {
            // 更新当前路径数据
            current = map->AsMap();

            // 继续下一步
            continue;
        }

        // 2.3.空/不是map
        return nullptr;
    }

    // 未找到数据
    if (current == nullptr)
        return nullptr;

    // 3.设置数据
    // 获取最后一个路径step
    FString step = pathArray.Top();
    if (step.IsEmpty())
        return nullptr;

    // 此路径没有数据
    if (!current->ContainsBySKey(step))
        return nullptr;

    // 返回数据
    return current->GetValueBySKey(step);
}

bool UNIUtility::ExpressContains(const FString& path, UNIMap* dbase)
{
    // 输入参数检测
    if (path.IsEmpty() || dbase == nullptr)
        return false;

    // 路径step
    TArray<FString> pathArray;

    // 1.不包含此路径,解析路径且记录
    if (!mPathSplits.Contains(path))
    {
        // 通过"/"切割路径step
        if (path.ParseIntoArray(pathArray, TEXT("/")) <= 0)
            return false;

        // 记录此路径
        mPathSplits.Emplace(path, pathArray);

        // 容量体积太大了，警告
        if (mPathSplits.Num() >= 1024)
        {
            
        }
    }
    else
    {
        pathArray = mPathSplits[path];
    }

    // 当前路径Map
    UNIMap* current = dbase;

    // 2.追踪到目标路径
    for (int i = 0; i < pathArray.Num() - 1; i++)
    {
        // 当前路径Key
        FString step = pathArray[i];

        // 2.1.没有相应路径数据
        if (!current->ContainsBySKey(step))
        {
            return false;
        }

        // 2.2.获取当前路径数据
        UNIValue* map = current->GetValueBySKey(step);
        if (map != nullptr && map->IsMap())
        {
            // 更新当前路径数据
            current = map->AsMap();

            // 继续下一步
            continue;
        }

        // 2.3.空/不是map
        return false;
    }

    // 未找到数据
    if (current == nullptr)
        return false;

    // 3.设置数据
    // 获取最后一个路径step
    FString step = pathArray.Top();
    if (step.IsEmpty())
        return false;

    // 此路径没有数据
    if (!current->ContainsBySKey(step))
        return false;

    return true;
}

bool UNIUtility::ExpressDelete(const FString& path, UNIMap* dbase)
{
    // 输入参数检测
    if (path.IsEmpty() || dbase == nullptr)
        return false;

    // 路径step
    TArray<FString> pathArray;

    // 1.不包含此路径,解析路径且记录
    if (!mPathSplits.Contains(path))
    {
        // 通过"/"切割路径step
        if (path.ParseIntoArray(pathArray, TEXT("/")) <= 0)
            return false;

        // 记录此路径
        mPathSplits.Emplace(path, pathArray);

        // 容量体积太大了，警告
        if (mPathSplits.Num() >= 1024)
        {
            
        }
    }
    else
        pathArray = mPathSplits[path];

    // 当前路径Map
    UNIMap* current = dbase;

    // 2.追踪到目标路径
    for (int i = 0; i < pathArray.Num() - 1; i++)
    {
        // 当前路径Key
        FString step = pathArray[i];

        // 2.1.没有相应路径数据
        if (!current->ContainsBySKey(step))
            return false;

        // 2.2.获取当前路径数据
        UNIValue* map = current->GetValueBySKey(step);
        if (map != nullptr && map->IsMap())
        {
            // 更新当前路径数据
            current = map->AsMap();

            // 继续下一步
            continue;
        }

        // 2.3.空/不是map
        return false;
    }

    // 未找到数据
    if (current == nullptr)
        return false;

    // 3.设置数据
    // 获取最后一个路径step
    FString step = pathArray.Top();
    if (step.IsEmpty())
        return false;

    // 此路径没有数据
    if (!current->ContainsBySKey(step))
        return false;

    // 删除数据
    return current->RemoveBySKey(step);
}

#pragma endregion

UNIValue* UNIUtility::RestoreArray(FString& content, int32& offset)
{
    int32 length = content.Len();
    UNIArray* arrayValue = UNIValue::CreateArray()->AsArray();

    while (offset < length)
    {
        wchar_t c = content[offset];

        switch (c)
        {
        // 解析别名
        case '@':
            {
                offset++;

                // 还原别名
                UNIValue* value = RestoreAlias(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                arrayValue->Add(value);
            }
            break;
        // String
        case '"':
            {
                offset++;

                // 还原字符串
                UNIValue* value = RestoreString(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                arrayValue->Add(value);
            }
            break;

        // Array
        case '[':
            {
                offset++;

                // 还原Array
                UNIValue* value = RestoreArray(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                arrayValue->Add(value);
            }
            break;

        // Map
        case '{':
            {
                offset++;

                // 还原Map
                UNIValue* value = RestoreMap(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                arrayValue->Add(value);
            }
            break;

        // 数字
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            {
                // 还原数字
                UNIValue* value = RestoreNumber(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                arrayValue->Add(value);
            }
            break;

        case ']':
            {
                offset++;
                return arrayValue;
            }
            break;

        default:
            offset++;
            break;
        }
    }

    return arrayValue;
}

UNIValue* UNIUtility::RestoreMap(FString& content, int32& offset)
{
    int32 length = content.Len();
    UNIMap* mapValue = UNIValue::CreateMap();
    UNIValue* mapKey = nullptr;

    while (offset < length)
    {
        wchar_t c = content[offset];

        switch (c)
        {
        // 以别名为key
        case '@':
            {
                offset++;

                // 解析字符串
                UNIValue* value = RestoreAlias(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                // 跳过空格字符
                SkipSpaceChar(content, offset);

                // 到达了key的标识":"处
                if (CheckKeyCompleted(content, offset))
                {
                    mapKey = value;
                }
                else if (CheckValueCompleted(content, offset))
                {
                    if (mapKey == nullptr)
                        return nullptr;
                    else if (mapKey->IsInt())
                        mapValue->AddByIKey(mapKey->AsInt()->GetValue(), value);
                    else if (mapKey->IsString())
                        mapValue->AddBySKey(mapKey->AsString()->GetValue(), value);
                    else
                    {
                        

                        return nullptr;
                    }
                }
            }
            break;

        // key : String
        case '"':
            {
                offset++;

                // 解析字符串
                UNIValue* value = RestoreString(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                // 跳过空格字符
                SkipSpaceChar(content, offset);

                // 到达了key的标识":"处
                if (CheckKeyCompleted(content, offset))
                {
                    mapKey = value;
                }
                else if (CheckValueCompleted(content, offset))
                {
                    if (mapKey == nullptr)
                        return nullptr;
                    else if (mapKey->IsInt())
                        mapValue->AddByIKey(mapKey->AsInt()->GetValue(), value);
                    else if (mapKey->IsString())
                        mapValue->AddBySKey(mapKey->AsString()->GetValue(), value);
                    else
                    {
                        

                        return nullptr;
                    }
                }
            }
            break;

        // 数字
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            {
                // 还原数字
                UNIValue* value = RestoreNumber(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                // 跳过空格字符
                SkipSpaceChar(content, offset);

                // 到达了key的标识":"处
                if (CheckKeyCompleted(content, offset))
                {
                    mapKey = value;
                }
                else if (CheckValueCompleted(content, offset))
                {
                    if (mapKey == nullptr)
                        return nullptr;
                    else if (mapKey->IsInt())
                        mapValue->AddByIKey(mapKey->AsInt()->GetValue(), value);
                    else if (mapKey->IsString())
                        mapValue->AddBySKey(mapKey->AsString()->GetValue(), value);
                    else
                    {
                       

                        return nullptr;
                    }
                }
            }
            break;

        // Array
        case '[':
            {
                offset++;

                // 还原Array
                UNIValue* value = RestoreArray(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                // 跳过空格字符
                SkipSpaceChar(content, offset);

                // 到达了key的标识":"处
                if (CheckKeyCompleted(content, offset))
                {
                    mapKey = value;
                }
                else if (CheckValueCompleted(content, offset))
                {
                    if (mapKey == nullptr)
                        return nullptr;
                    else if (mapKey->IsInt())
                        mapValue->AddByIKey(mapKey->AsInt()->GetValue(), value);
                    else if (mapKey->IsString())
                        mapValue->AddBySKey(mapKey->AsString()->GetValue(), value);
                    else
                    {
                        

                        return nullptr;
                    }
                }
            }
            break;

        // Map
        case '{':
            {
                offset++;

                // 还原Map
                UNIValue* value = RestoreMap(content, offset);
                if (value == nullptr)
                {
                    return nullptr;
                }

                // 跳过空格字符
                SkipSpaceChar(content, offset);

                // 到达了key的标识":"处
                if (CheckKeyCompleted(content, offset))
                {
                    mapKey = value;
                }
                else if (CheckValueCompleted(content, offset))
                {
                    if (mapKey == nullptr)
                        return nullptr;
                    else if (mapKey->IsInt())
                        mapValue->AddByIKey(mapKey->AsInt()->GetValue(), value);
                    else if (mapKey->IsString())
                        mapValue->AddBySKey(mapKey->AsString()->GetValue(), value);
                    else
                    {
                        

                        return nullptr;
                    }
                }
            }
            break;

        case '}':
            {
                offset++;

                return mapValue;
            }
            break;

        default:
            {
                offset++;
            }
            break;
        }
    }

    return mapValue;
}

UNIValue* UNIUtility::RestoreString(FString& content, int32& offset)
{
    int32 length = content.Len();
    int32 startOffset = offset;
    int32 count = 0;

    // 计算字符串跨度
    while (offset < length)
    {
        wchar_t c = content[offset];
        if (c == '"')
        {
            offset++;

            break;
        }

        offset++;
        count++;
    }

    // 截取字符串
    FString str = content.Mid(startOffset, count);

    return UNIValue::CreateString(str);
}

UNIValue* UNIUtility::RestoreNumber(FString& content, int32& offset)
{
    int32 length = content.Len();
    int32 startOffset = offset;
    bool isFloat = false;
    int32 count = 0;

    // 计算字符串跨度
    while (offset < length)
    {
        wchar_t c = content[offset];

        // 浮点数
        if (c == '.')
        {
            isFloat = true;
        }

        if ((c == '-') || (c == '.') || ((c >= '0') && (c <= '9')))
        {
            offset++;

            count++;

            continue;
        }

        break;
    }

    // 截取字符串
    FString str = content.Mid(startOffset, count);

    // 整数
    int32 value = FCString::Atoi(*str);

    return UNIValue::CreateInt(value);
}

UNIValue* UNIUtility::RestoreAlias(FString& content, int32& offset)
{
    int32 length = content.Len();
    int32 startOffset = offset;
    int32 count = 0;

    // 计算字符串跨度
    while (offset < length)
    {
        wchar_t c = content[offset];

        if ((c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            (c == '(') ||
            (c == ')') ||
            (c == '_'))
        {
            offset++;

            count++;

            continue;
        }

        break;
    }

    // 截取字符串
    FString aliasName = content.Mid(startOffset, count);

    return UNIValue::CreateInt(0);
    
    // 获取别名值
    // int32 aliasValue = UAliasParser::GetAliasValue(aliasName);
    // if (aliasValue < 0)
    // {
    //     
    //
    //     // 这里默认使用string处理
    //     return UNIValue::CreateString("@" + aliasName);
    // }
    //
    // return UNIValue::CreateInt(aliasValue);
}

void UNIUtility::SkipSpaceChar(FString& content, int32& offset)
{
    int32 length = content.Len();

    while (offset < length)
    {
        wchar_t c = content[offset];

        if (c == ' ' || c == '\n' || c == '\r')
        {
            offset++;

            continue;
        }

        break;
    }
}

bool UNIUtility::CheckKeyCompleted(FString& content, int32& offset)
{
    if (content[offset] == ':')
    {
        offset++;

        return true;
    }

    return false;
}

bool UNIUtility::CheckValueCompleted(FString& content, int32& offset)
{
    wchar_t c = content[offset];

    switch (c)
    {
    case ',':
        {
            offset++;
            return true;
        }

    case ']':
    case '}':
        return true;
    }

    return false;
}
