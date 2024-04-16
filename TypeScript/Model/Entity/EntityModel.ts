/*
 * @Author: linb
 * @Date: 2024-04-15 18:28:32
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { $ref, $unref } from "puerts";
import { ModelBase } from "../../Abstract/ModelBase";
import { ModelID } from "../../Const/ModelID";
import { LogUtility } from "../../Utility/LogUtility";
import { IEntityModel } from "./IEntityModel";

export interface IEntityTemplate {
    name: string;
    components: Array<string>;
}

export class EntityModel extends ModelBase implements IEntityModel {

    // <模板名称，模板>
    private mEntityTemplateMap: Map<string, IEntityTemplate> = new Map();

    protected GetModelID(): number {
        return ModelID.ENTITY_MODEL;
    }

    protected OnInit(): void {
        // 加载实体组件模板
        this.LoadEntityTemplate();
    }

    protected OnRelease(): void {

    }

    /**
     * @description: 获取实体模板
     * @param {string} name
     * @return {*}
     */
    GetEntityTemplate(name: string): IEntityTemplate {
        if (!this.mEntityTemplateMap.has(name))
            return null;

        return this.mEntityTemplateMap.get(name);
    }

    /**
     * @description: 加载所有实体模板
     * @return {*}
     */
    private LoadEntityTemplate(): void {
        // 文件目录路径
        let fileDirPath = UE.BlueprintPathsLibrary.ProjectContentDir() + "Etc/EntityTemplate/";

        // 文件名列表引用
        let refFilenames = $ref(UE.NewArray(UE.BuiltinString));

        // 查找所有文件 FileManager->FindFiles()
        // 由于 FileManager 没有映射，需在C++代码中写一个中间件扩展
        UE.FileExtensionMethods.FindFiles(refFilenames, fileDirPath + "*.json", true, false);

        // 解引用
        let filenames = $unref(refFilenames);

        if (filenames == null || filenames.Num() < 0) {
            LogUtility.Error(`the path ${fileDirPath} not exsit files.`);
            return;
        }

        // 遍历
        for (let index = 0; index < filenames.Num(); index++) {
            // 文件名
            let fileName = filenames.Get(index);

            // 文件路径
            let filePath = fileDirPath + fileName;

            // 加载文件内容
            let content = UE.FileExtensionMethods.LoadFileToString(filePath);
            if (content.length <= 0) {
                LogUtility.Error(`the file(${fileName}) content is empty.`)
                continue;
            }

            // 解析json
            let entityTemplate: IEntityTemplate = null;
            try {
                entityTemplate = JSON.parse(content);
            } catch (error) {
                LogUtility.Error(error);
                continue;
            }

            if (entityTemplate == null) {
                LogUtility.Error(`the file(${fileName}) parse is fail.`);
                continue;
            }

            if (this.mEntityTemplateMap.has(entityTemplate.name))
                continue;

            this.mEntityTemplateMap.set(entityTemplate.name, entityTemplate);
        }
    }
}