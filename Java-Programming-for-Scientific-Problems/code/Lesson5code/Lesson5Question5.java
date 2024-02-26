/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-25 20:43:48
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-25 23:18:30
 */

import java.math.BigInteger;
import java.util.Scanner;

public class Lesson5Question5 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        BigInteger number = scanner.nextBigInteger();
        int p = scanner.nextInt();
        scanner.close();

        BigInteger loc = number;

        StringBuffer Bite = new StringBuffer();
        while (number.compareTo(BigInteger.valueOf(0)) > 0)
        {
            Bite.append(number.mod(BigInteger.valueOf(10)));
            number = number.divide(BigInteger.valueOf(10));
        }

        Bite.reverse();
        BigInteger result = BigInteger.valueOf(0);
        for (int i = p; Bite.length() > 0; i++)
        {
            result = result.add(BigInteger.valueOf((int)Math.pow(Bite.charAt(0) - '0', i)));
            Bite.deleteCharAt(0);
        }

        BigInteger a = result.mod(loc);
        if (a.equals(BigInteger.valueOf(0)))
        {
            System.out.println(result.divide(loc));
        }
        else
        {
            System.out.println(-1);
        }
    }
}