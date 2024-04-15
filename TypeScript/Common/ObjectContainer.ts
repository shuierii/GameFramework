/*
 * @Author: linb
 * @Date: 2024-04-15 16:29:51
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */

export class ObjectContainer {

    // <对象ID，对象实例>
    private mObjMap: Map<number, object> = new Map();

    /**
     * @description: 注册实例对象
     * @param {number} objID
     * @param {TObject} obj
     * @return {*}
     */
    Register<TObject extends Object>(objID: number, obj: TObject): boolean {
        if (obj == null)
            return false;

        this.mObjMap.set(objID, obj);

        return true;
    }

    /**
     * @description: 获取实例对象
     * @param {number} objID
     * @return {*}
     */
    Get<TObject extends Object>(objID: number): TObject {
        if (this.mObjMap.has(objID))
            return null;

        return this.mObjMap.get(objID) as TObject;
    }

    /**
     * @description: 包含实例对象
     * @param {number} objID
     * @return {*}
     */
    Contain(objID: number): boolean {
        return this.mObjMap.has(objID);
    }

    /**
     * @description: 清理
     * @return {*}
     */
    Clear(): void {
        this.mObjMap.clear();
    }
}