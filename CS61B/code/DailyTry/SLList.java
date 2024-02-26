/**An SLList is a list of integers, which hides the terribles
 * of the nakedness within. */
public class SLList {

    /*The first item (if it exits) is at sentinel.next. */
    private IntNode sentinel;
    private int size;

    public class IntNode 
    {
        public int item;
        public IntNode next;

        public IntNode (int i, IntNode n)
        {
            item = i;
            next = n;
        }
    }

    /**Create an empty SLList. */
    public SLList()
    {
        sentinel = new IntNode(63, null);
        size = 0;
    }

    public SLList(int x)
    {
        sentinel = new IntNode(63, null);
        sentinel.next = new IntNode(x, null);
        size = 1;
    }

    /**Adds x to the front of the list. */
    public void addFirst(int x)
    {
        sentinel.next = new IntNode(x, sentinel.next);
        size += 1;
    }

    /**Returns the first item in the list */
    public int getFirst()
    {
        return sentinel.next.item;
    }

    /**Adds an itemd to the end of the list. */
    public void addLast(int x)
    {
        IntNode p = sentinel;

        /**Move p until it reaches the end of the list */
        while (p.next != null)
        {
            p = p.next;
        }
        p.next = new IntNode(x, null);
        size += 1;
    }

    public int size()
    {
        return size;
    }

    public static void main(String[] args)
    {
        /**Creates a Intlist of one integer namely 10 */
        SLList L = new SLList(15);
        L.addFirst(10);
        L.addFirst(5);
        L.addLast(20);
        System.out.println(L.size());
    }
}