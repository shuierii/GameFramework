/*
 * @Author: linb
 * @Date: 2024-04-16 14:31:07
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { SystemBase } from "../../Abstract/SystemBase";
import { CommonEnum } from "../../Const/CommonEnum";
import { ComponentType } from "../../Const/ComponentType";
import { EntityType } from "../../Const/EntityType";
import { ModelID } from "../../Const/ModelID";
import { SystemID } from "../../Const/SystemID";
import { IEntityData } from "../../Data/IEntityData";
import { CharacterMovement } from "../../Entity/Component/CharacterMovement";
import { Entity } from "../../Entity/Entity";
import { IEntityFactory } from "../../Entity/Factory/IEntityFactory";
import { EntityFactory } from "../../Entity/Factory/EntityFactory";
import { IEntity } from "../../Interface/IEntity";
import { IEntityTemplate } from "../../Model/Entity/EntityModel";
import { IEntityModel } from "../../Model/Entity/IEntityModel";
import { LogUtility } from "../../Utility/LogUtility";
import { IEntitySystem } from "./IEntitySystem";

export class EntitySystem extends SystemBase implements IEntitySystem {

    // 实体工厂
    mEntityFactory: IEntityFactory;

    protected GetSystemID(): number {
        return SystemID.ENTITY_SYSTEM;
    }

    protected OnInit(): void {
        this.mEntityFactory = new EntityFactory();

        // 绑定实体
        this.mEntityFactory.BindEntity(EntityType.ENTITY, Entity);

        // 绑定组件
        this.mEntityFactory.BindComponent(ComponentType.CHARACTER_MOVEMENT, CharacterMovement)
    }

    protected OnRelease(): void {

    }

    /**
     * @description: 创建实体
     * @param {IEntityData} entityData
     * @return {*}
     */
    CreateEntity(entityData: IEntityData): IEntity {
        if (entityData == null) {
            LogUtility.Error(`the entityData is null.`)

            return null;
        }

        // 创建对象
        let entity = this.mEntityFactory.SpawnEntity(EntityType.ENTITY);
        if (entity == null) {
            LogUtility.Error(`the entity(${entityData.class_id}) spawn entity is fail.`);
            return null;
        }

        // 初始化实体流程
        entity.Init(entityData);

        return entity;
    }

    /**
     * @description: 获取实体模板
     * @param {number} entityType
     * @return {*}
     */
    GetEntityTemplate(entityType: number): IEntityTemplate {
        let entityModel = this.GetModel<IEntityModel>(ModelID.ENTITY_MODEL);

        switch (entityType) {
            case CommonEnum.EntityType.NPC:
                return entityModel.GetEntityTemplate("npc");
        }
    }
}