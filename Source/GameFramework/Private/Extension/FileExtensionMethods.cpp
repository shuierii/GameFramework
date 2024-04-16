// Copyright HuanMos. All Rights Reserved.

#include "Extension/FileExtensionMethods.h"
#include "Serialization/BufferArchive.h"

void UFileExtensionMethods::FindFiles(TArray<FString>& fileNames, const FString& findExtension, bool isFiles, bool isDirectory)
{
	IFileManager::Get().FindFiles(fileNames, *findExtension, isFiles, isDirectory);
}

FString UFileExtensionMethods::LoadFileToString(const FString& filePath)
{
	FString result;
	if (!FFileHelper::LoadFileToString(result, *filePath))
	{
		UE_LOG(LogTemp, Error, TEXT("The load filePath(%s) is faild"), *filePath);

		return "";
	}

	return result;
}
