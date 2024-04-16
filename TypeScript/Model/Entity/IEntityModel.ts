/*
 * @Author: linb
 * @Date: 2024-04-16 12:30:10
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IModel } from "../../Interface/IModel";
import { IEntityTemplate } from "./EntityModel";

export interface IEntityModel extends IModel {
    /**
     * @description: 获取实体模板
     * @param {string} name
     * @return {*}
     */
    GetEntityTemplate(name: string): IEntityTemplate;
}