package com.example.proteindatabase.utils;

public class StringUtil
{
    public static boolean isEmpty(String str)
    {
        return str == null || str.isEmpty() || str.trim().isEmpty();
    }
}
