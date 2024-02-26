// 树状数组算法
import java.util.Arrays;
import java.util.Scanner;

public class Lesson6Question4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String len = scanner.nextLine();
        int length = Integer.parseInt(len);
        String[] loc = scanner.nextLine().split(" ");
        scanner.close();

        int[] array = new int[length];
        for (int i = 0; i < length; i++) 
        {
            array[i] = Integer.parseInt(loc[i]);
        }

        int[] sortedArray = array.clone();
        Arrays.sort(sortedArray); // 对输入数组进行排序，以便进行离散化

        int[] fenwickTree = new int[length + 1];
        long count = 0; // 逆序对数量

        for (int i = length - 1; i >= 0; i--) {
            int rank = Arrays.binarySearch(sortedArray, array[i]) + 1; // 离散化后的位置
            count += query(fenwickTree, rank - 1); // 查询小于rank的元素数量
            update(fenwickTree, rank, 1); // 在rank位置增加1
        }

        System.out.println(count);
    }

    // 树状数组的更新操作
    private static void update(int[] fenwickTree, int index, int delta) {
        int n = fenwickTree.length;
        for (; index < n; index += (index & -index)) {
            fenwickTree[index] += delta;
        }
    }

    // 树状数组的查询操作
    private static int query(int[] fenwickTree, int index) {
        int sum = 0;
        for (; index > 0; index -= (index & -index)) {
            sum += fenwickTree[index];
        }
        return sum;
    }
}

// 归并排序算法
// import java.util.Scanner;

// public class Main {
//     public static void main(String[] args) {
//         Scanner scanner = new Scanner(System.in);
//         String len = scanner.nextLine();
//         int length = Integer.parseInt(len);
//         String[] loc = scanner.nextLine().split(" ");
//         scanner.close();

//         int[] array = new int[length];
//         for (int i = 0; i < length; i++) 
//         {
//             array[i] = Integer.parseInt(loc[i]);
//         }

//         int result = MergeSort(array, 0, array.length-1);
//         System.out.println(result);
//     }

//     private static int MergeSort(int[] num, int left, int right)
//     {
//         int count = 0;
//         if (left < right)
//         {
//             int middle = (left + right) / 2;
//             count += MergeSort(num, left, middle);
//             count += MergeSort(num, middle+1, right);
//             count += Merge(num, left, middle, right);
//         }
//         return count;
//     }

//     private static int Merge(int[] num, int left, int middle, int right)
//     {
//         int count = 0;
//         int[] temp = new int[right - left + 2];

//         int i = left;
//         int j = middle + 1;
//         int k = 0;
//         while (i <= middle && j <= right)
//         {
//             if (num[i] <= num[j])
//             {
//                 temp[k++] = num[i++];
//             }
//             else
//             {
//                 temp[k++] = num[j++];
//                 count += (middle - i + 1);
//             }
//         }
//         while (i <= middle)
//         {
//             temp[k++] = num[i++];
//         }
//         while (j <= right)
//         {
//             temp[k++] = num[j++];
//         }

//         for (i = left; i <= right; i++)
//         {
//             num[i] = temp[i - left];
//         }
//         return count;
//     }
// }