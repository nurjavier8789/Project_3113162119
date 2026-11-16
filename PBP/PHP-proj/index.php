<?php
    session_start();

    if (isset($_SESSION["is_login"])) {
        header("location: tokline.php");
        exit;
    } else {
        session_abort();
    };

    include "conn.php";

    if (isset($_POST['login'])) {
        $username = $_POST['username'];
        $password = $_POST['password'];

        $query = "SELECT * FROM users WHERE username = '$username' AND password = '$password'";

        $result = mysqli_query($koneksi, $query) or die(mysqli_error($koneksi));

        if ($result->num_rows > 0) {
            session_start();
            $_SESSION["is_login"] = true;
            $_SESSION["username"] = $username;
            header("location: tokline.php");
        } else {
            echo "Tidak ada!";
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
        <input type="text" name="username" id="username" placeholder="Username" required>
        <input type="password" name="password" id="password" placeholder="Password" required>

        <button type="submit" name="login">Login</button>
    </form>
    <p><a href="register.php">Buat akun</a></p>
</body>
</html>