/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-25 02:24:59
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-26 00:11:30
 */
import java.math.BigInteger;
import java.util.Scanner;

public class Lesson5Question1 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        BigInteger n = scanner.nextBigInteger();
        scanner.close();

        System.out.println(foo(n));
    }
    
    private static BigInteger JudgeConverting(BigInteger n)
    {
        BigInteger loc = (n.subtract(BigInteger.valueOf(1))).divide(BigInteger.valueOf(2));
        if ((loc.mod(BigInteger.valueOf(2))).equals(BigInteger.valueOf(1)))
        {
            BigInteger Odd = loc;
            BigInteger Even = Odd.add(BigInteger.valueOf(1));
            return F(BigInteger.valueOf(1), BigInteger.valueOf(1), Odd, Even);
        }
        else
        {
            BigInteger Even = loc;
            BigInteger Odd = Even.add(BigInteger.valueOf(1));
            return F(BigInteger.valueOf(1), BigInteger.valueOf(1), Odd, Even);
        }
    }
    // foo(0) = 0
    // foo(1) = 1
    // foo(2n+1) = foo(n) + foo(n+1)
    // foo(2n) = foo(n)

    public static BigInteger foo(BigInteger n)
    {
        if (n.mod(BigInteger.valueOf(2)).equals(BigInteger.valueOf(1)))
        {          
            return JudgeConverting(n);
        }
        
        while((n.mod(BigInteger.valueOf(2)).equals(BigInteger.valueOf(0))))
        {
            n = n.divide(BigInteger.valueOf(2));
        }
        
        return JudgeConverting(n);
    }

    private static BigInteger F(BigInteger a, BigInteger b, BigInteger c, BigInteger d)
    {
        BigInteger NumOfOdd = a, NumOfEven = b, Odd = c, Even = d;

        while (!Odd.equals(BigInteger.valueOf(1)))
        {
            BigInteger loc = BigInteger.valueOf(0);
            if (Odd.compareTo(Even) == 1)
            {
                if (((Even.divide(BigInteger.valueOf(2))).mod(BigInteger.valueOf(2))).equals(BigInteger.valueOf(1)))
                {
                    loc = NumOfEven;
                    NumOfEven = NumOfOdd;
                    NumOfOdd = NumOfOdd.add(loc);
                    Odd = Even.divide(BigInteger.valueOf(2));
                    Even = Odd.add(BigInteger.valueOf(1));
                }                
                else
                {
                    loc = NumOfEven;
                    NumOfEven = NumOfEven.add(NumOfOdd);
                    Even = Even.divide(BigInteger.valueOf(2));
                    Odd = Even.add(BigInteger.valueOf(1));
                }
            }
            else
            {
                if (((Even.divide(BigInteger.valueOf(2))).mod(BigInteger.valueOf(2))).equals(BigInteger.valueOf(1)))
                {
                    loc = NumOfEven;
                    NumOfEven = NumOfOdd;
                    NumOfOdd = NumOfOdd.add(loc);
                    Odd = Even.divide(BigInteger.valueOf(2));
                    Even = Odd.subtract(BigInteger.valueOf(1));
                }                
                else
                {
                    loc = NumOfEven;
                    NumOfEven = NumOfEven.add(NumOfOdd);
                    Even = Even.divide(BigInteger.valueOf(2));
                    Odd = Even.subtract(BigInteger.valueOf(1));
                } 
            }
        }

        return NumOfEven.add(NumOfOdd);
    }
}
