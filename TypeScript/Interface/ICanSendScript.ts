/*
 * @Author: linb
 * @Date: 2024-04-15 18:11:05
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
export interface ICanSendScript {
    SendScript(ScriptID: string, params?: any[]): any;
}