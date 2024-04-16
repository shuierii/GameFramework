/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

export interface ICanTriggerEvent {
    TriggerEvent(eventID: string, args?: any[]): void;
}