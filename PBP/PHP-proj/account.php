<?php
    include "conn.php";

    session_start();

    if (!isset($_SESSION["is_login"])) {
        header("location: index.php");
        exit;
    };

    $messages = $_SESSION["messages"] ?? null;
    $is_available = $_SESSION['is_available'] ?? null;

    if (!$messages == null) {
        echo "<b>$messages</b>";
        unset($_SESSION['messages']);
    }
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Toko Online - Akun</title>
    </head>
    <body>
        <p>Halo <b><?= $_SESSION["username"] ?></b>!</p>
        <p><a href="tokline.php">Kembali</a></p>

        <h1>Pengaturan</h1>

        <h2>Ubah Username</h2>

        <form action="changepassuser.php" method="POST">
            <input type="text" name="newusername" id="newUsername" placeholder="Username" oninput="resetButton()" required><br><br>

            <button type="submit" name="checkusername">Cek Username</button>
            <button type="submit" name="changeusername" id="btnChangeUsername" disabled>Ganti Username</button>
        </form>

        <script>
            function resetButton() {
                btnChangeUsername.disabled = true;
            }

            <?php if (isset($_SESSION["newUsername"])): ?>
                document.getElementById("newUsername").value = "<?= $_SESSION["newUsername"] ?>";
                <?php unset($_SESSION["newUsername"]); ?>
            <?php endif; ?>

            <?php if (isset($_SESSION['is_available']) && ($_SESSION['is_available'])): ?>
                btnChangeUsername.disabled = false;
                <?php unset($_SESSION["is_available"]); ?>
            <?php elseif (isset($_SESSION['is_available']) && (!$_SESSION['is_available'])): ?>
                btnChangeUsername.disabled = true;
                <?php unset($_SESSION["is_available"]); ?>
            <?php endif; ?>
        </script>

        <hr>

        <h2>Ubah Password</h2>

        <form action="changepassuser.php" method="POST">
            <input type="password" name="oldpass" placeholder="Password Lama" required><br>
            <input type="password" name="newpass1" placeholder="Password Baru" required><br>
            <input type="password" name="newpass2" placeholder="Ulangi Password Baru" required><br><br>

            <button type="submit" name="changepass">Ubah Password</button>
        </form>
    </body>
</html>

<?php
    if (!$is_available == null) {
        unset($_SESSION['is_available']);
    }
?>
