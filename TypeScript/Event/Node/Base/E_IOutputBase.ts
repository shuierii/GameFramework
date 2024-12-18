/*
 * @Author: linb
 * @Date: 2024-11-27 16:09:04
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { E_IOutput } from "../Implememt/E_IOutput";
import { E_NodeBase } from "./E_NodeBase";

export abstract class E_IOutputBase extends E_NodeBase implements E_IOutput {

    // 输出器字段
    private mField: string = "";

    protected abstract InitProperty(propertyData: object): void;
    protected abstract OnExecute(): boolean;

    protected OnInit(nodeData: object): void {
        if (nodeData == null)
            return;

        this.mField = nodeData["field"];

        let properties = nodeData["properties"];
        this.InitProperty(properties);
    }

    protected OnReset(): void {
        this.mField = "";
    }

    GetField(): string {
        return this.mField;
    }

    /**
     * @description: 执行
     * @return {*}
     */
    Execute(): boolean {
        return this.OnExecute();
    }
}