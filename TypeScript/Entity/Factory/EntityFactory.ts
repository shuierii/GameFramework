/*
 * @Author: linb
 * @Date: 2024-04-16 17:09:25
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ObjectPool } from "../../Common/ObjectPool";
import { IComponent } from "../../Interface/IComponent";
import { IEntity } from "../../Interface/IEntity";
import { LogUtility } from "../../Utility/LogUtility";
import { IEntityFactory } from "./IEntityFactory";

export class EntityFactory implements IEntityFactory {

    // <类型，实体class>
    private mEntityClassMap: Map<string, new (...args: any[]) => IEntity> = new Map();

    // <类型，组件class>
    private mComponentClassMap: Map<string, new (...args: any[]) => IComponent> = new Map();

    // 对象池
    private mObjectPool: ObjectPool = new ObjectPool();

    /**
     * @description: 绑定实体
     * @param {string} entityType
     * @param {new} entityClass
     * @return {*}
     */
    BindEntity(entityType: string, entityClass: new (...args: any[]) => IEntity): void {
        if (entityClass == null) {
            LogUtility.Error(`entityType_${entityType} class is null.`);
            return;
        }

        if (this.mEntityClassMap.has(entityType)) {
            LogUtility.Warn(`entityType_${entityType} is exist.`);
            return;
        }

        this.mEntityClassMap.set(entityType, entityClass);
    }

    /**
     * @description: 创建实体对象
     * @param {string} entityType
     * @return {*}
     */
    SpawnEntity(entityType: string): IEntity {
        if (!this.mEntityClassMap.has(entityType)) {
            LogUtility.Error(`entityType_${entityType} is not exist.`);
            return null;
        }

        let entityClass = this.mEntityClassMap.get(entityType);

        // 创建对象
        let entity = this.mObjectPool.Spawn<IEntity>(entityType, entityClass)
        if (entity == null) {
            LogUtility.Error(`entityType_${entityType} spawn failed.`);
            return null;
        }

        return entity;
    }

    /**
     * @description: 回收实体对象
     * @param {string} entityType
     * @param {IEntity} entity
     * @return {*}
     */
    RecycleEntity(entityType: string, entity: IEntity): void {
        if (entity == null)
            return;

        this.mObjectPool.Recycle(entityType, entity);
    }

    /**
     * @description: 绑定组件
     * @param {string} componentType
     * @param {new} componentClass
     * @return {*}
     */
    BindComponent(componentType: string, componentClass: new (...args: any[]) => IComponent): void {
        if (componentClass == null) {
            LogUtility.Error(`componentType_${componentType} class is null.`);
            return;
        }

        if (this.mComponentClassMap.has(componentType)) {
            LogUtility.Warn(`componentType_${componentType} is exist.`);
            return;
        }

        this.mComponentClassMap.set(componentType, componentClass);
    }

    /**
     * @description: 创建组件对象
     * @param {string} componentType
     * @return {*}
     */
    SpawnComponent(componentType: string): IComponent {
        if (!this.mComponentClassMap.has(componentType)) {
            LogUtility.Error(`componentType_${componentType} is not exist.`);
            return null;
        }

        let entityClass = this.mComponentClassMap.get(componentType);

        // 创建对象
        let component = this.mObjectPool.Spawn<IComponent>(componentType, entityClass)
        if (component == null) {
            LogUtility.Error(`componentType_${componentType} spawn failed.`);
            return null;
        }

        return component;
    }

    /**
     * @description: 回收组件对象
     * @param {string} componentType
     * @param {IComponent} component
     * @return {*}
     */
    RecycleComponent(componentType: string, component: IComponent): void {
        if (component == null)
            return;

        this.mObjectPool.Recycle(componentType, component);
    }
}