/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { IEvent } from "../Const/EventID";

export interface ICanRigisterEvent {
    RegisterEvent<TEvent extends IEvent>(listenerID: string, eventClass: new (...args: any[]) => TEvent, handle: (arg?: TEvent) => void): void;

    UnregitsterEvent(listenerID: string): void;
}