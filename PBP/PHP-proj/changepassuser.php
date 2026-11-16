<?php
    include "conn.php";

    session_start();

    if (!isset($_SESSION["is_login"])) {
        header("location: index.php");
        exit;
    };

    if (isset($_POST['changepass'])) {
        $username = $_SESSION['username'];
        $password = $_POST['oldpass'];
        $password1 = $_POST['newpass1'];

        try {
            $query = "SELECT * FROM users WHERE username = '$username' AND password = '$password'";
            $result = mysqli_query($koneksi, $query);

            if ($result->num_rows > 0) {
                if ($_POST['newpass1'] == $_POST['newpass2']) {
                    $query = "UPDATE users SET password = '$password1' WHERE users.username = '$username' ";
                    $result1 = mysqli_query($koneksi, $query);

                    if ($result1) {
                        $_SESSION['messages'] = "Password berhasil diubah!";
                        header("location: account.php");
                    }
                } else {
                    $_SESSION['messages'] = "Password baru tidak cocok!";
                    header("location: account.php");
                };
            } else {
                $_SESSION['messages'] = "Password lama salah!";
                header("location: account.php");
            }
        } catch (mysqli_sql_exception $e) {
            $errorCode = $e->getCode();

            error_log("Error $errorCode: " . $e->getMessage());
            $_SESSION['messages'] = "Terjadi kesalahan pada server.";
            header("location: account.php");
        }
    }

    if (isset($_POST['checkusername'])) {
        $username = $_POST['newusername'];

        try {
            $query = "SELECT * FROM users WHERE username = '$username'";
            $result = mysqli_query($koneksi, $query);

            if ($result->num_rows > 0) {
                $_SESSION['is_available'] = false;
                $_SESSION['messages'] = "Username tidak tersedia";
                $_SESSION["newUsername"] = $username;
                header("location: account.php");
            } else {
                $_SESSION['is_available'] = true;
                $_SESSION['messages'] = "Username tersedia";
                $_SESSION["newUsername"] = $username;
                header("location: account.php");
            }
        } catch (mysqli_sql_exception $e) {
            $errorCode = $e->getCode();

            error_log("Error $errorCode: " . $e->getMessage());
            $_SESSION['messages'] = "Terjadi kesalahan pada server.";
            header("location: account.php");
        }
    }

    if (isset($_POST['changeusername'])) {
        $newUsername = $_POST['newusername'];
        $oldUsername = $_SESSION['username'];

        try {
            $query = "UPDATE users SET username = '$newUsername' WHERE users.username = '$oldUsername' ";
            $result = mysqli_query($koneksi, $query);
            
            if ($result) {
                if (mysqli_affected_rows($koneksi) > 0) {
                    $_SESSION['messages'] = "Username berhasil diubah!";
                    $_SESSION['username'] = $newUsername;
                } else {
                    $_SESSION['messages'] = "Username tetap sama!";
                    $_SESSION['username'] = $newUsername;
                }
                header("location: account.php");
            }
        } catch (mysqli_sql_exception $e) {
            $errorCode = $e->getCode();

            error_log("Error $errorCode: " . $e->getMessage());
            $_SESSION['messages'] = "Terjadi kesalahan pada server.";
            header("location: account.php");
        }
    }
?>
