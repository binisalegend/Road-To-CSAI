import java.util.Scanner;
import java.util.Stack;

public class Lesson2Question2 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String string = scanner.next();
        scanner.close();

        if (Judgement(string))
        {
            System.out.println("true");
        }
        else
        {
            System.out.println("false");
        }
        System.exit(0);
    }

    public static boolean Judgement(String a)
    {
        Stack<Character> count = new Stack<>();
        char[] strCharArray = a.toCharArray();
        int len = a.length();

        for (int i = 0; i < len; i++)
        {
            if (count.empty())
            {
                count.push(strCharArray[i]);
            }
            else
            {
                if (strCharArray[i] == '(' || strCharArray[i] == '{' || strCharArray[i] == '[')
                {
                    count.push(strCharArray[i]);
                }
                else if (strCharArray[i] == ')')
                {
                    if (count.peek() != '(')
                    {
                        return false;
                    }
                    else
                    {
                        count.pop();
                    }
                }
                else if (strCharArray[i] == ']')
                {
                    if (count.peek() != '[')
                    {
                        return false;
                    }
                    else
                    {
                        count.pop();
                    }
                }
                else
                {
                    if (count.peek() != '{')
                    {
                        return false;
                    }
                    else
                    {
                        count.pop();
                    }
                }
            }
        }
            
        if (count.empty())
        {
            return true;
        }
        return false;
    }
}
