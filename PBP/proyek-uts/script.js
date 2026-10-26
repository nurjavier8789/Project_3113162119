// Menentukan tanggal pernikahan
const weddingDate = new Date("Dec 24, 2026 08:00:00").getTime();

// Memperbarui hitungan mundur setiap 1 detik
const countdownFunction = setInterval(function() {
    
    // Mendapatkan tanggal dan waktu hari ini
    const now = new Date().getTime();
    
    // Menghitung selisih waktu
    const distance = weddingDate - now;
    
    // Perhitungan waktu untuk hari, jam, menit, dan detik
    const days = Math.floor(distance / (1000 * 60 * 60 * 24));
    const hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
    const minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((distance % (1000 * 60)) / 1000);
    
    // Menampilkan hasil pada elemen dengan id="countdown"
    document.getElementById("countdown").innerHTML = `
        <div class="time-box"><span>${days}</span><small>Hari</small></div>
        <div class="time-box"><span>${hours}</span><small>Jam</small></div>
        <div class="time-box"><span>${minutes}</span><small>Menit</small></div>
        <div class="time-box"><span>${seconds}</span><small>Detik</small></div>
    `;
    
    // Jika waktu hitung mundur selesai
    if (distance < 0) {
        clearInterval(countdownFunction);
        document.getElementById("countdown").innerHTML = "<h2>Acara Sedang Berlangsung</h2>";
    }
}, 1000);