<?php
$prices = [
    "desktop" => 1234,
    "laptop" => 2345,
    "hdd" => 246,
    "ram" => 79
];

$names = [
    "desktop" => "CPU",
    "laptop" => "Laptop",
    "hdd" => "Hard Disk Drive",
    "ram" => "RAM module"
];

$selected = isset($_POST["items"]) ? $_POST["items"] : [];
$total = 0;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Invoice</title>
</head>
<body>
    <h1>CSCI Store Invoice</h1>

    <table border="1" cellpadding="15">
        <tr>
            <th>Item</th>
            <th>Price</th>
        </tr>

        <?php
        if (empty($selected)) {
            echo "<tr><td colspan='2'>No items selected.</td></tr>";
        } else {
            foreach ($selected as $item) {
                echo "<tr>
                        <td>{$names[$item]}</td>
                        <td>\${$prices[$item]}</td>
                    </tr>";
                $total += $prices[$item];
            }
        }
        ?>

        <tr>
            <td><strong>Total</strong></td>
            <td><strong>$<?php echo $total; ?></strong></td>
        </tr>
    </table>

    <br>
    <a href="store.html">Retun to Store</a>
    <a href="index.html">Return to Home</a>
</body>
</html>