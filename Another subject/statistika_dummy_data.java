// public class statistika_dummy_data {
//     public static void main(String[] args) {
//         System.out.println("\nNilai rata-rata semester Budi\n");
//         System.out.println("|----------|-------|");
//         System.out.println("| Semester | Nilai |");
//         System.out.println("|----------|-------|");
//         System.out.println("|    1     | 83,25 |");
//         System.out.println("|    2     | 86,33 |");
//         System.out.println("|    3     | 90,63 |");
//         System.out.println("|    4     | 88,18 |");
//         System.out.println("|    5     | 87,80 |");
//         System.out.println("|----------|-------|");
//     }
// }

// I have no idea what im doing ngl

public class statistika_dummy_data {
    public static void main(String[] args) {
        String[][] data = {
            {"1", "Budi Santoso", "  Laki-laki  ", "Futsal ", "   1    ", "83.25", "100%"},
            {" ", "            ", "             ", "       ", "   2    ", "86.33", "95%"},
            {"2", "Siti Aminah ", "  Perempuan  ", "  PMR  ", "   1    ", "90.50", "100%"},
            {" ", "            ", "             ", "       ", "   2    ", "91.20", "100%"},
            {"3", "Yadi Sutiaji", "  Laki-laki  ", "Robotik", "   1    ", "80.00", "100%"},
            {" ", "            ", "             ", "       ", "   2    ", "84.50", "98%"}
        };

        System.out.println("---------------------------------------------------------------------------");
        System.out.println("No |  Nama Siswa  | Jenis Kelamin | Ekskul  | Semester | Nilai | Kehadiran");
        System.out.println("---------------------------------------------------------------------------");
        
        for (int i = 0; i < data.length; i++) {
            System.out.println(data[i][0] + "  | " + data[i][1] + " | " + data[i][2] + " | " + 
            data[i][3] + " | " + data[i][4] + " | " + data[i][5] + " | " + data[i][6]);
        }
        
        System.out.println("---------------------------------------------------------------------------");
    }
}
