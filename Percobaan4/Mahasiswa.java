package PBO.Praktikum.Percobaan4;

public class Mahasiswa {
    public String nama; 
    public String nim; 
    public String kelas; 
    public int angkatan;

    public Mahasiswa(String nama, String nim, String kelas, int angkatan) { 
        this.nama = nama; 
        this.nim = nim; 
        this.kelas = kelas; 
        this.angkatan = angkatan; 
        System.out.println("Data sudah disimpan kedalam database\n"); 
    }

    public void tampilkanInformasi() { 
        System.out.println("INFORMASI MAHASISWA"); 
        System.out.println("Nama\t: " + nama); 
        System.out.println("NIM\t: " + nim); 
        System.out.println("Kelas\t: " + kelas); 
        System.out.println("Angkatan: " + angkatan + "\n"); 
    }

    public void setNama(String nama) {
        this.nama = nama;
    }
    
    public void setNim(String nim) {
        this.nim = nim;
    }
    
    public void setKelas(String kelas) {
        this.kelas = kelas;
    }

    public String getNama() { 
        return nama; 
    } 
}
