/*
 * @Descripttion: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-17 10:04:12
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-17 22:31:30
 */
import java.util.Scanner;
import java.util.Stack;

public class Lesson4Question4 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String string = scanner.nextLine();
        String[] str = string.split(" ");
        scanner.close();

        double result = CalculateResult(str);
        System.out.printf("%.4f\n", result);
        System.exit(0);
    }

    /**
     * @name: CalculateResult
     * @msg: actually calculate main function
     * @param {String[]} str
     * @return {*}
     */
    private static double CalculateResult(String[] str)
    {
        int length = str.length;
        Stack<Double> number = new Stack<>();


        for (int i = length-1; i >= 0; i--)
        {
            String ch = str[i];
            if (ch.length() != 1 || (ch.length() == 1 && !isSymbol(ch)))
            {
                double num = Double.parseDouble(ch);
                number.push(num);
            }
            else
            {
                double start = number.peek();
                number.pop();
                double end = number.peek();
                number.pop();
                double NewNumber = calculate(start, end, ch);
                number.push(NewNumber);
            }
        }

        double result = number.peek();
        number.pop();
        return result;
    }

    /**
     * @name: isSymbol
     * @msg: judging if a character is operator
     * @param {String} ch
     * @return {*}
     */
    private static boolean isSymbol(String ch)
    {
        if (ch.equals("+") || ch.equals("-") || ch.equals("*") || ch.equals("/"))
        {
            return true;
        }
        return false;
    }

    /**
     * @name: calculate
     * @msg: do operations judging by strings
     * @param {double} front
     * @param {double} end
     * @param {String} ch
     * @return: calculate result
     */
    private static double calculate(double front, double end, String ch)
    {
        double result = 0;
        switch (ch)
        {
            case "+":
                result = front + end;
                break;
            case "-":
                result = front - end;
                break;
            case "*":
                result = front * end;
                break;
            case "/":
                result = front / end;
                break;
        }
        return result;
    }
}