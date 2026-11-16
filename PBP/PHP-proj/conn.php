<?php
    require_once __DIR__ . '/../vendor/autoload.php';

    $dotenv = Dotenv\Dotenv::createImmutable(__DIR__ . '/..');
    $dotenv->load();

    $hostname = $_ENV['DB_HOST'];
    $usernamedb = $_ENV['DB_USER'];
    $passworddb = $_ENV['DB_PASS'];
    $database = $_ENV['DB_NAME'];

    try {
        $koneksi = mysqli_connect($hostname, $usernamedb, $passworddb, $database);

        if ($koneksi) {
            echo "Server Online<br><br>";
        }
    } catch (mysqli_sql_exception $e) {
        $errorCode = $e->getCode();

        error_log("Error $errorCode: " . $e->getMessage());
        echo "Server Offline<br><br>";
    }
?>
