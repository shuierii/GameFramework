/*
 * @Author: linb
 * @Date: 2024-04-15 18:03:00
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ElementBase } from "../Abstract/ElementBase";
import { SystemID } from "../Const/SystemID";
import { IEntityData } from "../Data/IEntityData";
import { IComponent } from "../Interface/IComponent";
import { IEntity } from "../Interface/IEntity";
import { IEntitySystem } from "../System/Entity/IEntitySystem";
import { LogUtility } from "../Utility/LogUtility";

export class Entity extends ElementBase implements IEntity {
    // 对象类型
    mType: string;

    // 唯一ID
    private mUID: string;

    private mEntityType: number;

    private mClassID: number;

    // <组件类型，组件对象>
    private mComponentMap: Map<string, IComponent> = new Map();

    private mEntityData: IEntityData;

    /**
     * @description: 初始化数据
     * @param {IEntityData} entityData
     * @return {*}
     */
    Init(entityData: IEntityData): void {
        if (entityData == null) {
            LogUtility.Error(`the entityData is null.`);

            return null;
        }

        // 1.数据
        this.mUID = entityData.uid;
        this.mEntityType = entityData.entity_type;
        this.mClassID = entityData.class_id;

        this.mEntityData = entityData;

        let entitySys = this.GetSystem<IEntitySystem>(SystemID.ENTITY_SYSTEM);

        // 2.组件
        let entityTemplate = entitySys.GetEntityTemplate(this.mEntityType);
        if (entityTemplate == null) {
            LogUtility.Error(`the entityTemplate is null.`);

            return null;
        }

        let entityFactory = entitySys.mEntityFactory;
        for (const componentType of entityTemplate.components) {
            if (this.mComponentMap.has(componentType))
                continue;

            // 创建组件对象
            let component = entityFactory.SpawnComponent(componentType);
            if (component == null) {
                LogUtility.Error(`the componentType_${componentType} spawn failed.`);

                continue;
            }

            // 组件初始化流程
            component.Init();

            this.mComponentMap.set(componentType, component);
        }
    }

    Release(): void {

    }

    Reset(): void {
        this.mUID = "";
        this.mEntityType = 0;
        this.mClassID = 0;
    }

    /**
     * @description: 获取UID
     * @return {*}
     */
    GetUID(): string {
        return this.mUID;
    }

    /**
     * @description: 获取ClassID
     * @return {*}
     */
    GetClassID(): number {
        return this.mClassID;
    }

    /**
     * @description: 获取实体类型
     * @return {*}
     */
    GetEntityType(): number {
        return this.mEntityType;
    }

    /**
     * @description: 读取实体数据
     * @param {string} key
     * @return {*}
     */
    ReadData(key: string): any {
        return this.mEntityData.ReadData(key);
    }
}