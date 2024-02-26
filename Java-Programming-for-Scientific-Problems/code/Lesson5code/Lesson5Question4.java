/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-25 15:51:35
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-25 20:35:10
 */

import java.util.Scanner;

public class Lesson5Question4 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String loc = scanner.nextLine();
        StringBuffer m = new StringBuffer(loc);
        loc = scanner.nextLine();
        StringBuffer n = new StringBuffer(loc);
        scanner.close();

        StringBuffer result = new StringBuffer();

        m.reverse();
        n.reverse();
        
        int carrybite = 0;
        while ((m.length() > 0) && (n.length() > 0))
        {
            int LocNumBite = m.charAt(0) - '0' + n.charAt(0) - '0' + carrybite;
            if (LocNumBite >= 10)
            {
                carrybite = 1;
                LocNumBite -= 10;
            }
            else
            {
                carrybite = 0;
            }
            result.append(LocNumBite);
            m.deleteCharAt(0);
            n.deleteCharAt(0);
        }

        while (m.length() > 0)
        {
            int LocNumBite = m.charAt(0) - '0' + carrybite;
            if (LocNumBite >= 10)
            {
                carrybite = 1;
                LocNumBite -= 10;
            }
            else
            {
                carrybite = 0;
            }
            result.append(LocNumBite);
            m.deleteCharAt(0);
        }

        while (n.length() > 0)
        {
            int LocNumBite = n.charAt(0) - '0' + carrybite;
            if (LocNumBite >= 10)
            {
                carrybite = 1;
                LocNumBite -= 10;
            }
            else
            {
                carrybite = 0;
            }
            result.append(LocNumBite);
            n.deleteCharAt(0);
        }

        if (carrybite == 1)
        {
            result.append(carrybite);
        }
        
        result.reverse();

        while (result.charAt(0) == '0')
        {
            result.deleteCharAt(0);
        }

        System.out.println(result);
    }
}