/*
 * @Author: linb
 * @Date: 2024-04-16 14:34:42
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
export interface IEntityData {
    // 唯一ID
    uid: string;

    // 实体类型
    entity_type: number;

    // 该类型下的ID
    class_id: number;

    Load(data: object): void;

    ReadData(key: string): any;
}