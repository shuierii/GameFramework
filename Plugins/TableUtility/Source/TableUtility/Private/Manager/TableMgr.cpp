// Copyright HuanMos. All Rights Reserved.

#include "Manager/TableMgr.h"
#include "Table/TableParser.h"

UTableData* UTableMgr::LoadTable(FString tablePath, FString tableName)
{
    if (tablePath.IsEmpty())
        return nullptr;

    // 检测配置表是否存在
    if (!IFileManager::Get().FileExists(*tablePath))
    {
        return nullptr;
    }

    // 加载配置表内容
    TArray<FString> contentList;
    if (!FFileHelper::LoadFileToStringArray(contentList, *tablePath))
    {
        return nullptr;
    }

    // 没有内容的表
    if (contentList.Num() <= 0)
    {
        return nullptr;
    }

    // 构建配置表解析器
    UTableParser* tableParser = NewObject<UTableParser>(this);
    if (tableParser == nullptr)
        return nullptr;

    // 执行解析配置表
    return tableParser->ParseTable(tableName, contentList);
}
