import java.util.Scanner;
public class Lesson4Question3 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String[] str1 = scanner.nextLine().split(" ");
        String[] str2 = scanner.nextLine().split(" ");
        scanner.close();
        int carrybits = 0;
        int len1 = str1.length;
        int len2 = str2.length;
        int index1 = 0, index2 = 0, index_all = 0;
        int res[] = new int[1000];
        while(index1<len1&&index2<len2)
        {
            Integer num ;
            num = Integer.valueOf(str1[index1])+Integer.valueOf(str2[index2])+carrybits;
            if(carrybits>0) carrybits--;
            if(num>=10)
            {
                num -= 10;
                carrybits += 1;
            }
            res[index_all++] = num;
            index1++;
            index2++;
        }
        while(index1<len1)
        {
            Integer num ;
            num = Integer.valueOf(str1[index1])+carrybits;
            if(carrybits>0) carrybits--;
            if(num>=10)
            {
                num -= 10;
                carrybits += 1;
            }
            res[index_all++] = num;
            index1++;
        }
        while(index2<len2)
        {
            Integer num ;
            num = Integer.valueOf(str2[index2])+carrybits;
            if(carrybits>0) carrybits--;
            if(num>=10)
            {
                num -= 10;
                carrybits += 1;
            }
            res[index_all++] = num;
            index2++;
        }
        if(carrybits>0)res[index_all++] = carrybits;
        for(index1 = 0; index1 < index_all; index1++)
        {
            if(index1!=index_all-1) System.out.print(res[index1]+" ");
            else System.out.println(res[index1]);
        }
    }
}