/*
 * @Author: linb
 * @Date: 2024-11-01 15:46:17
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { $ref, $unref } from "puerts";
import * as UE from "ue";
import { ModelBase } from "../../Abstract/ModelBase";
import { ModelID } from "../../Const/ModelID";
import { LogUtility } from "../../Utility/LogUtility";
import { IEventModel } from "./IEventModel";

export class EventModel extends ModelBase implements IEventModel {
    // 事件数据映射 <事件id，事件数据>
    private mEventDataMap: Map<string, object> = new Map();

    protected GetModelID(): number {
        return ModelID.EVENT_MODEL;
    }

    protected OnInit(): void {
        this.LoadEventData();
    }

    protected OnRelease(): void {
        this.mEventDataMap.clear();
    }

    /**
     * @description: 事件数据
     * @return {*}
     */
    GetEventDataMap(): Map<string, object> {
        return this.mEventDataMap;
    }

    /**
     * @description: 加载事件数据
     * @return {*}
     */
    private LoadEventData(): void {
        // 项目根目录
        let rootPath = UE.BlueprintPathsLibrary.ProjectContentDir();

        // 文件目录路径
        let fileDirectoryPath = rootPath + "Etc/Event/";

        // 文件名
        let fileNamesRef = $ref(UE.NewArray(UE.BuiltinString)); // 创建列表引用

        // 获取目录下所有的json文件
        UE.FileExtensionMethods.FindFiles(fileNamesRef, fileDirectoryPath + "*.json", true, false); // C++中的接口表现为 IFileManager::Get().FindFiles(TArray<FString>& FileNames, const TCHAR* Filename, bool Files, bool Directories)

        // 解引用
        let fileNames = $unref(fileNamesRef);

        if (fileNames.Num() <= 0)
            return;

        // 对json数据进行解析并映射
        for (let i = 0; i < fileNames.Num(); i++) {
            let fileName = fileNames.Get(i);
            let filePath = fileDirectoryPath + fileName;

            // 加载文件内容
            let fileContent = UE.FileExtensionMethods.LoadFileToString(filePath);   // C++中的接口表现为 FFileHelper::LoadFileToString(FString& Result, const TCHAR* Filename)
            if (fileContent.length <= 0)
                continue;

            // 解析
            let eventData = this.ParseEventData(fileContent);
            if (eventData == null)
                continue;

            let eventId = eventData["id"];
            fileName = fileName.replace(".json", "");
            eventData["name"] = fileName;

            if (this.mEventDataMap.has(eventId))
                continue;

            this.mEventDataMap.set(eventId, eventData);

            LogUtility.Log(`${fileName}内容：\n ${JSON.stringify(eventData)}`);
        }
    }

    /**
     * @description: 事件数据解析
     * @param {string} fileContent
     * @return {*}
     */
    private ParseEventData(fileContent: string): object {
        let eventData: object = null;
        try {
            eventData = JSON.parse(fileContent);
        } catch (error) {
            LogUtility.Error("解析失败");
        }

        return eventData;
    }
}