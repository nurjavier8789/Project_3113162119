<?php
    include "conn.php";

    if (isset($_SESSION["is_login"])) {
        header("location: tokline.php");
        exit;
    };

    if (isset($_POST['register'])) {
        $username = $_POST['username'];
        $password = $_POST['password'];

        try {
            $regis = "INSERT INTO users(username, password) VALUES ('$username', '$password')";
            $result = mysqli_query($koneksi, $regis);
            
            if ($result) {
                echo "Data masuk!";
            }
        } catch (mysqli_sql_exception $e) {
            $errorCode = $e->getCode();
            $error_msg = match ($errorCode) {
                1062    => "Username sudah digunakan!<br>Pilih username lain.",
                default => "Terjadi gangguan sistem database."
            };

            echo $error_msg;
            error_log("Error $errorCode: " . $e->getMessage());
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
        <input type="text" name="username" id="username" placeholder="Username" required>
        <input type="password" name="password" id="password" placeholder="Password" required>

        <button type="submit" name="register">Register</button>
    </form>

    <p><a href="index.php">Kembali</a></p>
</body>
</html>