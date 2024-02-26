/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-25 23:19:10
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-31 16:09:35
 */

import java.math.BigInteger;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Lesson5Question3 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String loc = scanner.nextLine();
        BigInteger OperationNum = scanner.nextBigInteger();
        scanner.close();

        BigInteger result = Operation(loc, OperationNum);
        System.out.println(result);
    }

    private static BigInteger Operation(String str, BigInteger OperationNum)
    {
        BigInteger Result = BigInteger.valueOf(0);
        String[] string = str.split("(?=[+-])");
        Pattern patternNoIndex = Pattern.compile("^([+|-])?(\\d*)x$");
        Pattern patternIndex = Pattern.compile("^([+|-])?(\\d*)x\\^(\\d+)$");
        Pattern patternNum = Pattern.compile(   "^([+|-])?(\\d*)$");
        for (String s : string)
        {
            if (patternNum.matcher(s).matches())
            {
                continue;
            }
            else if (patternNoIndex.matcher(s).matches())
            {
                Pattern number = Pattern.compile("([+|-])?(\\d+)(?=[x])");
                Matcher matcher = number.matcher(s);
                if (matcher.find())
                {
                    BigInteger Num = new BigInteger(matcher.group(0));
                    Result = Result.add(Num);
                }
                else
                {
                    if (s.charAt(0) == '-')
                    {
                        Result.subtract(BigInteger.valueOf(1));
                    }
                    else
                    {
                        Result.add(BigInteger.valueOf(1));
                    }
                }
                
            }
            else if (patternIndex.matcher(s).matches())
            {
                Pattern number = Pattern.compile("([+|-]?\\d+)(x\\^(\\d+))");
                Matcher matcher = number.matcher(s);
                if (matcher.find())
                { 
                    BigInteger num = new BigInteger(matcher.group(1));
                    int index = Integer.parseInt(matcher.group(3));
                    Result = Result.add((num.multiply(BigInteger.valueOf(index))).multiply(OperationNum.pow(index-1)));
                }
                else
                {
                    if (s.charAt(0) == '-')
                    {
                        int index = Integer.parseInt(s.substring(3));
                        Result = Result.subtract(BigInteger.valueOf(index).multiply(OperationNum.pow(index-1)));
                    }
                    else if (s.charAt(0) == '+')
                    {
                        int index = Integer.parseInt(s.substring(3));
                        Result = Result.add(BigInteger.valueOf(index).multiply(OperationNum.pow(index-1)));
                    }
                    else
                    {
                        int index = Integer.parseInt(s.substring(2));
                        Result = Result.add(BigInteger.valueOf(index).multiply(OperationNum.pow(index-1)));
                    }
                }
            }
        }
        return Result;
    }
}