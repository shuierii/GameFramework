/*
 * @Author: linb
 * @Date: 2024-04-15 17:39:41
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IInitable } from "./IInitable";
import { IRecycable } from "./IRecycable";
import { IReleasable } from "./IReleasable";

export interface IComponent extends IInitable, IReleasable, IRecycable {

}