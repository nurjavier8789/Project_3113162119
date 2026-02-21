#TUGAS
#Tugas 3 - Analisis data (Nama)

# This is simple version
# namaDepan = input("Masukkan nama depan: ")
# namaBelakang = input("Masukkan nama belakang: ")

# print("\nNama lengkap: " + namaDepan + " " + namaBelakang)
# print("Nama dibalik: "+ namaBelakang[::-1] + " " + namaDepan[::-1])

namaLengkap = []

namaLengkap.append(input("Masukkan nama depan: "))
namaLengkap.append(input("Masukkan nama belakang: "))

namaDepanBalik = ''
namaBelakangBalik = ''

for char in namaLengkap[0]:
    namaDepanBalik = char + namaDepanBalik

for char in namaLengkap[1]:
    namaBelakangBalik = char + namaBelakangBalik

print("\nNama Lengkap: " + namaLengkap [0] + " " + namaLengkap[1])
print("Nama dibalik: " + namaBelakangBalik + " " + namaDepanBalik)
