/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { IEvent } from "../Const/EventID";

export interface ICanTriggerEvent {
    TriggerEvent<TEvent extends IEvent>(eventClass: new (...args: any[]) => TEvent, arg?: TEvent): void;
}