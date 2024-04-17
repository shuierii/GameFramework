/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { IEntityData } from "../Data/IEntityData";
import { IElement } from "./IElement";
import { IRecycable } from "./IRecycable";
import { IReleasable } from "./IReleasable";

export interface IEntity extends IReleasable, IRecycable, IElement {

    /**
     * @description: 初始化数据
     * @param {IEntityData} entityData
     * @return {*}
     */
    Init(entityData: IEntityData): void

    /**
     * @description: 获取UID
     * @return {*}
     */
    GetUID(): string;

    /**
     * @description: 获取ClassID
     * @return {*}
     */
    GetClassID(): number;

    /**
     * @description: 获取实体类型
     * @return {*}
     */
    GetEntityType(): number;

    /**
     * @description: 读取实体数据
     * @param {string} key
     * @return {*}
     */
    ReadData(key: string): any;
}