<?php
$showForm = true;
$errorMsg = "";
$result = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["return"])) {
        $showForm = true;
    } else {
        $amount = $_POST["amount"];
        $tax = $_POST["tax"];

        if (!is_numeric($amount) || !is_numeric($tax)) {
            $showForm = false;
            $errorMsg = "
                <div style='background-color:#808080; color:red; padding:5px; width:300px;'>
                    Amount must be a numeric value!<br/>
                    Rate must be a numeric value!<br/>
                    Cannot calculate!
                </div>
                <form method='post'>
                    <button type='submit' name='return'>Return to Calculator</button>
                </form>
            ";
        } else {
            $taxAmount = ($tax/100) * $amount;
            $total = $amount + $taxAmount;

            $showForm = false;
            $result = "
                <h2>Calculation Result</h2>
                <p>Entered Amount: $$amount</p>
                <p>Entered Tax Rate: $tax%</p>
                <p>Calculated Tax Amount: $" . number_format($total, 2) . "</p>

                <form method='post'>
                    <button type='submit' name='return'>Return to Calculator</button>
                </form>
            ";
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Task 1</title>
</head>
<body>
    <h1>Sales Tax Calculator</h1>

    <?php if ($errorMsg !== "") echo $errorMsg; ?>

    <?php if ($showForm): ?>
    <form method="post">
        Amount: <input type="text" name="amount" /><br/>
        Tax Rate (%): <input type="text" name="tax" /><br/>
        <input type="submit" value="Calculate"/>
    </form>
    <?php endif; ?>

    <?php echo $result; ?>
</body>
</html>