/*
 * @Author: linb
 * @Date: 2024-04-12 10:37:54
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ICanGetModel } from "./ICanGetModel";
import { ICanGetSystem } from "./ICanGetSystem";
import { ICanRigisterEvent } from "./ICanRigisterEvent";
import { ICanTriggerEvent } from "./ICanTriggerEvent";
import { IInitable } from "./IInitable";
import { IReleasable } from "./IReleasable";

export interface ISystem extends IInitable, IReleasable, ICanGetSystem, ICanGetModel, ICanRigisterEvent, ICanTriggerEvent {

}