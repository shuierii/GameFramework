/*
 * @Author: linb
 * @Date: 2024-04-17 11:30:17
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
import { IEntityData } from "./IEntityData";

export class PlayerData implements IEntityData {
    private mData: object;

    uid: string;
    entity_type: number;
    class_id: number;

    name: string;

    Load(data: object) {
        this.uid = data["uid"];
        this.entity_type = data["entity_type"];
        this.class_id = data["class_id"];

        this.name = data["name"];

        this.mData = data;
    }

    ReadData(key: string): any {
        return this.mData[key];
    }
}