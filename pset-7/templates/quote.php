<p>
<?php
    $stock = lookup($_POST["symbol"]);
    echo "A share of " . $stock["name"] . " (" . $stock["symbol"] . ")" . " cost $" . number_format($stock["price"],2,".",",");
?>
</p>
