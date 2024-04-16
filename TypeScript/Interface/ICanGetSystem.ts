/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ISystem } from "./ISystem";

export interface ICanGetSystem {
    GetSystem<TSystem extends ISystem>(systemID: number): TSystem;
}