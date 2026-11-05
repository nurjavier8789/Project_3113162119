<?php
    include 'db.php';
    $koneksi = mysqli_connect($hostname, $usernamedb, $passworddb, $database);

    if ($koneksi) {
        echo "Server Online<br>";
    } else {
        echo "Server Offline<br>";
    }

    if (isset($_POST['login'])) {
        $username = $_POST['username'];
        $password = $_POST['password'];

        $result = "SELECT * FROM users";

        if (mysqli_query($koneksi, $login)) {
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
    <title>Login</title>
</head>
<body>
    <h1>Login</h1>

    <form action="index.php" method="POST">
        <input type="text" name="username" id="username" placeholder="Username">
        <input type="password" name="password" id="password" placeholder="Password">

        <button type="submit" name="login">Login</button>
    </form>
    <p><a href="register.php">Buat akun</a></p>
</body>
</html>