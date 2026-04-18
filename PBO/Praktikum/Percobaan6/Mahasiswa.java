package PBO.Praktikum.Percobaan6;

public abstract class Mahasiswa {
    public String nama; 
    public String nim;
    public String kelas; 
    public int angkatan;
    String jurusanDefault;
    protected String jurusanProtected;

    public Mahasiswa(String nama, String nim, String kelas, int angkatan, String jurusan) { 
        this.nama = nama; 
        this.nim = nim; 
        this.kelas = kelas; 
        this.angkatan = angkatan;
        this.jurusanDefault = jurusan;
        this.jurusanProtected = jurusan;
        System.out.println("Data sudah disimpan kedalam database\n"); 
    }

    public void tampilkanInformasi() { 
        System.out.println("INFORMASI MAHASISWA"); 
        System.out.println("Nama\t: " + nama); 
        System.out.println("NIM\t: " + nim); 
        System.out.println("Kelas\t: " + kelas); 
        System.out.println("Angkatan: " + angkatan + "\n"); 
    }

    public abstract void aktivitas();

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
