public class MaxNumInArray {
    public static int max(int[] m)
    {
        int max = 0, i = 0;
        while (i < m.length)
        {
            if (m[i] >= max)
            {
                max = m[i];
            }
            i = i + 1;
        }
        return max;
    }
    public static void main(String[] args)
    {
        int num[] = new int[]{9, 1, 2, 3, 6, 0};
        System.out.println(max(num));
        System.exit(0);
    }
}
