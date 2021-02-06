package dev.justinf.kmatch.utils;

public class StringUtils {

    public static String convertMillisToTime(int millis) {
        int seconds = millis / 1000 % 60;
        int minutes = millis / 60000;
        return minutes + ":" + (seconds < 10 ? "0" : "") + seconds;
    }

    public static String getProgress(int offset, int total) {
        return String.format("%.1f", Math.min(100.0, ((double) offset / total)) * 100.0) + "%";
    }

    public static boolean containsIgnoreCase(String str, String... keywords) {
        String lowerCase = str.toLowerCase();
        for (String word : keywords) {
            if (lowerCase.contains(word.toLowerCase())) return true;
        }
        return false;
    }
}