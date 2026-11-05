<?php
    require_once __DIR__ . '/../vendor/autoload.php';

    $dotenv = Dotenv\Dotenv::createImmutable(__DIR__ . '/..');
    $dotenv->load();

    $hostname = $_ENV['DB_HOST'];
    $usernamedb = $_ENV['DB_USER'];
    $passworddb = $_ENV['DB_PASS'];
    $database = $_ENV['DB_NAME'];

    $koneksi = mysqli_connect($hostname, $usernamedb, $passworddb, $database);

    if ($koneksi) {
        echo "Server Online<br>";
    } else {
        echo "Server Offline<br>";
    }

    session_start();

    if (!isset($_SESSION["is_login"])) {
        header("location: index.php");
        exit;
    };

    $query = "SELECT * FROM produk ORDER BY produk.kode_produk ASC;";
    $result = $koneksi->query($query);
?>

<!DOCTYPE html>
<html lang="en">
    <style>
        table, th, td {
            border: 1px solid black;
        }
    </style>
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Toko Online - Pembeli</title>
    </head>
    <body>
        <p><a href="logout.php">Logout</a></p>
        <h1>Daftar Produk</h1>
        <table>
            <thead>
                <tr>
                    <th>Nama Produk</th>
                    <th>Harga</th>
                    <th>Stok</th>
                    <th>Aksi</th>
                </tr>
            </thead>
            <tbody>
                <?php if ($result && $result->num_rows > 0): ?>
                    <?php while ($row = $result->fetch_assoc()): ?>
                    <tr>
                        <td><?= htmlspecialchars($row['nama_produk']); ?></td>
                        <td class="text-right">Rp <?= number_format($row['harga'], 0, ',', '.'); ?></td>
                        <td class="text-center <?= ($row['stok'] < 10) ? 'stok-low' : ''; ?>"><?= (int)$row['stok']; ?></td>
                        <td class="text-center">
                            <?php if ($row['stok'] > 0): ?>
                                <form action="buy.php" method="POST" style="margin: 0;">
                                    <input type="hidden" name="produk_id" value="<?= (int)$row['kode_produk']; ?>">
                                    <input type="hidden" name="jumlah" value="1">
                                    <input type="hidden" name="stok" value="<?= (int)$row['stok']; ?>">
                                    <button type="submit" class="btn-beli-1">Beli 1</button>
                                </form>

                                <button type="button" onclick="prosesBeliBanyak(<?= (int)$row['kode_produk']; ?>, <?= (int)$row['stok']; ?>, '<?= htmlspecialchars($row['nama_produk'], ENT_QUOTES); ?>')">
                                    Beli Banyak
                                </button>
                            <?php else: ?>
                                <button type="button" disabled>Stok Habis</button>
                            <?php endif; ?>
                        </td>
                    </tr>
                    <?php endwhile; ?>
                <?php else: ?>
                    <tr>
                        <td colspan="4" class="text-center">Belum ada barang yang tersedia.</td>
                    </tr>
                <?php endif; ?>
            </tbody>
        </table>

        <form id="form-pembelian-banyak" action="buy.php" method="POST" style="display: none;">
            <input type="hidden" name="produk_id" id="hidden-produk-id">
            <input type="hidden" name="jumlah" id="hidden-jumlah">
            <input type="hidden" name="stok" id="hidden-stok">
        </form>

        <script>
            function prosesBeliBanyak(id, maxStok, namaProduk) {
                let input = prompt(`Masukkan jumlah "${namaProduk}" yang ingin dibeli:\n(Stok tersedia: ${maxStok})`, "2");
                
                if (input === null) return;

                let jumlah = parseInt(input, 10);

                if (isNaN(jumlah) || jumlah < 1) {
                    alert("Jumlah pembelian harus berupa angka minimal 1!");
                    return;
                }

                if (jumlah > maxStok) {
                    alert(`Stok tidak mencukupi! Pembelian maksimal adalah ${maxStok} unit.`);
                    return;
                }

                document.getElementById('hidden-produk-id').value = id;
                document.getElementById('hidden-jumlah').value = jumlah;
                document.getElementById('hidden-stok').value = maxStok;
                document.getElementById('form-pembelian-banyak').submit();
            }
        </script>
    </body>
</html>