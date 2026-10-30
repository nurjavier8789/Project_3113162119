const express = require('express');
const db = require('./database');
const app = express();

app.use(express.json());
app.use(express.static('web'));

app.get('/api/tokline', async (req, res) => {
  try {
    const [rows] = await db.query('SELECT * FROM produk');
    res.json(rows);
  } catch (err) {
    res.status(500).json({ pesan: 'Gagal mengambil data' });
  }
});

app.post('/api/tokline', async (req, res) => {
  const { nama_produk, harga, stok } = req.body;
  if (!nama_produk || !harga || !stok)
    return res.status(400).json({ pesan: 'Isi semua kolom' });
  try {
    await db.execute(
      'INSERT INTO produk (`kode_produk`, `nama_produk`, `harga`, `stok`) VALUES (null,?,?,?)',
      [nama_produk, harga, stok]
    );
    res.status(201).json({ pesan: 'Data ditambahkan' });
  } catch (err) {
    res.status(400).json({ pesan: 'Sudah ada / data salah' });
  }
});

app.put('/api/tokline/:kode_produk', async (req, res) => {
  const { nama_produk, harga, stok } = req.body;
  if (!nama_produk || !harga || !stok)
    return res.status(400).json({ pesan: 'Isi semua kolom' });
  try {
    const [hasil] = await db.execute(
      'UPDATE produk SET nama_produk=?, harga=?, stok=? WHERE kode_produk=?',
      [nama_produk, harga, stok, req.params.kode_produk]
    );
    if (!hasil.affectedRows) return res.sendStatus(404);
    res.json({ pesan: 'Data diperbarui' });
  } catch (err) { res.sendStatus(500); }
});

app.delete('/api/tokline/:kode_produk', async (req, res) => {
  try {
    const [hasil] = await db.execute(
      'DELETE FROM produk WHERE kode_produk=?', [req.params.kode_produk]
    );
    if (!hasil.affectedRows) return res.sendStatus(404);
    res.json({ pesan: 'Data dihapus' });
  } catch (err) { res.sendStatus(500); }
});

app.listen(1660, () => console.log("Done!"))