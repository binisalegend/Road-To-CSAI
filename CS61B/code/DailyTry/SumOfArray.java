public class SumOfArray {
    public static void windowPosSum(int[] a, int n)
    {
        for (int i = 0; i < a.length; i++)
        {
            if (a[i] > 0)
            {
                for (int j = i + 1; j < i + 1 + n && j < a.length; j++)
                {
                    a[i] += a[j];
                }
            }
        }
    }
    public static void main(String[] args)
    {
        int num[] = new int[]{1, 2, -3, 4, 5, 4};
        windowPosSum(num, 3);
        for (int i = 0; i < num.length; i++)
        {
            System.out.println(num[i]);
        }
        System.exit(0);
    }
}
