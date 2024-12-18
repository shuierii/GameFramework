/*
 * @Author: linb
 * @Date: 2024-11-01 15:46:26
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { IModel } from "../../Interface/IModel";

export interface IEventModel extends IModel {
    /**
     * @description: 事件数据
     * @return {*}
     */
    GetEventDataMap(): Map<string, object>;
}