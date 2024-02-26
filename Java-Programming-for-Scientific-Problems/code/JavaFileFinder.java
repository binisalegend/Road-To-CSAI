import java.io.File;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class JavaFileFinder {
    public static void main(String[] args) {
        String folderPath = "D:\\大学资料\\Road-To-CSAI\\Java-Programming-for-Scientific-Problems"; 
        List<File> result = findJavaFiles(folderPath);
        result.stream().forEach(System.out::println);
    }

    public static List<File> findJavaFiles(String folderPath) 
    {
        File folder = new File(folderPath);
        if (!folder.exists() || !folder.isDirectory()) 
        {
            System.out.println("路径无效");
            return null;
        }
        List<File> javaFiles = Arrays.stream(folder.listFiles())
                .filter(file -> file.isFile() && file.getName().endsWith(".java"))
                .collect(Collectors.toList());
        System.out.println(javaFiles);

        File[] files = folder.listFiles();
        if (files != null) 
        {
            for (File file : files) 
            {
                if (file.isDirectory()) 
                {
                    findJavaFiles(file.getAbsolutePath());
                } 
                else if (file.isFile() && file.getName().endsWith(".java")) 
                {
                    javaFiles.add(file);
                    // System.out.println(file.getAbsolutePath()); 
                }
            }
        }
        return javaFiles;
    }
}
