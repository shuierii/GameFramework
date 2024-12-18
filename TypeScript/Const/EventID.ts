/*
 * @Author: linb
 * @Date: 2024-10-31 18:04:28
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import { E_IDialog } from "../Event/Node/Implememt/E_IDialog";

export interface IEvent {

}

export abstract class EventBase implements IEvent {

}

export module Event_Test {
    // 测试事件
    export class EVENT_TEST extends EventBase {
        content: string;
    }

    // 触发剧情
    export class EVENT_TRIGGER_DIALOG extends EventBase {

    }

    // 执行对话
    export class EVENT_EXECUTE_TALK extends EventBase {
        dialog: E_IDialog;
    }
}