/*
 * @Author: linb
 * @Date: 2024-04-16 14:31:19
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IEntityData } from "../../Data/IEntityData";
import { IEntityFactory } from "../../Entity/Factory/IEntityFactory";
import { IEntity } from "../../Interface/IEntity";
import { ISystem } from "../../Interface/ISystem";
import { IEntityTemplate } from "../../Model/Entity/EntityModel";

export interface IEntitySystem extends ISystem {

    // 实体工厂
    mEntityFactory: IEntityFactory;

    /**
     * @description: 创建实体
     * @param {IEntityData} entityData
     * @return {*}
     */
    CreateEntity(entityData: IEntityData): IEntity;

    /**
     * @description: 获取实体模板
     * @param {number} entityType
     * @return {*}
     */
    GetEntityTemplate(entityType: number): IEntityTemplate;
}