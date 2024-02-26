import java.util.Scanner;
import java.util.Stack;

public class Lesson7Question2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String Str = scanner.nextLine();
        scanner.close();

        StringBuilder str = new StringBuilder(Str);
        BFcodeToCcode(str);
    }

    static Stack<Character> LoopStack = new Stack<>();

    private static StringBuilder SimplifyString(StringBuilder str)
    {
        int i = 0;
        StringBuilder temp = new StringBuilder();
        while (i < str.length())
        {
            if (temp.length() == 0) 
            {
                temp.append(str.charAt(i++));
                continue;
            }
            else
            {
                if (str.charAt(i) == '+')
                {
                    if (temp.charAt(temp.length() - 1) == '-') 
                    {
                        temp.deleteCharAt(temp.length() - 1);
                        i++;
                        continue;
                    }
                    else temp.append(str.charAt(i++));
                }
                else if (str.charAt(i) == '-')
                {
                    if (temp.charAt(temp.length() - 1) == '+') 
                    {
                        temp.deleteCharAt(temp.length() - 1);
                        i++;
                        continue;
                    }
                    else temp.append(str.charAt(i++));
                }
                else if (str.charAt(i) == '<')
                {
                    if (temp.charAt(temp.length() - 1) == '>') 
                    {
                        temp.deleteCharAt(temp.length() - 1);
                        i++;
                        continue;
                    }
                    else temp.append(str.charAt(i++));
                }
                else if (str.charAt(i) == '>')
                {
                    if (temp.charAt(temp.length() - 1) == '<') 
                    {
                        temp.deleteCharAt(temp.length() - 1);
                        i++;
                        continue;
                    }
                    else temp.append(str.charAt(i++));
                }
                else if (str.charAt(i) == ']')
                {
                    if (temp.charAt(temp.length() - 1) == '[') 
                    {
                        temp.deleteCharAt(temp.length() - 1);
                        i++;
                        continue;
                    }
                    else temp.append(str.charAt(i++));
                }
                else if (str.charAt(i) == '[')  temp.append(str.charAt(i++));
                else if (str.charAt(i) == '.')  temp.append(str.charAt(i++));
                else if (str.charAt(i) == ',')  temp.append(str.charAt(i++));
                else i++;
            }
        }
        return temp;
    }

    private static void BFcodeToCcode(StringBuilder Str) {
        int AddCount = 0, SubCount = 0, PorinterAddCount = 0, PointerSubCount = 0, BackSpaceCount = 0;
        int j = 0;
        StringBuilder str = new StringBuilder();
        str = SimplifyString(Str);
        while (j < str.length())
        {
            if (str.charAt(j) == '[')
            {
                if (LoopStack.empty() || LoopStack.peek().equals('[')) 
                {
                    LoopStack.add('[');
                    j++;
                }
                continue;
            }
            else if (str.charAt(j) == ']')
            {
                if (LoopStack.empty()) 
                {
                    System.out.println("Error!");
                    return;
                }
                else
                {
                    LoopStack.pop();
                    j++;
                }
                continue;
            }
            else j++;
        }
        if (!LoopStack.empty())
        {
            System.out.println("Error!");
            return;
        }

        for (int i = 0; i < str.length(); i++)
        {
            if (str.charAt(i) == '+')
            {
                PorinterAddCount++;
                if (i != str.length() - 1 && (str.charAt(i+1) == '+' || str.charAt(i+1) == '-')) continue;
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("*p += " + PorinterAddCount + ";\n");
                PorinterAddCount = 0;
            }
            else if (str.charAt(i) == '-')
            {
                PointerSubCount++;
                if (i != str.length() - 1 && (str.charAt(i+1) == '+' || str.charAt(i+1) == '-')) continue;
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("*p -= " + PointerSubCount + ";\n");
                PointerSubCount = 0;
            }
            else if (str.charAt(i) == '>')
            {
                AddCount++;
                if (i != str.length() - 1 && str.charAt(i+1) == '>') continue;
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("p += " + AddCount + ";\n");
                AddCount = 0;
            }
            else if (str.charAt(i) == '<')
            {
                SubCount++;
                if (i != str.length() - 1 && str.charAt(i+1) == '<') continue;
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("p -= " + SubCount + ";\n");
                SubCount = 0;
            }
            else if (str.charAt(i) == '.')
            {
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("putchar(*p);\n");
            }
            else if (str.charAt(i) == ',')
            {
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("*p = getchar();\n");
            }
            else if (str.charAt(i) == '[')
            {
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("if (*p) do {\n");
                BackSpaceCount += 2;
            }
            else if (str.charAt(i) == ']')
            {
                BackSpaceCount -= 2;
                int loc = BackSpaceCount;
                while (loc > 0)
                {
                    System.out.print(' ');
                    loc--;
                }
                System.out.print("} while (*p);\n");
            }
            else continue;
        }
    }
}
