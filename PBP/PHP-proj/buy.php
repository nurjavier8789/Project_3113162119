<?php
    session_start();

    if (!isset($_SESSION["is_login"])) {
        header("location: index.php");
        exit;
    };

    require_once __DIR__ . '/../vendor/autoload.php';

    $dotenv = Dotenv\Dotenv::createImmutable(__DIR__ . '/..');
    $dotenv->load();

    $hostname = $_ENV['DB_HOST'];
    $usernamedb = $_ENV['DB_USER'];
    $passworddb = $_ENV['DB_PASS'];
    $database = $_ENV['DB_NAME'];

    $conn = mysqli_connect($hostname, $usernamedb, $passworddb, $database);

    $id = $_POST['produk_id'];
    $jumlahAkhir = $_POST['stok'] - $_POST['jumlah'];

    $query = "UPDATE produk SET stok='$jumlahAkhir' WHERE kode_produk='$id';";
    $result = mysqli_query($conn, $query);

    header("location: tokline.php");
    exit;
?>