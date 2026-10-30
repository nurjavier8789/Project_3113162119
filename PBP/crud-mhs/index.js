const express = require('express');
const db = require('./database');
const app = express();

app.use(express.json());
app.use(express.static('public'));

app.get('/', (req, res)=>{
    res.send('trst');
})

app.get('/api/mahasiswa', async (req, res) => {
  try {
    const [rows] = await db.query('SELECT * FROM mahasiswa');
    res.json(rows);
  } catch (err) {
    res.status(500).json({ pesan: 'Gagal mengambil data' });
  }
});

app.post('/api/mahasiswa', async (req, res) => {
  const { nim, nama, prodi } = req.body;
  if (!nim || !nama || !prodi)
    return res.status(400).json({ pesan: 'Isi semua kolom' });
  try {
    await db.execute(
      'INSERT INTO mahasiswa (nim,nama,prodi) VALUES (?,?,?)',
      [nim, nama, prodi]
    );
    res.status(201).json({ pesan: 'Data ditambahkan' });
  } catch (err) {
    res.status(400).json({ pesan: 'NIM sudah ada / data salah' });
  }
});

app.put('/api/mahasiswa/:nim', async (req, res) => {
  const { nama, prodi } = req.body;
  if (!nama || !prodi)
    return res.status(400).json({ pesan: 'Isi semua kolom' });
  try {
    const [hasil] = await db.execute(
      'UPDATE mahasiswa SET nama=?,prodi=? WHERE nim=?',
      [nama, prodi, req.params.nim]
    );
    if (!hasil.affectedRows) return res.sendStatus(404);
    res.json({ pesan: 'Data diperbarui' });
  } catch (err) { res.sendStatus(500); }
});

app.delete('/api/mahasiswa/:nim', async (req, res) => {
  try {
    const [hasil] = await db.execute(
      'DELETE FROM mahasiswa WHERE nim=?', [req.params.nim]
    );
    if (!hasil.affectedRows) return res.sendStatus(404);
    res.json({ pesan: 'Data dihapus' });
  } catch (err) { res.sendStatus(500); }
});



app.listen(1660, () => console.log("Done!"))