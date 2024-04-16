import { IComponent } from "../../Interface/IComponent";
import { IEntity } from "../../Interface/IEntity";

/*
 * @Author: linb
 * @Date: 2024-04-16 17:09:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
export interface IEntityFactory {
    /**
     * @description: 绑定实体
     * @param {string} entityType
     * @param {new} entityClass
     * @return {*}
     */
    BindEntity(entityType: string, entityClass: new (...args: any[]) => IEntity): void;

    /**
     * @description: 创建实体对象
     * @param {string} entityType
     * @return {*}
     */
    SpawnEntity(entityType: string): IEntity;

    /**
     * @description: 回收实体对象
     * @param {string} entityType
     * @param {IEntity} entity
     * @return {*}
     */
    RecycleEntity(entityType: string, entity: IEntity): void;

    /**
     * @description: 绑定组件
     * @param {string} componentType
     * @param {new} componentClass
     * @return {*}
     */
    BindComponent(componentType: string, componentClass: new (...args: any[]) => IComponent): void;

    /**
     * @description: 创建组件对象
     * @param {string} componentType
     * @return {*}
     */
    SpawnComponent(componentType: string): IComponent;

    /**
     * @description: 回收组件对象
     * @param {string} componentType
     * @param {IComponent} component
     * @return {*}
     */
    RecycleComponent(componentType: string, component: IComponent): void;
}