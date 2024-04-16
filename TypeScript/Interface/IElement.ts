/*
 * @Author: linb
 * @Date: 2024-04-16 15:22:51
 * @Description: 包含基础功能的框架接口
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { ICanGetModel } from "./ICanGetModel";
import { ICanGetSystem } from "./ICanGetSystem";
import { ICanRigisterEvent } from "./ICanRigisterEvent";
import { ICanSendScript } from "./ICanSendScript";
import { ICanTriggerEvent } from "./ICanTriggerEvent";

export interface IElement extends ICanGetSystem, ICanGetModel, ICanTriggerEvent, ICanRigisterEvent, ICanSendScript {

}