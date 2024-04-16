// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExtensionMethods.h"
#include "FileExtensionMethods.generated.h"

/// <summary>
/// File扩展方法
/// </summary>
UCLASS(BlueprintType)
class GAMEFRAMEWORK_API UFileExtensionMethods : public UExtensionMethods
{
    GENERATED_BODY()

public:
    /// <summary>
    /// 查找指定类型文件/文件夹
    /// eg:
    ///     1.查找指定类型文件:
    ///           findExtension: "../../Content/Resources/ActionSet/*.json"
    ///           isFiles: true
    ///           isDirectory: false
    ///
    ///     2.查询指定目录下文件夹:
    ///           findExtension: "../../Content/Resources/*"
    ///           isFiles: false
    ///           isDirectory: true
    /// </summary>
    /// <param name="fileNames">文件/文件夹名列表</param>
    /// <param name="findExtension">查找过滤规则/</param>
    /// <param name="isFiles">是否查找文件</param>
    /// <param name="isDirectory">是否查找文件夹</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = FileExtensionMethods)
    static void FindFiles(TArray<FString>& fileNames, const FString& findExtension, bool isFiles, bool isDirectory);

    UFUNCTION(BlueprintCallable, Category = FileExtensionMethods)
    static FString LoadFileToString(const FString& filePath);
};
