const API = '/api/mahasiswa';
const $ = id => document.getElementById(id);
let nimEdit = null;

const form = $('formMahasiswa');
const tabel = $('dataMahasiswa');
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
    [m.nim, m.nama, m.prodi].forEach(nilai => {
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
    hapus.onclick = () => hapusData(m.nim);

    aksi.append(edit, hapus);
    tr.appendChild(aksi);
    tabel.appendChild(tr);
  });
}

async function simpanData(data) {
  try {
    const url = nimEdit
      ? API + '/' + encodeURIComponent(nimEdit) : API;
    const res = await fetch(url, {
      method: nimEdit ? 'PUT' : 'POST',
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
  nimEdit = m.nim;
  $('nim').value = m.nim;
  $('nim').disabled = true;
  $('nama').value = m.nama;
  $('prodi').value = m.prodi;
  $('btnSimpan').textContent = 'Perbarui';
}

function batalEdit() {
  nimEdit = null;
  form.reset();
  $('nim').disabled = false;
  $('btnSimpan').textContent = 'Simpan';
}

async function hapusData(nim) {
  if (!confirm('Hapus mahasiswa ' + nim + '?')) return;
  try {
    const url = API + '/' + encodeURIComponent(nim);
    const res = await fetch(url, { method: 'DELETE' });
    if (!res.ok) throw new Error('Gagal menghapus');
    if (nimEdit === nim) batalEdit();
    await muatData();
    tampilPesan('Data berhasil dihapus');
  } catch (err) {
    tampilPesan(err.message);
  }
}

form.addEventListener('submit', async (e) => {
  e.preventDefault();

  const data = {
    nim: $('nim').value.trim(),
    nama: $('nama').value.trim(),
    prodi: $('prodi').value.trim()
  };

  await simpanData(data);
});

$('btnBatal').addEventListener('click', batalEdit);
muatData();
