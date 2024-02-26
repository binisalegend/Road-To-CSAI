import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class ExplanatoryNote {
    // 判断是否是单行注释
    public static boolean isSingleLineComment(String line) 
    {
        line = line.trim();
        return line.startsWith("//");
    }

    // 判断是否是多行注释的起始行
    public static boolean isStartOfMultiLineComment(String line) 
    {
        line = line.trim();
        return line.startsWith("/*");
    }

    // 判断是否是多行注释的结束行
    public static boolean isEndOfMultiLineComment(String line) 
    {
        line = line.trim();
        return line.endsWith("*/");
    }

    // 判断是否是多行注释中的行
    public static boolean isInsideMultiLineComment(String line, boolean insideComment) 
    {
        line = line.trim();
        if (insideComment) return true;
        else 
        {
            return line.startsWith("/*") || line.endsWith("*/") || line.contains("*/");
        }
    }    

    // 判断是否是注释行
    public static boolean isCommentLine(String line, boolean insideComment) 
    {
        return isSingleLineComment(line) || isInsideMultiLineComment(line, insideComment);
    }

    public static void removeCommentsFromFile(String filePath) 
    {
        StringBuilder result = new StringBuilder();
        boolean insideMultiLineComment = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;

            while ((line = reader.readLine()) != null) 
            {
                if (!isCommentLine(line, insideMultiLineComment)) 
                {
                    result.append(line).append("\n");
                }

                // 更新多行注释状态
                if (isStartOfMultiLineComment(line)) 
                {
                    insideMultiLineComment = true;
                } 
                else if (isEndOfMultiLineComment(line)) 
                {
                    insideMultiLineComment = false;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 写回文件
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) 
        {
            writer.write(result.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) 
    {
        String filePath = "D:\\大学资料\\Road-To-CSAI\\Java-Programming-for-Scientific-Problems\\code\\ExplanatoryNote.java";
        removeCommentsFromFile(filePath);

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            boolean insideMultiLineComment = false;

            while ((line = reader.readLine()) != null) 
            {
                boolean isComment = isCommentLine(line, insideMultiLineComment);
                System.out.println("Line: " + line + " is a comment? " + isComment);

                if (isStartOfMultiLineComment(line)) 
                {
                    insideMultiLineComment = true;
                } 
                else if (isEndOfMultiLineComment(line)) 
                {
                    insideMultiLineComment = false;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
