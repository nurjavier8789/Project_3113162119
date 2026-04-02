package PBO.Praktikum.Percobaan4;

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
        Mahasiswa mhs1 = new Mahasiswa(nama, nim, kelas, angkatan);
        mhs1.tampilkanInformasi();
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
        MahasiswaInternasional mhsinter1 = new MahasiswaInternasional(nama, nim, kelas, angkatan, bahasa, negaraAsal, nilai, statusVisaFR);
        mhsinter1.tampilkanInformasi(mataUang);
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Are you international students? (y/n)\n> ");
        isInterConfirm = input.next();

        if (isInterConfirm.equalsIgnoreCase("y")) {
            interIdentity();
        } else if (isInterConfirm.equalsIgnoreCase("n")) {
            identityMhs();
        }
    }
}
