package PBO.Praktikum.Percobaan5;

public class MahasiswaInternasional extends Mahasiswa {
    public String bahasa;
    public String negaraAsal;
    public int nilai;
    public boolean statusVisa;

    public MahasiswaInternasional(String nama, String nim, String kelas, int angkatan, String jurusan, String bahasa, String negaraAsal, int nilai, boolean statusVisa) {
        super(nama, nim, kelas, angkatan, jurusan);
        this.bahasa = bahasa;
        this.negaraAsal = negaraAsal;
        this.nilai = nilai;
        this.statusVisa = statusVisa;
    }

    public void tampilkanInformasi(String matauang) { 
        super.tampilkanInformasi();

        String stringStatusVisa;
        if (statusVisa) {
            stringStatusVisa = "Visa aktif, mahasiswa diizinkan tinggal";
        } else {
            stringStatusVisa = "Visa tidak aktif, segera lakukan perpanjangan";
        }

        System.out.println("INFORMASI TAMBAHAN");
        System.out.println("Bahasa\t\t : " + bahasa);
        System.out.println("Negara\t\t : " + negaraAsal);
        System.out.println("Uang\t\t : " + matauang);
        System.out.println("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        System.out.println("Nilai\t\t : " + nilai);
        System.out.println("Status Visa\t : " + stringStatusVisa);
        System.out.println("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        if (nilai >= 75) {
            System.out.println("Mahasiswa LULUS");
        } else if (nilai < 75) {
            System.out.println("Remidial diperbolehkan");
        } else if (nilai < 60) {
            System.out.println("Harus mengulang, diperbolehkan memperpanjang masa tinggal (kepulangan ditunda)");
        }
        if (nilai < 60 && !statusVisa) {
            System.out.println("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            System.out.println("PERINGATAN: Mahasiswa harus mengulang dan segera memperpanjang visa!");
        }
    }

    public void perkenalan() {
        System.out.println("Nama saya adalah " + nama); 
        System.out.println(", NIM saya adalah" + nim); 
        // System.out.println(", Saya dari kelas" + kelas); 
    }
}
