<?php

    // configuration
    require("../includes/config.php");
    
    // set variable "id"
    $id = $_SESSION["id"];
    
    // process SQL queries to get arrays
    $rows = query("SELECT symbol, shares FROM portfolio WHERE id = $id");
    $cash = query("SELECT cash FROM users WHERE id = $id");
    
    // set variable "cash"
    $cash = $cash[0]["cash"];
    
    // set variables "positions"
    $positions = [];
    
    // iterate over each position to extract variables
    foreach ($rows as $row)
    {
        // iterate over symbol to extract stock info from Yahoo
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);
?>
