/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IModel } from "./IModel";

export interface ICanGetModel {
    GetModel<TModel extends IModel>(modelID: number): TModel;
}