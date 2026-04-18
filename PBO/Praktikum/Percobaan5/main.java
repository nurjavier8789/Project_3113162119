package PBO.Praktikum.Percobaan5;

import java.util.Scanner;

public class main {
    public static String nama, kelas, nim, isInterConfirm, bahasa, negaraAsal, statusVisa, mataUang;
    public static int angkatan, nilai;
    public static boolean isInter, statusVisaFR;
    
    public static void identityMhs() {
        Scanner input = new Scanner(System.in);

        System.out.print("Nama mahasiswa: ");
        nama = input.next();
        System.out.print("NIM: ");
        nim = input.next();
        System.out.print("Kelas: ");
        kelas = input.next();
        System.out.print("Angkatan: ");
        angkatan = input.nextInt();
        
        System.out.println("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        Mahasiswa mhs1 = new Mahasiswa(nama, nim, kelas, angkatan, "TekFor");
        mhs1.tampilkanInformasi();

        input.close();
    }

    public static void interIdentity() {
        Scanner input = new Scanner(System.in);

        System.out.print("Name: ");
        nama = input.next();
        System.out.print("NIM: ");
        nim = input.next();
        System.out.print("Class: ");
        kelas = input.next();
        System.out.print("Generation: ");
        angkatan = input.nextInt();
        System.out.print("Primary language: ");
        bahasa = input.next();
        System.out.print("Country of origin: ");
        negaraAsal = input.next();
        System.out.print("Currency: ");
        mataUang = input.next();
        System.out.print("Grade: ");
        nilai = input.nextInt();
        System.out.print("Visa status (active/expired): ");
        statusVisa = input.next();

        if (statusVisa.equalsIgnoreCase("active")) {
            statusVisaFR = true;
        } else if (statusVisa.equalsIgnoreCase("expired")) {
            statusVisaFR = false;
        }

        System.out.println("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        MahasiswaInternasional mhsinter1 = new MahasiswaInternasional(nama, nim, kelas, angkatan, "TekFor", bahasa, negaraAsal, nilai, statusVisaFR);
        mhsinter1.tampilkanInformasi(mataUang);

        input.close();
    }

    public static void main(String[] args) {
        Mahasiswa mhs1 = new Mahasiswa("Alfandi", "123", "G", 19, "Teknik Informatika");

        System.out.println(mhs1.nama); 
        System.out.println(mhs1.nim);
        System.out.println(mhs1.jurusanDefault);
        System.out.println(mhs1.jurusanProtected);
    }
}
