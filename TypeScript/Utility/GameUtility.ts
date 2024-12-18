/*
 * @Author: linb
 * @Date: 2024-11-28 17:44:56
 * @Description:
 * @Copyright: Copyright HuanMos. All Rights Reserved.
 */
export class GameUtility {

    private static mCookieIndex: number = 0;

    /**
     * @description: 生成Cookie
     * @param {string} prefix
     * @return {*}
     */
    static CreateCookie(prefix: string): string {
        return prefix + "_" + this.mCookieIndex++;
    }
}