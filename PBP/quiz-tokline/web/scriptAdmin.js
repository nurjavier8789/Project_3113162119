const API = '/api/tokline';
const $ = id => document.getElementById(id);
let kodeEdit = null;

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
    [m.kode_produk, m.nama_produk, m.harga, m.stok].forEach(nilai => {
      const td = document.createElement('td');
      td.textContent = nilai;
      tr.appendChild(td);
    });
    const aksi = document.createElement('td');
    const edit = document.createElement('button');
    edit.textContent = 'Edit';
    edit.onclick = () => mulaiEdit(m);

    const hapus = document.createElement('button');
    hapus.textContent = 'Hapus';
    hapus.onclick = () => hapusData(m.kode_produk, m.nama_produk);

    aksi.append(edit, hapus);
    tr.appendChild(aksi);
    tabel.appendChild(tr);
  });
}

async function simpanData(data) {
  try {
    const url = kodeEdit
      ? API + '/' + encodeURIComponent(kodeEdit) : API;
    const res = await fetch(url, {
      method: kodeEdit ? 'PUT' : 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(data)
    });
    if (!res.ok) throw new Error('Gagal menyimpan data');
    batalEdit();
    await muatData();
    tampilPesan('Data berhasil disimpan');
  } catch (err) { tampilPesan(err.message); }
}

function mulaiEdit(m) {
  kodeEdit = m.kode_produk;
  $('nama-produk').value = m.nama_produk;
  $('harga').value = m.harga;
  $('stok').value = m.stok;
  $('btnSimpan').textContent = 'Perbarui';
}

function batalEdit() {
  kodeEdit = null;
  form.reset();
  $('btnSimpan').textContent = 'Simpan';
}

async function hapusData(kode, nama) {
  if (!confirm('Hapus produk ' + nama + '?')) return;
  try {
    const url = API + '/' + encodeURIComponent(kode);
    const res = await fetch(url, { method: 'DELETE' });
    if (!res.ok) throw new Error('Gagal menghapus');
    // if (nimEdit === nim) batalEdit();
    await muatData();
    tampilPesan('Data berhasil dihapus');
  } catch (err) {
    tampilPesan(err.message);
  }
}

form.addEventListener('submit', async (e) => {
  e.preventDefault();

  const data = {
    nama_produk: $('nama-produk').value.trim(),
    harga: $('harga').value.trim(),
    stok: $('stok').value.trim()
  };

  await simpanData(data);
});

$('btnBatal').addEventListener('click', batalEdit);
muatData();
