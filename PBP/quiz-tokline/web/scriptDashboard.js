const API = '/api/tokline';
const $ = id => document.getElementById(id);

const form = $('formProduk');
const tabel = $('dataProduk');
const pesan = $('pesan');

function tampilPesan(teks) {
  pesan.textContent = teks;
}

async function muatData() {
  try {
    const res = await fetch(API);
    if (!res.ok) throw new Error('Gagal mengambil data');

    const data = await res.json();
    tampilkanTabel(data);
  } catch (error) {
    tampilPesan(error.message);
  }
}

function tampilkanTabel(data) {
  tabel.replaceChildren();
  data.forEach(m => {
    const tr = document.createElement('tr');
    [m.nama_produk, m.harga, m.stok].forEach(nilai => {
      const td = document.createElement('td');
      td.textContent = nilai;
      tr.appendChild(td);
    });
    const aksi = document.createElement('td');

    const buy = document.createElement('button');
    buy.textContent = 'Beli';
    buy.onclick = () => beliItem(m);

    const bulkBuy = document.createElement('button');
    bulkBuy.textContent = 'Beli Banyak';
    bulkBuy.onclick = () => bulkBeli(m);

    aksi.append(buy, bulkBuy);
    tr.appendChild(aksi);
    tabel.appendChild(tr);
  });
}

async function beliItem(m) {
  const minusStok = m.stok - 1;

  const bodyField = {
    'stok': minusStok
  };

  try {
    const url = API + '/beli/' + m.kode_produk;
    const res = await fetch(url, {
      method: 'put',
      headers: { 'content-type': 'application/json' },
      body: JSON.stringify(bodyField)
    });
    if (!res.ok) throw new Error('Gagal menyimpan data');
    await muatData();
    tampilPesan('Membeli 1 ' + m.nama_produk + '!');
  } catch (e) {
    tampilPesan(e.message);
  }
}

async function bulkBeli(m) {
  let input = prompt("Masukkan jumlah barang yang ingin dibeli:", "1");

  if (input != null) {
    const minusStok = m.stok - input;
  
    const bodyField = {
      'stok': minusStok
    };
  
    try {
      const url = API + '/beli/' + m.kode_produk;
      const res = await fetch(url, {
        method: 'put',
        headers: { 'content-type': 'application/json' },
        body: JSON.stringify(bodyField)
      });
      if (!res.ok) throw new Error('Gagal menyimpan data');
      await muatData();
      tampilPesan('Membeli ' + input + ' ' + m.nama_produk + '!');
    } catch (e) {
      tampilPesan(e.message);
    }
  }
}

muatData();
