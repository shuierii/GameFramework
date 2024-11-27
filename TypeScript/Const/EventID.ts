/*
 * @Author: linb
 * @Date: 2024-10-31 18:04:28
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

export interface IEvent {

}

export abstract class EventBase implements IEvent {

}

export module Event_Test {
    // 测试事件
    export class EVENT_TEST extends EventBase {
        content: string;
    }
}