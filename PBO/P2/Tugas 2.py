#TUGAS
#Tugas 2 - Analisis data (Nomor)

inputAng = []
for loop in range(10):
  inputAng.append(int(input("Masukkan angka ke-" + str(loop+1) + ": ")))

# Rata-rata
jumlahTotal = 0
for loop in range(len(inputAng)):
  jumlahTotal += inputAng[loop]

avg = jumlahTotal / len(inputAng)
print("\nRata-rata: " + str(avg))

# Angka terbesar
tempBig = inputAng[0]
for loop in range(len(inputAng)):
  if tempBig < inputAng[loop]:
    tempBig = inputAng[loop]
print("Angka terbesar: " + str(tempBig))

# Angka terkecil
tempSmall = inputAng[0]
for loop in range(len(inputAng)):
  if tempSmall > inputAng[loop]:
    tempSmall = inputAng[loop]
print("Angka terkecil: " + str(tempSmall))

# Angka Ganjil
counterGanjil = 0
for loop in range(len(inputAng)):
  if inputAng[loop] % 2 == 1:
    counterGanjil += 1
print("Jumlah angka ganjil: " + str(counterGanjil))

# Angka Genap
counterGenap = 0
for loop in range(len(inputAng)):
  if inputAng[loop] % 2 == 0:
    counterGenap += 1
print("Jumlah angka genap: " + str(counterGenap))
