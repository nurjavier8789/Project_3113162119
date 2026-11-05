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

    if (isset($_POST['register'])) {
        $username = $_POST['username'];
        $password = $_POST['password'];

        $regis = "INSERT INTO users(username, password) VALUES ('$username', '$password')";

        if (mysqli_query($koneksi, $regis)) {
            echo "Data masuk!";
        } else {
            echo "Ada masalah!";
        }
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Register</title>
</head>
<body>
    <h1>Register</h1>

    <form action="register.php" method="POST">
        <input type="text" name="username" id="username" placeholder="Username">
        <input type="password" name="password" id="password" placeholder="Password">

        <button type="submit" name="register">Register</button>
    </form>

    <p><a href="index.php">Kembali</a></p>
</body>
</html>