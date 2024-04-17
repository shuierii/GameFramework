/*
 * @Author: linb
 * @Date: 2024-04-17 11:23:45
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IEntityData } from "../../Data/IEntityData";
import { ISystem } from "../../Interface/ISystem";

export interface IPlayerSystem extends ISystem{
    /**
     * @description: 生成数据
     * @param {string} name
     * @return {*}
     */
    GeneratePlayerData(name: string): IEntityData;
}