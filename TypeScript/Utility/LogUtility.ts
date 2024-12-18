/*
 * @Author: linb
 * @Date: 2024-10-31 18:04:28
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

import * as UE from "ue";
import { MainGame } from "../MainGame";

export class LogUtility {

    private static title: string = " [Framework Project] ";

    static Log(...data: any[]): void {
        console.log(`${this.title}` + data);
    }

    static Warn(...data: any[]): void {
        console.warn(`${this.title}` + data + `[${this.GetCallLineInfo()}]`);
    }

    static Error(...data: any[]): void {
        console.error(`${this.title}` + data + `[${this.GetCallLineInfo()}]`);
    }

    static Info(...data: any[]): void {
        UE.KismetSystemLibrary.PrintString(MainGame.UEInstance, `${data}`, true, true, new UE.LinearColor(0, 1, 0, 1), 5);
    }

    /**
     * @description: 获取调用行信息
     * @param {*}
     * @return {*}
     */
    private static GetCallLineInfo(needStack = false): string {
        // 构建Error
        let errorObj = new Error();
        if (errorObj == null) {
            return "";
        }

        // 通过\n截取stack数据
        let stackList = errorObj.stack.split("\n");
        if (stackList.length < 4) {
            return "";
        }

        if (needStack) {
            stackList.splice(0, 3)
            return stackList.join("\n");
        }

        // 获取stack调用行信息
        let stackLine = stackList[3];

        // 获取调用行信息
        return stackLine.slice(stackLine.lastIndexOf("(") + 1, stackLine.lastIndexOf(")"));
    }
}