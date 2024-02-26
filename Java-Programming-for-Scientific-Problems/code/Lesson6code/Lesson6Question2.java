import java.util.Scanner;
import java.util.HashMap;

public class Lesson6Question2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String loc = scanner.nextLine();
        long OperationNum = scanner.nextLong();
        scanner.close();

        if (OperationNum < 1) {
            System.out.println(loc); // No operation needed
            return;
        }

        String resultString = ConvertingString(loc, OperationNum);
        System.out.println(resultString);
    }

    public static String ConvertingString(String s, long times) {
        if (times < 1) {
            return s; 
        }

        HashMap<String, Long> cycleMap = new HashMap<>();
        String resultString = s;

        for (long i = 0; i < times; i++) {
            resultString = scrambleCharacters(resultString);

            // Check if the current resultString has been seen before
            if (cycleMap.containsKey(resultString)) {
                long cycleLength = i - cycleMap.get(resultString);
                long remainingTimes = (times - i - 1) % cycleLength;
                i = times - remainingTimes - 1;
                cycleMap.clear(); // Clear the map to start a new cycle
            } else {
                cycleMap.put(resultString, i);
            }
        }

        return resultString;
    }

    private static String scrambleCharacters(String s) {
        int length = s.length();
        char[] resultArray = new char[length];

        for (int i = 0; i < length; i++) {
            if (i % 2 == 0) {
                resultArray[i] = s.charAt(length - (i >> 1) - 1);
            } else {
                resultArray[i] = s.charAt(i >> 1);
            }
        }

        return new String(resultArray);
    }
}
// 下面这个一直有WA和超内存的问题，然后把位置映射取消了，直接对字符串操作，哈希表记录位置
// import java.util.Scanner;

// public class Main {
//     public static void main(String[] args) {
//         Scanner scanner = new Scanner(System.in);
//         String loc = scanner.nextLine();
//         long OperationNum = scanner.nextLong();
//         scanner.close();

//         final int length = loc.length();

//         int[] ResultString = ConvertingString(length, OperationNum);

//         char[] resultArray = new char[length];
//         for (int i = 0; i < length; i++) 
//         {
//             resultArray[i] = loc.charAt(ResultString[i]);
//         }

//         System.out.println(resultArray);
//     }

//     private static int[][] adj;
//     private static int[] constMap;

//     private static int[] InitialMap(int length) 
//     {
//         int[] Initial = new int[length];
//         for (int i = 0; i < length; i++) 
//         {
//             Initial[i] = i;
//         }
//         return Initial;
//     }

//     public static int[] ConvertingString(int length, long times) 
//     {
//         constMap = InitialMap(length);
//         int[] mapping = constMap;
//         adj = new int[(int)times][];
//         for (long i = 0; i < times; i++) 
//         {
//             adj[(int)i] = mapping;
//             mapping = ConstMapCal(mapping, length);
//             for (long j = 0; j <= i; j++) 
//             {
//                 if (areArraysEqual(mapping, adj[(int)j], length)) 
//                 {
//                     return adj[(int)(times % (i - j + 1))];
//                 }
//             }
//         }
//         return mapping;
//     }

//     private static int[] ConstMapCal(int[] str, int length) 
//     {
//         int count = length - 1;
//         int[] mapping = new int[length];
//         for (int i = 0; i < length; i++) 
//         {
//             if (i % 2 == 0) 
//             {
//                 mapping[i] = str[constMap[count]];
//                 count--;
//             }
//             else 
//             {
//                 mapping[i] = str[constMap[length - count - 2]];
//             }
//         }
//         return mapping;
//     }

//     private static boolean areArraysEqual(int[] arr1, int[] arr2, int length) 
//     {
//         for (int i = 0; i < length; i++) {
//             if (arr1[i] != arr2[i]) {
//                 return false;
//             }
//         }
//         return true;
//     }
// }

// vector数组似乎要比直接建立[][]慢很多
// import java.util.Scanner;  
// import java.util.Vector;
  
// public class Main {  
//     public static void main(String[] args) {  
//         Scanner scanner = new Scanner(System.in);  
//         String loc = scanner.nextLine();  
//         long OperationNum = scanner.nextLong();  
//         scanner.close();  

//         final int length = loc.length();
  
//         Vector<Integer> ResultString = ConvertingString(length, OperationNum);;
        

//         char[] resultArray = new char[length];
//         for (int i = 0; i < length; i++)  
//         {  
//             resultArray[i] = loc.charAt(ResultString.get(i));
//         }  

//         System.out.println(resultArray);  
//     }  

//     static Vector<Vector<Integer>> adj = new Vector<Vector<Integer>>();

//     private static Vector<Integer> InitialMap(int length)
//     {
//         Vector<Integer> Initial = new Vector<>();
//         for (int i = 0; i < length; i++)
//         {
//             Initial.add(i);
//         }
//         return Initial;
//     }

//     public static Vector<Integer> ConvertingString(int length, long times)
//     {
//         Vector<Integer> constMap = InitialMap(length);
//         Vector<Integer> mapping = constMap;
//         for (long i = 0; i < times; i++)
//         {
//             adj.add(mapping);
//             mapping = ConstMapCal(mapping, constMap, length);
//             for (long j = 0; j <= i; j++)
//             {
//                 if (mapping.equals(adj.get((int)j)))
//                 {
//                     return adj.get((int)(times%(i-j+1)));
//                 }
//             }
//         }
//         return mapping;
//     }

//     private static Vector<Integer> ConstMapCal(Vector<Integer> str, Vector<Integer> constmap, int length)
//     {
//         int count = length - 1;
//         Vector<Integer> mapping = new Vector<Integer>();
//         for (int i = 0; i < length; i++)
//         {
//             if (i % 2 == 0)  
//             {  
//                 mapping.add(str.get(constmap.get(count)));  
//                 count--;  
//             }  
//             else  
//             {  
//                 mapping.add(str.get(constmap.get(length - count - 2)));  
//             }  
//         }
//         return mapping;
//     }
// }  
