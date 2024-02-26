public class EnhencedForBreakDemo {
    public static void main(String[] args)
    {
        String[] a = new String[]{"cat", "dog", "horse666", "fish"};
    
        for (String s: a)
        {
            for (int i = 0; i < 3; i++)
            {
                System.out.println(s);
                if (s.contains("horse"))
                {
                    break;
                }
            }
        }
        System.exit(0);
    }
}
