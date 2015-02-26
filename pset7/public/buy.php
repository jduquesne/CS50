<?php

    // configuration
    require("../includes/config.php"); 

    // set "id"
    $id = $_SESSION["id"];

    // set "cash"
    $cash = query("SELECT cash FROM users WHERE id = $id");
    $cash = $cash[0]["cash"];
    
    // if stock symbol was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {           

        // set stock and price
        $stock = lookup($_POST["symbol"]);
        $price = lookup($stock["price"]);

        // validate submission
        if ($stock == false)
        {
            apologize("Sorry, you entered an invalid ticker symbol.");
        }
        else if (preg_match("/^\d+$/", $_POST["shares"]) == false || $_POST["shares"] == 0)
        {
            apologize("Sorry, you must provide a positive whole number of shares to buy.");
        }
        else if ($_POST["shares"] * $stock["price"] > $cash)
        {
            apologize("Sorry, you don't have the funds.");
        }
        
        // update portfolio
        $symbol = strtoupper ($stock["symbol"]);
        query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $id, $symbol, $_POST["shares"]);
        
        // update cash value
        $cash = $cash - $_POST["shares"] * $stock["price"]; 
        query("UPDATE users SET cash = '$cash' WHERE id = $id");

        // update history
        query("INSERT INTO history (userid, time, symbol, shares, price, action) VALUES(?, now(), ?, ?, ?, ?)", $id, $symbol, $_POST["shares"], $stock["price"], "BUY");

        // redirect to buy form confirming purchase
        render("buy.php", ["cash" => number_format($cash,2,".",","), "number" => $_POST["shares"], "position" => $symbol, "title" => "Bought share"]);   
    }
    else
    {
        // render sell form
        render("buy_form.php", ["cash" => $cash, "title" => "Buy share"]);
    }    
?>
