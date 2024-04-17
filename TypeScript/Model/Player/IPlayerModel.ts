/*
 * @Author: linb
 * @Date: 2024-04-17 14:34:07
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import * as UE from "ue";
import { IModel } from "../../Interface/IModel";

export interface IPlayerModel extends IModel {
    /**
     * @description: 根据ID获取配置行数据
     * @param {number} classID
     * @return {*}
     */
    GetPlayerRow(classID: number): UE.RowData;
}