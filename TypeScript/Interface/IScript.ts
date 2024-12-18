import { IRecycable } from "./IRecycable";

/*
 * @Author: linb
 * @Date: 2024-04-15 11:32:45
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
export interface IScript extends IRecycable {
    Execute(params?: any[]): any;
}