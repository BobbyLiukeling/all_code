import javax.swing.plaf.basic.BasicComboPopup;

/**
 * Filename:CheckEmile title:数据数组操作
 * 
 * @date 创建时间：2017年12月23日 下午7:15:43
 * @version 1.0
 * @parameter charAt(),indexOf(),substring() Description:一维数组和多维数组的操作
 * @author Liu Keling 作者 E-mail: 1194380923@qq.com
 */
public class CheckEmile {
	char[] cNum = { '1', '2', '3', '4', '5', '6', '8', '9', '0' };
	char[] cStr = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
			'u', 'v', 'w', 'x', 'y', 'z' };
	int[] iMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	String[] sMail = { "@", "." };

	/**
	 * 校验电子邮件
	 */
	public boolean isMail(String sPara) {
		for (int i = 0; i < sMail.length; i++) {
			if (sPara.indexOf(sMail[i]) == -1) {// 搜索sMail[i]在SPara中的位置，如果没有找到就返回-1
				return false;
			}
		}
		return true;
	}

	/**
	 * 判断是否为数字
	 */
	public boolean isNumber(String sPara) {
		int iPLength = sPara.length();
		int key = 0;
		int i = 0;
		for (; i < iPLength; i++) {
			char cTemp = sPara.charAt(i);

			for (int j = 0; j < cNum.length; j++) {
				if (cTemp == cNum[j]) {
					key++;
					break;
				}
			}
		}
		if (key == i)
			return true;
		else
			return false;
	}

	/**
	 * 判断是否都为英文字符
	 */

	public boolean isString(String sPara) {
		int iPLength = sPara.length();
		for (int i = 0; i < iPLength; i++) {
			char cTemp = sPara.charAt(i);// SPara.charAt(i)得到SPara的第i个元素
			boolean bTemp = false;
			for (int j = 0; j < cStr.length; j++) {
				if (cTemp == cStr[j]) {
					bTemp = true;
					break;
				}
			}
			if (!bTemp)
				return false;
		}
		return true;
	}

	/**
	 * 判断是否为闰年
	 */
	public boolean chickDay(int iPara) {
		return iPara % 100 == 0 && iPara % 4 == 0;
	}

	/**
	 * 检查日期是否正确
	 * 
	 * @param sPara
	 * @return
	 */
	public int chickDate(String sPara) {
		boolean bTemp = false;
		// 确定输入的日期的长度
		if (sPara.length() != 10) {
			return -2;
		}
		// 获取年
		String sYear = sPara.substring(0, 4);
		// 判断年是否为数字
		if (!isNumber(sYear)) {
			return -2;
		}
		// 获取月份
		String sMonth = sPara.substring(5, 7);
		// 判断月份是否为数字
		if (!isNumber(sMonth)) {
			return -2;
		}
		// 获取日期
		String sDate = sPara.substring(8, 10);
		// 判断日期是否为数字
		if (!isNumber(sDate)) {
			return -2;
		}
		int iYear = Integer.parseInt(sYear);
		int iMon = Integer.parseInt(sMonth);
		int iDate = Integer.parseInt(sDate);
		if (iMon > 12) {
			return -1;
		}
		// 闰二月
		if (iMon == 2 && chickDay(iYear)) {
			if (iDate > 29) {
				return 2;
			} else {
				if (iDate > iMonth[iMon - 1]) {
					return -1;
				}
			}

		}
		return 0;
	}

	/**
	 * 主方法
	 * 
	 * @param args
	 */

	public static void main(String[] args) {
		CheckEmile check = new CheckEmile();
		boolean bMail = check.isMail("tom@163.com");
		System.out.println("1 bMail is:" + bMail);

		// 演示是否是数字
		boolean bIsNum = check.isNumber("12354");
		System.out.println("bIsNum:" + bIsNum);

		// 演示是否是英文字符
		boolean bisStr = check.isString("liukeling");
		System.out.println("bIsStr:" + bisStr);

		// 演示检查日期
		int iIsTime = check.chickDate("2017-12-24");
		System.out.println("iIstime:" + iIsTime);

	}

}
