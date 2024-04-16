/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

export interface ICanRigisterEvent {
    RegisterEvent(listenerID: string, eventID: string, handle: (args?: any[]) => void): void;

    UnregitsterEvent(listenerID: string): void;
}