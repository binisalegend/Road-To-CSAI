/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-25 15:45:18
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-25 15:51:26
 */

import java.math.BigInteger;
import java.util.Scanner;

public class Lesson5Question2 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.close();

        BigInteger result = BigInteger.valueOf(1);
        for (int i = 1; i <= n; i++)
        {
            result = result.multiply(BigInteger.valueOf(i));
        }

        System.out.println(result);
    }
}